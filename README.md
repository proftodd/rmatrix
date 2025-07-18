# RMatrix

C implementation of basic matrix operations using integer arithmetic

To install (after cloning):
```
$ cmake -S . -B build
$ make -C build && make test -C build
```

I've only tested the build, compilation, testing, and installation on my Mac. CMake is supposed to be cross-platform, but YMMV.

## Creation and destruction of RMatrices and querying their elements

When an RMatrix is created from an array of Rashunals, copies are made of the supplied values. You still need to manage them after RMatrix creation, but the RMatrix will be unchanged when you do so.

When an RMatrix is destroyed, both the elements and the matrix are destroyed.

Querying RMatrix elements creates copies of the elements. You are responsible for disposing of the copies.
