{
  stdenv,
  qmk-firmware,
  qmk-chibios,
  qmk-chibios-contrib,
  qmk-googletest,
  qmk-lufa,
  qmk-vusb,
  qmk-printf,
  qmk-pico-sdk,
  qmk-lvgl,
  rsync,
  ...
}: stdenv.mkDerivation {
  name = "qmkFirmware";
  src = qmk-firmware;
  phases = [ "unpackPhase" "installPhase" ];
  buildInputs = [ rsync ];
  installPhase = ''
    # Copy full repo to output directory
    mkdir --parents $out
    rsync --archive $src/ $out
    # Also do the same with modules
    mkdir --parents $out/lib/chibios
    rsync --archive ${qmk-chibios}/ $out/lib/chibios/
    mkdir --parents $out/lib/chibios-contrib
    rsync --archive ${qmk-chibios-contrib}/ $out/lib/chibios-contrib/
    mkdir --parents $out/lib/googletest
    rsync --archive ${qmk-googletest}/ $out/lib/googletest/
    mkdir --parents $out/lib/lufa
    rsync --archive ${qmk-lufa}/ $out/lib/lufa/
    mkdir --parents $out/lib/lvgl
    rsync --archive ${qmk-lvgl}/ $out/lib/lvgl/
    mkdir --parents $out/lib/pico-sdk
    rsync --archive ${qmk-pico-sdk}/ $out/lib/pico-sdk/
    mkdir --parents $out/lib/printf
    rsync --archive ${qmk-printf}/ $out/lib/pico-sdk/
    mkdir --parents $out/lib/vusb
    rsync --archive ${qmk-vusb}/ $out/lib/vusb/
  '';
}
