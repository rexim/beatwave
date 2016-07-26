with import <nixpkgs> {}; {
  beatwaveEnv = stdenv.mkDerivation {
    name = "beatwave";
    buildInputs = [ stdenv sfml cmake ];
  };
}
