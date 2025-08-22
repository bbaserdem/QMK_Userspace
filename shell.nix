{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell {
  buildInputs = with pkgs; [
    qmk
    qmk_hid

    # Basic utilities
    git
    gnumake
    gcc
    python3

    # AI utils
    pnpm
    nodejs-slim
    uv
  ];

  shellHook = ''
    echo "QMK userspace development environment"
    echo "Available tools: qmk, qmk_hid"
  '';
}
