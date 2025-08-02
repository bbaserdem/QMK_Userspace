/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */

#include "sbp.h"

// Language imports
#include <sendstring_dvorak.h>

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
        static userspace_config_t  last_userspace_config;
        static userspace_runtime_t last_userspace_runtime;
        static fast_timer_t        last_sync_timer = 0;

        // Throttle RPC bursts (20ms minimum gap)
        if (!force_sync && timer_elapsed_fast(last_sync_timer) < 20) {
            return;
        }

        // Check if the config values are different
        bool config_needs_sync = memcmp(&transport_userspace_config, &last_userspace_config, sizeof(transport_userspace_config));
        if (config_needs_sync) {
            memcpy(&last_userspace_config, &transport_userspace_config, sizeof(transport_userspace_config));
        }

        // Check if the runtime values are different
        bool runtime_needs_sync = memcmp(&transport_userspace_runtime, &last_userspace_runtime, sizeof(transport_userspace_runtime));
        if (runtime_needs_sync) {
            memcpy(&last_userspace_runtime, &transport_userspace_runtime, sizeof(transport_userspace_runtime));
        }

        // Perform the syncs independently
        if (config_needs_sync || force_sync) {
            transaction_rpc_send(RPC_ID_CONFIG_SYNC, sizeof(transport_userspace_config), &transport_userspace_config);
        }

        if (runtime_needs_sync || force_sync) {
            transaction_rpc_send(RPC_ID_RUNTIME_SYNC, sizeof(transport_userspace_runtime), &transport_userspace_runtime);
        }

        // Update sync timer if we sent anything
        if (config_needs_sync || runtime_needs_sync || force_sync) {
            last_sync_timer = timer_read_fast();
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
SBP_WEAK_HOOK_VOID(keyboard_pre_init, (void)) {
    // Keymap specific stuff
    keyboard_pre_init_keymap();
}

/*---------------------*\
|*-----MATRIX INIT-----*|
\*---------------------*/
/* This code runs once midway thru the firmware process.
 * So far, sets the base layer and fixes unicode mode
 */
SBP_WEAK_HOOK_VOID(matrix_init, (void)) {
    // Keymap specific things
    matrix_init_keymap();
}

/*----------------------------*\
|*-----KEYBOARD POST INIT-----*|
\*----------------------------*/
/* This code runs after anything is started.
 * Good for late hardware setup, like setting up layer specifications
 */
SBP_WEAK_HOOK_VOID(keyboard_post_init, (void)) {
    // Fix beginning base layer, in case some other firmware was flashed
    //  set_single_persistent_default_layer(_BASE);

    // Split keyboard halves communication
#ifdef SPLIT_KEYBOARD
    // Register the transactions
    transaction_register_rpc(RPC_ID_CONFIG_SYNC, userspace_config_sync);
    transaction_register_rpc(RPC_ID_RUNTIME_SYNC, userspace_runtime_sync);
    // Load default config values
    if (is_keyboard_master()) {
        // If we are main; load from EEPROM
        userspace_config.raw = eeconfig_read_user();
        // And update the transport variable
        userspace_transport_update();
        // Do one forced transfer to sync halves
        userspace_transport_sync(true);
    } else {
        // Just sync the data received
        userspace_transport_update();
    }
#else  // SPLIT_KEYBOARD
    // If we are not split; just load from eeprom
    userspace_config.raw = eeconfig_read_user();
#endif // SPLIT_KEYBOARD

    // Backlight LED
#ifdef BACKLIGHT_ENABLE
    keyboard_post_init_backlight();
#endif // BACKLIGHT_ENABLE

    // RGB underglow
#ifdef RGBLIGHT_ENABLE
    keyboard_post_init_rgblight();
#endif // RGBLIGHT_ENABLE

    // Keymap specific stuff
    keyboard_post_init_keymap();
}

/*---------------------------*\
|*-----HOUSEKEEPING TASK-----*|
\*---------------------------*/
/* This gets called at the end of all qmk processing
 */
SBP_WEAK_HOOK_VOID(housekeeping_task, (void)) {
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
        if (config_dirty || memcmp(&prev_userspace_config, &userspace_config, sizeof(userspace_config))) {
            memcpy(&prev_userspace_config, &userspace_config, sizeof(userspace_config));
            eeconfig_update_user(userspace_config.raw);
            config_dirty = false;
        }
    }

    // Do transport stuff if we are split boards
#ifdef SPLIT_KEYBOARD
    userspace_transport_update();
    userspace_transport_sync(false);
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
    reset_encoder_state();
#endif // ENCODER_ENABLE
    // Update the eeprom
    eeconfig_update_user(userspace_config.raw);
}

/*------------------------*\
|*-----PROCESS RECORD-----*|
\*------------------------*/
/* Process record: custom keycodes to process here
 * Allow also the following codes to hook here as well;
 *  Macro definitions
 *  Audio hooks
 */
SBP_WEAK_HOOK_RETURN(process_record, bool, (uint16_t keycode, keyrecord_t* record), true) {
    // Return after running through all individual hooks
    return process_record_keymap(keycode, record) &&
#ifdef AUDIO_ENABLE
           process_record_audio(keycode, record) &&
#endif // AUDIO_ENABLE
#ifdef ENCODER_ENABLE
           process_record_encoder(keycode, record) &&
#endif // ENCODER_ENABLE
           process_record_macro(keycode, record);
}

/*---------------------*\
|*-----MATRIX SCAN-----*|
\*---------------------*/
/* This code runs every frame
 * I used to check for layer switching here, but layer state is better used.
 * Try to not put anything here; as it runs hundreds time per second-ish
 */
SBP_WEAK_HOOK_VOID(matrix_scan, (void)) {
    // Keymap specific scan function
    matrix_scan_keymap();
}

/*---------------------*\
|*-----LAYER STATE-----*|
\*---------------------*/
/* This code runs after every layer change
 * State represents the new layer state.
 */
SBP_WEAK_HOOK_RETURN(layer_state_set, layer_state_t, (layer_state_t state), state) {
    // Keymap layer state setting
    state = layer_state_set_keymap(state);
    // For underglow stuff
#ifdef RGBLIGHT_ENABLE
    state = layer_state_set_rgblight(state);
#endif // RGBLIGHT_ENABLE
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
SBP_WEAK_HOOK_RETURN(default_layer_state_set, layer_state_t, (layer_state_t state), state) {
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
SBP_WEAK_HOOK_VOID(led_set, (uint8_t usb_led)) {
    led_set_keymap(usb_led);
}

/*-----------------*\
|*-----SUSPEND-----*|
\*-----------------*/
/* Suspend stuff here, mostly for the rgb lighting.
 */
SBP_WEAK_HOOK_VOID(suspend_power_down, (void)) {
    suspend_power_down_keymap();
    // RGB matrix sleep hook
#ifdef RGB_MATRIX_ENABLE
    suspend_power_down_rgbmatrix();
#endif // RGB_MATRIX_ENABLE
}

SBP_WEAK_HOOK_VOID(suspend_wakeup_init, (void)) {
    suspend_wakeup_init_keymap();
    // RGB matrix sleep hook
#ifdef RGB_MATRIX_ENABLE
    suspend_wakeup_init_rgbmatrix();
#endif // RGB_MATRIX_ENABLE
}

/*------------------*\
|*-----SHUTDOWN-----*|
\*------------------*/
/* Shutdown stuff here; for when entering bootmode.
 */
SBP_WEAK_HOOK_VOID(shutdown, (void)) {
    // Underglow LED hook on boot
#ifdef RGBLIGHT_ENABLE
    shutdown_rgblight();
#endif // RGBLIGHT_ENABLE
    // Perkey led hook on boot
#ifdef RGB_MATRIX_ENABLE
    shutdown_rgbmatrix();
#endif // RGB_MATRIX_ENABLE
    // Keymap hooks
    shutdown_keymap();
}
