with import <nixpkgs> {}; {
  beatwaveEnv = clangStdenv.mkDerivation {
    name = "beatwave";
    buildInputs = [ clangStdenv sfml cmake rtags doxygen ];
  };
}
