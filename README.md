[![Build Status](https://travis-ci.org/rexim/beatwave.svg?branch=master)](https://travis-ci.org/rexim/beatwave)

# Beatwave #

Musical Puzzle Game

![screenshot](http://i.imgur.com/somxQOU.png)

## Building ##

### Linux ###

See general build instructions for Linux in the file `.travis.yml`
inside of the Beatwave source directory.

You will need C++11-compatible compiler (GCC or Clang), [CMake] and
[SFML].

Below is an example of building Beatwave on [NixOS Linux]. Feel free
to add instructions for any other distributions.

#### Building and Usage on NixOS ####

    $ nix-shell
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..
    $ ./build/beatwave

# License #

Copyright (c) 2016 Alexey Kutepov a.k.a. rexim

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

[CMake]: https://cmake.org/
[SFML]: http://www.sfml-dev.org/
[NixOS Linux]: https://nixos.org/
