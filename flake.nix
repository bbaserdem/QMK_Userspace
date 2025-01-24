{
  description = "Flake for using qmk firmware";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-24.11";
    nixpkgs-unstable.url = "github:nixos/nixpkgs/nixos-24.11";
    flake-utils.url = "github:numtide/flake-utils";

    # QMK sources
    qmk-firmware = {
      flake = false;
      url = "github:qmk/qmk_firmware";
    };

    # QMK Submodules
    qmk-chibios = {
      repo = "ChibiOS";
      owner = "qmk";
      type = "github";
      ref = "master";
      flake = false;
    };
    qmk-chibios-contrib = {
      repo = "ChibiOS-Contrib";
      owner = "qmk";
      type = "github";
      ref = "master";
      flake = false;
    };
    qmk-googletest = {
      repo = "googletest";
      owner = "qmk";
      type = "github";
      flake = false;
    };
    qmk-lufa = {
      repo = "lufa";
      owner = "qmk";
      type = "github";
      flake = false;
    };
    qmk-vusb = {
      repo = "v-usb";
      owner = "qmk";
      type = "github";
      flake = false;
    };
    qmk-printf = {
      repo = "printf";
      owner = "qmk";
      type = "github";
      flake = false;
    };
    qmk-pico-sdk = {
      repo = "pico-sdk";
      owner = "qmk";
      type = "github";
      flake = false;
    };
    qmk-lvgl = {
      repo = "lvgl";
      owner = "qmk";
      type = "github";
      ref = "release/v8.2";
      flake = false;
    };
  };

  outputs = {
    self,
    ...
  } @ inputs: inputs.flake-utils.lib.eachDefaultSystem (system:
  let

    # Default user to be used in this qmk
    keymap = "sbp";

    # Generic pkgs import
    pkgs = inputs.nixpkgs.legacyPackages.${system};

    # Config settings for qmk, so this repo works as the qmk overlay
    qmkConfig = pkgs.writeTextFile {
      name = "qmk-config.ini";
      text = ''
        [user]
        keymap = ${keymap}
        overlay_dir = ${self}
      '';
    };

    qmkFirmware = pkgs.callPackage ./qmkFirmware.nix {
      # Pass the modules and main firmware here
      inherit (inputs)
        qmk-firmware
        qmk-chibios
        qmk-chibios-contrib
        qmk-googletest
        qmk-lufa
        qmk-vusb
        qmk-printf
        qmk-pico-sdk
        qmk-lvgl
        ;
    };

    # Config set
  in {

    # Enter the devshell with the qmk command, configured to liking
    devShell = pkgs.mkShell {

      # QMK environment variables, mostly need this repo and a full qmk_firmware
      QMK_HOME = qmkFirmware;
      QMK_FIRMWARE = qmkFirmware;
      KEYMAP = keymap;

      # Required packages for functioning here
      buildInputs = [
        qmkFirmware
        pkgs.qmk
      ];
      packages = [
        pkgs.qmk
      ];

      # Shell overrides
      shellHook = ''
        # Override QMK command to always use the config file from this flake
        alias qmk='${pkgs.qmk}/bin/qmk --config-file ${qmkConfig}'
      '';
    };
  });
}
