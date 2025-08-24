# Crkbd

Using [this](https://github.com/ItsWaffle/waffle_corne) Proton-C compatible PCB.

Applying the similar keymap to [@waffle](https://github.com/ItsWaffle/waffle_corne);
using their `crkbd:rev1:arm` build.

## Build

Build commands;

* `qmk flash -kb crkbd/rev1 -km batuhan -bl dfu-util-split-left`
* `qmk flash -kb crkbd/rev1 -km batuhan -bl dfu-util-split-right`
