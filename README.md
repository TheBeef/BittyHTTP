# Introduction

Bitty HTTP is a small lightweight web server designed be used in small microcontrollers, but powerful enough to be used with large embedded processors and even embedded into larger programs.

If you are looking for small, simple, easy to use HTTP server with minimal dependencies then you have found what you are looking for.

Bitty HTTP is licensed under the MIT License (see License.txt). This means you are free to use this software however you want as long as you keep the copyright notice.

# Web site

You can access the web site for Bitty HTTP at http://bittyhttp.com and the documentation at http://bittyhttp.com/Development.html

The web site is running under Bitty HTTP as an example of what Bitty HTTP can do.

# Build and run

## Prerequisite for building

Bitty HTTP is written in C and only requires the C standard library to compile and run.

**HOWEVER** Bitty HTTP does not use standard sockets calls, instead it calls functions that you provide that will
access your sockets.  This allows you to use non standard sockets.

Examples of using Posix/Berkeley and Winsock are provided (as src/SocketsCon.c for Posix, and src/SocketsConWin.c for Winsock).

You must also have GCC or some other C99 compiler.

The examples have been written for Linux with GCC.

## Steps for building

There aren't any makefiles provided, but instead simple 1 line scripts (for the examples).

The core is all in one file named `WebServer.c`.  The sockets wrapper is in `SocketsCon.c`.  Most of the examples include a standard `main.c` and a `FileServer.c` that handles what files will be served.

So to compile a basic server (where you have copied the needed files into your own directory):

`gcc main.c SocketsCon.c FileServer.c WebServer.c -o example.exe`

is all you need.

### Windows
For Windows a simple 1 line bat file is included (for the examples).

The core is all in one file named `WebServer.c`.  The sockets wrapper is in `SocketsConWin.c`.  Most of the examples include a standard `main.c` and a `FileServer.c` that handles what files will be served.

You will also need to install a GCC version for window (mingw for example) and have it in your path.

So to compile a basic server under Windows:

`gcc main.c SocketsCon.c FileServer.c WebServer.c -o example.exe -lws2_32`

is all you need.

The examples should work under Visual Studio however I have not tried it as I don't really use Windows.

### Examples
The examples include a build.sh (and build.bat for Windows) for building.  Just cd into the directory and run it (note for Windows you must have a Windows gcc installed in the path (mingw)
