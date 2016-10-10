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

#### Building and Run ####

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..
    $ ./build/beatwave

#### Unit Tests ####

First, build the project. Then

    $ cd build
    $ ctest

#### NixOS Development Environment ####

If you're a happy user of [NixOS] linux distribution, we have a
special `default.nix` file for you, which describes the development
environment. You can enter the environment by `$ nix-shell` at the
root of the project.

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
[NixOS]: https://nixos.org/
