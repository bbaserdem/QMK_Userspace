/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */

#include "batuhan.h"

// Need memcpy and memcmp from string.h along with transfer stuff
#ifdef SPLIT_KEYBOARD
#    include "transactions.h"
#    include <string.h>
#endif // SPLIT_KEYBOARD

/*-------------------------*\
|*-----KEYBOARD CONFIG-----*|
\*-------------------------*/
// Separate the userspace general from user settings set in keyboard folder
userspace_config_t  userspace_config;
userspace_runtime_t userspace_runtime;

// EEPROM wear leveling
static bool config_dirty = false;
void        mark_config_dirty(void) {
    config_dirty = true;
}

/*---------------------------------*\
|*----SPLIT KEYBOARD TRANSPORT-----*|
\*---------------------------------*/
// Want to transfer my internal state variables across split keyboards.
// These information are in custom structs, defined in the header
// Split into two, because one gets written to EEPROM and one doesn't
#ifdef SPLIT_KEYBOARD
userspace_config_t  transport_userspace_config;
userspace_runtime_t transport_userspace_runtime;

// Translate the RPC data to the local variables, from primary to secondary
void userspace_config_sync(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    // Copy incoming data from primary to local variable at secondary
    if (in_buflen == sizeof(transport_userspace_config)) {
        memcpy(&transport_userspace_config, in_data, in_buflen);
    }
    // There is no data to send back; so no output handling
}
void userspace_runtime_sync(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    // Copy incoming data from primary to local variable at secondary
    if (in_buflen == sizeof(transport_userspace_runtime)) {
        memcpy(&transport_userspace_runtime, in_data, in_buflen);
    }
    // There is no data to send back; so no output handling
}

// Either send or receive the correct data
void userspace_transport_update(void) {
    if (is_keyboard_master()) {
        // If we are the main device; we want to send info.
        transport_userspace_config.raw  = userspace_config.raw;
        transport_userspace_runtime.raw = userspace_runtime.raw;
    } else {
        // If we are the secondary device; we want to receive info.
        userspace_config.raw  = transport_userspace_config.raw;
        userspace_runtime.raw = transport_userspace_runtime.raw;
    }
}

// Initiate the protocol on sync
void userspace_transport_sync(bool force_sync) {
    if (is_keyboard_master()) {
        // Keep track of the last state
        static userspace_config_t  last_userspace_config  = {0};
        static userspace_runtime_t last_userspace_runtime = {0};
        static uint32_t            last_sync_timer = 0;

        // Throttle RPC calls per documentation (500ms for normal sync)
        if (!force_sync && timer_elapsed32(last_sync_timer) < 500) {
            return;
        }

        // Check if the config values are different
        bool config_needs_sync = memcmp(&transport_userspace_config, &last_userspace_config, sizeof(transport_userspace_config)) != 0;
        if (config_needs_sync) {
            memcpy(&last_userspace_config, &transport_userspace_config, sizeof(transport_userspace_config));
        }

        // Check if the runtime values are different
        bool runtime_needs_sync = memcmp(&transport_userspace_runtime, &last_userspace_runtime, sizeof(transport_userspace_runtime)) != 0;
        if (runtime_needs_sync) {
            memcpy(&last_userspace_runtime, &transport_userspace_runtime, sizeof(transport_userspace_runtime));
        }

        // Perform the syncs independently using transaction_rpc_send
        bool sync_success = true;
        if (config_needs_sync || force_sync) {
            if (!transaction_rpc_send(RPC_ID_CONFIG_SYNC, sizeof(transport_userspace_config), &transport_userspace_config)) {
                sync_success = false;
                dprint("Config sync failed!\n");
            }
        }

        if (runtime_needs_sync || force_sync) {
            if (!transaction_rpc_send(RPC_ID_RUNTIME_SYNC, sizeof(transport_userspace_runtime), &transport_userspace_runtime)) {
                sync_success = false;
                dprint("Runtime sync failed!\n");
            }
        }

        // Update sync timer only if we successfully sent something
        if (sync_success && (config_needs_sync || runtime_needs_sync || force_sync)) {
            last_sync_timer = timer_read32();
        }
    }
}
#endif // SPLIT_KEYBOARD

/*---------------------------*\
|*-----KEYBOARD PRE INIT-----*|
\*---------------------------*/
/* This code runs before anything is started.
 * Good for early hardware setup
 */
BATUHAN_WEAK_HOOK_VOID(keyboard_pre_init, (void)) {
    // Keymap specific stuff
    keyboard_pre_init_keymap();
}

/*---------------------*\
|*-----MATRIX INIT-----*|
\*---------------------*/
/* This code runs once midway thru the firmware process.
 * So far, sets the base layer and fixes unicode mode
 */
BATUHAN_WEAK_HOOK_VOID(matrix_init, (void)) {
    // Keymap specific things
    matrix_init_keymap();
}

/*----------------------------*\
|*-----KEYBOARD POST INIT-----*|
\*----------------------------*/
/* This code runs after anything is started.
 * Good for late hardware setup, like setting up layer specifications
 */
BATUHAN_WEAK_HOOK_VOID(keyboard_post_init, (void)) {
    // Fix beginning base layer, in case some other firmware was flashed
    //  set_single_persistent_default_layer(_BASE);

    // Load configuration from EEPROM with validation
    userspace_config.raw = eeconfig_read_user();
    
    // Validate the loaded configuration
    bool needs_init = false;
    
    // Check if encoder values are within valid ranges
#ifdef ENCODER_ENABLE
    if (userspace_config.bits.e0base >= ENC_MODE_BASE_COUNT ||
        userspace_config.bits.e1base >= ENC_MODE_BASE_COUNT ||
        userspace_config.bits.e0point >= ENC_MODE_POINTER_COUNT ||
        userspace_config.bits.e1point >= ENC_MODE_POINTER_COUNT ||
        userspace_config.bits.e0rgb >= ENC_MODE_RGB_COUNT ||
        userspace_config.bits.e1rgb >= ENC_MODE_RGB_COUNT) {
        needs_init = true;
    }
#endif
    
    // Check if layout value is valid (2 bits = max value 3)
    if (userspace_config.bits.layout > 3) {
        needs_init = true;
    }
    
    // If invalid or uninitialized (all 0xFF), reinitialize
    if (needs_init || userspace_config.raw == 0xFFFFFFFF) {
        eeconfig_init_user();
        userspace_config.raw = eeconfig_read_user();
    }

    // Split keyboard halves communication
#ifdef SPLIT_KEYBOARD
    // Register the transactions
    transaction_register_rpc(RPC_ID_CONFIG_SYNC, userspace_config_sync);
    transaction_register_rpc(RPC_ID_RUNTIME_SYNC, userspace_runtime_sync);
    
    if (is_keyboard_master()) {
        // Update the transport variable
        userspace_transport_update();
        // Do one forced transfer to sync halves
        userspace_transport_sync(true);
    } else {
        // Just sync the data received
        userspace_transport_update();
    }
#endif // SPLIT_KEYBOARD

    // TODO: Implement these features
    // Backlight LED
// #ifdef BACKLIGHT_ENABLE
//     keyboard_post_init_backlight();
// #endif // BACKLIGHT_ENABLE

    // RGB underglow
// #ifdef RGBLIGHT_ENABLE
//     keyboard_post_init_rgblight();
// #endif // RGBLIGHT_ENABLE

    // Keymap specific stuff
    keyboard_post_init_keymap();
}

/*---------------------------*\
|*-----HOUSEKEEPING TASK-----*|
\*---------------------------*/
/* This gets called at the end of all qmk processing
 */
BATUHAN_WEAK_HOOK_VOID(housekeeping_task, (void)) {
    // Check eeprom every now and then
    static userspace_config_t prev_userspace_config;
    static fast_timer_t       throttle_timer = 0;
    static bool               init_flag      = true;

    // Read this if we never read it before
    if (init_flag) {
        init_flag                 = false;
        prev_userspace_config.raw = eeconfig_read_user();
    }

    // Throttled tasks here
    if (timer_elapsed_fast(throttle_timer) >= HOUSEKEEPING_THROTTLE_INTERVAL_MS) {
        // Refresh timer
        throttle_timer = timer_read_fast();
        // Check userspace config for eeprom updates (wear leveling)
        if (config_dirty || memcmp(&prev_userspace_config, &userspace_config, sizeof(userspace_config)) != 0) {
            memcpy(&prev_userspace_config, &userspace_config, sizeof(userspace_config));
            eeconfig_update_user(userspace_config.raw);
            config_dirty = false;
        }
    }

    // Do transport stuff if we are split boards - per documentation, sync in housekeeping
#ifdef SPLIT_KEYBOARD
    if (is_keyboard_master()) {
        // Update local transport variables from userspace variables
        userspace_transport_update();
        // Perform the sync with throttling (false = normal throttled sync)
        userspace_transport_sync(false);
    }
#endif // SPLIT_KEYBOARD

    // Hook to keymap code
    housekeeping_task_keymap();
}

/*-----------------------*\
|*-----EECONFIG INIT-----*|
\*-----------------------*/
/* Default values to send to the eeprom
 */
void eeconfig_init_user(void) {
    // Set everything to default
    userspace_config.raw = 0;
    
    // Set encoder states to sane defaults if enabled
#ifdef ENCODER_ENABLE
    // Initialize encoder 0 (left/first encoder)
    userspace_config.bits.e0base = ENC_MODE_VOLUME;     // Default: volume control
    userspace_config.bits.e0point = ENC_MODE_LATERAL;   // Mouse mode: horizontal scroll
    userspace_config.bits.e0rgb = ENC_MODE_HUE;         // RGB mode: hue control
    
    // Initialize encoder 1 (right/second encoder)
    userspace_config.bits.e1base = ENC_MODE_SONG;       // Default: song control (media next/prev)
    userspace_config.bits.e1point = ENC_MODE_VERTICAL;  // Mouse mode: vertical scroll  
    userspace_config.bits.e1rgb = ENC_MODE_VALUE;       // RGB mode: brightness control
#endif // ENCODER_ENABLE
    
    // Set default layout
    userspace_config.bits.layout = 0;
    
    // Initialize runtime state
    userspace_runtime.raw = 0;
    userspace_runtime.rgb_sleep = false;
    
    // Update the eeprom with the new defaults
    eeconfig_update_user(userspace_config.raw);
    mark_config_dirty(); // Ensure it gets written
}

/*------------------------*\
|*-----PROCESS RECORD-----*|
\*------------------------*/
/* Process record: custom keycodes to process here
 * Allow also the following codes to hook here as well;
 *  Macro definitions
 *  Audio hooks
 */
BATUHAN_WEAK_HOOK_RETURN(process_record, bool, (uint16_t keycode, keyrecord_t* record), true) {
    // Return after running through all individual hooks
    return process_record_keymap(keycode, record)
#ifdef AUDIO_ENABLE
           && process_record_audio(keycode, record)
#endif // AUDIO_ENABLE
// #ifdef ENCODER_ENABLE
//            && process_record_encoder(keycode, record)
// #endif // ENCODER_ENABLE
           ;
}

/*---------------------*\
|*-----MATRIX SCAN-----*|
\*---------------------*/
/* This code runs every frame
 * I used to check for layer switching here, but layer state is better used.
 * Try to not put anything here; as it runs hundreds time per second-ish
 */
BATUHAN_WEAK_HOOK_VOID(matrix_scan, (void)) {
    // Keymap specific scan function
    matrix_scan_keymap();
}

/*---------------------*\
|*-----LAYER STATE-----*|
\*---------------------*/
/* This code runs after every layer change
 * State represents the new layer state.
 */
BATUHAN_WEAK_HOOK_RETURN(layer_state_set, layer_state_t, (layer_state_t state), state) {
    // Keymap layer state setting
    state = layer_state_set_keymap(state);
    // TODO: Implement these features
    // For underglow stuff
// #ifdef RGBLIGHT_ENABLE
//     state = layer_state_set_rgblight(state);
// #endif // RGBLIGHT_ENABLE
    // Audio playback
#ifdef AUDIO_ENABLE
    state = layer_state_set_audio(state);
#endif // AUDIO_ENABLE

    return state;
}

/*-----------------------------*\
|*-----DEFAULT LAYER STATE-----*|
\*-----------------------------*/
/* This code runs after every time default base layer is changed
 */
BATUHAN_WEAK_HOOK_RETURN(default_layer_state_set, layer_state_t, (layer_state_t state), state) {
    // Keymap level code
    state = default_layer_state_set_keymap(state);
    return state;
}

/*------------------------*\
|*-----LED SET KEYMAP-----*|
\*------------------------*/
/* Code for LED indicators
 * I'm not sure when exactly does this code run
 */
BATUHAN_WEAK_HOOK_VOID(led_set, (uint8_t usb_led)) {
    led_set_keymap(usb_led);
}

/*-----------------*\
|*-----SUSPEND-----*|
\*-----------------*/
/* Suspend stuff here, mostly for the rgb lighting.
 */
BATUHAN_WEAK_HOOK_VOID(suspend_power_down, (void)) {
    suspend_power_down_keymap();
    // TODO: Implement RGB matrix sleep hook
// #ifdef RGB_MATRIX_ENABLE
//     suspend_power_down_rgbmatrix();
// #endif // RGB_MATRIX_ENABLE
}

BATUHAN_WEAK_HOOK_VOID(suspend_wakeup_init, (void)) {
    suspend_wakeup_init_keymap();
    // TODO: Implement RGB matrix sleep hook
// #ifdef RGB_MATRIX_ENABLE
//     suspend_wakeup_init_rgbmatrix();
// #endif // RGB_MATRIX_ENABLE
}

/*------------------*\
|*-----SHUTDOWN-----*|
\*------------------*/
/* Shutdown stuff here; for when entering bootmode.
 */
BATUHAN_WEAK_HOOK_RETURN(shutdown, bool, (bool jump_to_bootloader), true) {
    // TODO: Implement these features
    // Underglow LED hook on boot
// #ifdef RGBLIGHT_ENABLE
//     shutdown_rgblight();
// #endif // RGBLIGHT_ENABLE
    // Perkey led hook on boot
// #ifdef RGB_MATRIX_ENABLE
//     shutdown_rgbmatrix();
// #endif // RGB_MATRIX_ENABLE
    // Keymap hooks
    shutdown_keymap(jump_to_bootloader);
    return true;
}
