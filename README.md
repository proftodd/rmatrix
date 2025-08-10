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

## Comparing RMatrices

The RMatrix_cmp function returns an integer value. Unlike Rashunal's r_cmp or the usual interpretation of C's comparison functions, one should only infer that values different from 0 indicate non-equivalence. Since I'm not aware of a concept of matrices being greater or less than each other, there is no significance to the return value of RMatrix_cmp being less than or greater than 0 or to its magnitude.

## Mutating functions
The mutating functions RMatrix_set, RMatrix_row_mult, RMatrix_row_swap, and RMatrix_lc return newly-allocated RMatrices with all-new members. The old RMatrix and the new one should be freed appropriately.
