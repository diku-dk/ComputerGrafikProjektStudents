let
  pkgs = import (builtins.fetchGit {
    url = "https://github.com/NixOS/nixpkgs/";
    rev = "931ab058daa7e4cd539533963f95e2bb0dbd41e6";
  }) { };
in
pkgs.stdenv.mkDerivation {
  name = "env";
  nativeBuildInputs = [ pkgs.cmake ];
  buildInputs = with pkgs; [
    libGLU
    glew
    glm
    glfw
  ];
}
