## Introduction

**psdump** is a command line utility which parses Photoshop files and
outputs their layer hierarchy as a text, JSON, or XML data. Position and
size of each layer are included in the output.

The program has been tested on the following systems:

* Mac OS X
* Windows XP, 7

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
need to run `make` in the terminal window. The binary will appear in
a newly created 'build' directory.

You can also run `make test` to run the test-suite
and `make tidyup` to remove intermediate object files.

### Instructions for Windows users

To build from source on *Windows* you have two options.

The first one is to use [MinGW][mingw] with [Cygwin][cygwin]. With those
tools installed, building is as easy as typing `mingw32-make` (or a
similar command) in the Cygwin terminal window. _(There is also a
Cygwin-like environment called MSYS which supplements MinGW. However,
I haven't tested it.)_

Another way to build the utility is using Microsoft compiler. You
will find a Visual Studio project file in the 'vcproj' directory. This
file has been created in MS Visual Studio 2005 (version 9).

  [mingw]: http://www.mingw.org "MinGW homepage"
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
* build and test on as many platforms as possible (Linux is the first
priority here)
