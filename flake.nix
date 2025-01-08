{
  description = "Flake for using qmk firmware";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-24.11";
    nixpkgs-unstable.url = "github:nixos/nixpkgs/nixos-24.11";
    flake-utils.url = "github:numtide/flake-utils";
    # QMK firmware main repo
    qmkFirmware = {
      url = "github:qmk/qmk_firmware";
      flake = false;
      submodules = true;
    };
  };

  outputs = {
    self,
    ...
  } @ inputs: inputs.flake-utils.lib.eachDefaultSystem (system:
  let
    # Generic pkgs import
    pkgs = inputs.nixpkgs.legacyPackages.${system};

    # Config settings for qmk, so this repo works as the qmk overlay
    qmkConfig = pkgs.writeTextFile {
      name = "qmk-config.ini";
      text = ''
        [user]
        overlay_dir = ${self}
      '';
    };

    # Default list of keyboards
    keyboards = [
      "crkbd"
    ];

    # Default user to be used in this qmk
    keymap = "sbp";

    # Config set
  in {

    # Build keyboard as packages!
    # build with `nix build '.<keyboard>?submodules=1'`
    # We use the same package template every keymap/keyboard combo
    packages = builtins.listToAttrs (builtins.map (
      kb: {
        name = kb;
        value = pkgs.stdenv.mkDerivation {
          name = kb;
          src = ./.;
          phases = [ "buildPhase" ];
          buildInputs = [
            pkgs.qmk
            inputs.qmk-firmware
          ];
          QMK_FIRMWARE = inputs.qmkFirmware;
          buildPhase = ''
            make -C $src BUILD_DIR=`pwd`/.build COPY=echo -j8 ${kb}:${keymap}
            mkdir $out
            cp -r .build/* $out/
          '';
        };
      }
    ) keyboards);

    # Or just enter devshell with the qmk executable ready; `nix develop`
    #
    # Build dir is taken as a param of `build` and `flash`,
    # e.g. to flash with the output of `nix build '.?submodules=1'` do `flash result`.
    devShell = pkgs.mkShell {

      # QMK environment variables, mostly need this repo and a full qmk_firmware
      QMK_HOME = inputs.qmk-firmware;
      QMK_FIRMWARE = inputs.qmk-firmware;
      KEYMAP = keymap;
      buildInputs = [
        pkgs.qmk
      ];
      packages = [
        pkgs.qmk
      ];
      shellHook = ''

        # Build and flash commands
        build() {
          BUILD_DIR=''${1:-.build}
          make -C . BUILD_DIR=$BUILD_DIR COPY=echo -j8 $KEYBOARD:$KEYMAP
        }
        flash() {
          BUILD_DIR=''${1:-.build}
          make -C . BUILD_DIR=$BUILD_DIR COPY=echo -j8 $KEYBOARD:$KEYMAP:flash
        }

        # Override QMK to always use the config file from this flake
        alias qmk='${pkgs.qmk}/bin/qmk --config-file ${qmkConfig}'
      '';
    };
  });
}
