# StupidSat: the Stupid Sat solver #

## Overview ##

This is the git repository for StupidSat, a SAT solver which provides
the same interface as for MiniSat, but implemented in the most naive
way possible (cycling through every possible value).

On top of this is a swig interface offering an interface to
StupidSat. The code is uncommented, but should be pretty
self-explanatory.

This code comes with no guarentees of correctness, use at your own
risk!

To compile, on a unix system type

make

And to build the python bindings

make pysat

The former requires clang++ version 4.8 or higher. The latter
additionally requires swig version 3.0 and pyton version 2.7
