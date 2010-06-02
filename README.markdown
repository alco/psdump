## Introduction

**psdump** is a command line utility which parses Photoshop files and
outputs their layer hierarchy as a text, JSON, or XML data. Position and
size of each layer are included in the output.

The program has been tested on the following systems:

* Mac OS X
* Windows XP, 7
* Linux (Ubuntu 9.10)

## Installing psdump

In order to start using **psdump** you will likely need to build it
from source. However, there are precompiled binaries for Mac OS X and
Windows family. They can be found on the [Downloads][downloads] page.

Once you've downloaded a binary release for your OS, unzip it and type
`psdump --help` in the terminal window.

  [downloads]: http://github.com/alco/psdump/downloads

## Building from source

### The UNIX way

Building from source is fairly simple on a *UNIX-like* system. You just
need to run `make` in the terminal window. The binary will appear in a
newly created 'build' directory. _(If you are running some kind of
minimalistic Linux distribution, you may need to additionally install
g++.)_

You can also run `make test` to run the test-suite and `make tidyup` to
remove intermediate object files. _(If you don't have python
installed, run `make shtest` instead of `make test`.)_

### Instructions for Windows users

To build from source on *Windows* there are several options.

The first one is to use [MinGW][mingw] with [MSYS][msys]. With those
tools installed, building is as easy as typing `mingw32-make` (or a
similar command) in the MSYS terminal window.

Another way to build **psdump** is using [Cygwin][cygwin]. With 'g++'
and 'make' packages installed, you just need to run `make` in the
Cygwin-bash.
_**Important notice**. If you build psdump using Cygwin, it won't work
without cygwin1.dll._

Lastly, a Microsoft compiler can be used to build from source. You will
find a Visual Studio project file in the 'vcproj' directory. This file
has been created in MS Visual Studio 2005 (version 9).

  [mingw]: http://www.mingw.org "MinGW homepage"
  [msys]: http://www.mingw.org/wiki/MSYS "MSYS wiki page"
  [cygwin]: http://www.cygwin.com "Cygwin homepage"

## Dependencies

To parse Photoshop files, **libpsd** is used. You don't need to download
it separately since its source code is already included with **psdump** and
it hasn't changed since, I guess, 2007. You may visit its project page
on [SourceForge.net][libpsd].

Apart from **libpsd**, there are no other requirements to be able to
successfully build **psdump** from source.

  [libpsd]: http://sourceforge.net/projects/libpsd/ "libpsd page at SourceForge.net"

## Development

Feedback, feature requests, and code reviews are most welcome! Please
let me know about your experience using **psdump**.

It has been designed in such a way that makes it easy to add more output
formats and even to parse other hierarchical files, not just Photoshop
ones.

The following improvements are expected to be introduced in the nearest
future:

* provide more detailed documentation on adding new features
* build and test on as many platforms as possible (your help will be
appreciated)
