with import <nixpkgs> {}; {
  beatwaveEnv = clangStdenv.mkDerivation {
    name = "beatwave";
    buildInputs = [ clangStdenv sfml cmake rtags doxygen pugixml ];
    CTEST_OUTPUT_ON_FAILURE = 1;
  };
}
