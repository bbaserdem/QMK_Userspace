# QMK Claude Description

This is QMK configuration.
The way that this code works is;

- This is an overlay, forked from https://github.com/qmk/qmk_userspace
- This repo overlays, and uses, https://github.com/qmk/qmk_firmware ,
  which is also available as a submodule `@qmk_firmware`.
- Firmware is built using the `qmk` commands.
- Project guidelines are provided in `@.editorconfig`
- Dev environment is set at `@.envrc` and `@flake.nix`

## Guidelines

- NEVER modify any file in the `@qmk_firmware` directory, it's a submodule.
  You can read it, but never change any files there.
- Code must be kept modular, if something is to be reused across keyboards,
  it should be available in the user directory at `@users/batuhan`.
  The old user directory at `@users/sbp` are meant to be referenced,
  and not edited.
- Keep the `@.gitignore` file formatted and well documented.
  When adding features that creates files that shouldn't be checked out,
  add them to the gitignore.
- Each keyboards' configuration lies in `@keyboard` subdirectory.
- Mimicking QMK guidelines, the userspace uses the `_user` type functions of qmk.
  It exposes `_keymap` type weakly defined functions to override behavior on keymap level.
- The codebase is in C. Everything should be implemented in it.
- External scripting should be made in python.
  Scripts should be runnable with `uv run`.
  Dependencies should be declared using inline metadata. Example;
  
```python
#!/usr/bin/env -S uv run --script
#
# /// script
# dependencies = [
#   "requests<3",
#   "rich",
# ]
# ///

import requests
from rich.pretty import pprint

resp = requests.get("https://peps.python.org/api/peps.json")
data = resp.json()
pprint([(k, v["title"]) for k, v in data.items()][:10])
```

## Documentation

- QMK documentation is available at `@qmk_firmware/docs`
- The documentation is very long, when working on a feature first identify the relevant doc file,
  then read that doc file before starting implementing a feature.
