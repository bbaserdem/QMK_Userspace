{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    qmk
    qmk_hid
    
    # Basic utilities
    git
    gnumake
    gcc
    python3
  ];

  shellHook = ''
    echo "QMK userspace development environment"
    echo "Available tools: qmk, qmk_hid"
  '';
}