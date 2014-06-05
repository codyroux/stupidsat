# StupidSat: the Stupid Sat solver #

## Overview ##

This is the git repository for StupidSat, a SAT solver which provides
the same interface as for MiniSat, but implemented in the most naive
way possible (cycling through every possible value).

On top of this is a [swig][swig] interface offering an interface to
StupidSat. The code is uncommented, but should be pretty
self-explanatory.

This code comes with no guarentees of correctness, use at your own
risk!

To compile and build the python bindings on a Linux or OSX system,
type:

```
mkdir build
cd build
cmake ../
make
```

It requires C++ compiler ([g++ (>= 4.6.4)][gcc] or [clang++ (>= 3.3)][clang]), 
[swig(>= 2.0)][swig], and [python(>= 2.7)][python].

[gcc]: https://gcc.gnu.org
[clang]: http://clang.llvm.org
[swig]: http://www.swig.org
[python]: https://www.python.org
