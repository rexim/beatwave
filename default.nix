with import <nixpkgs> {}; {
  beatwaveEnv = clangStdenv.mkDerivation {
    name = "beatwave";
    buildInputs = [ clangStdenv sfml cmake rtags doxygen ];
    CTEST_OUTPUT_ON_FAILURE = 1;
  };
}
