# RMatrix

C implementation of basic matrix operations using integer arithmetic

To install (after cloning):
```
$ cmake -S . -B build
$ make -C build && make test -C build
```
If you like what you see,
`sudo cmake --install .`

I've only tested the build, compilation, testing, and installation on my Mac. CMake is supposed to be cross-platform, but YMMV.

Update: I've been using this library to test calling native code from other languages, and took the plunge to get it to work on Windows. It's not easy, though, and still has some specific paths to it.

I wanted to minimize the additional tools I had to install in Windows. So CMake from Chocolatey was all I added. NMake is part of Visual Studio, so I used that in a Visual Studio Developer PowerShell window.

Running the tests will require some more messing around with the paths. I haven't taken the time to fully explore that.

There seems to be no standard Windows installation directory. If you don't specify it seems to try to go to `C:/Program Files (x86)`. I don't know how to get Admin privileges in a Visual Studio Developer PowerShell window, so with ChatGPT's help I modified the CMake command to prepend a directory I have write permissions to.

```
> mkdir build-shell
> cd build-shell
> cmake .. -G "NMake Makefiles" -DCMAKE_INSTALL_PREFIX=C:/Users/john.todd/local/rmatrix
> nmake
> nmake install
```

## Creation and destruction of RMatrices and querying their elements

When an RMatrix is created from an array of Rashunals, copies are made of the supplied values. You still need to manage them after RMatrix creation, but the RMatrix will be unchanged when you do so.

When an RMatrix is destroyed, both the elements and the matrix are destroyed.

Querying RMatrix elements creates copies of the elements. You are responsible for disposing of the copies.

## Comparing RMatrices

The RMatrix_cmp function returns an integer value. Unlike Rashunal's r_cmp or the usual interpretation of C's comparison functions, one should only infer that values different from 0 indicate non-equivalence. Since I'm not aware of a concept of matrices being greater or less than each other, there is no significance to the return value of RMatrix_cmp being less than or greater than 0 or to its magnitude.

## Mutating functions
The mutating functions RMatrix_set, RMatrix_row_mult, RMatrix_row_swap, and RMatrix_lc return newly-allocated RMatrices with all-new members. The old RMatrix and the new one should be freed appropriately.

## Linear Algebra
RMatrix_gelim returns a struct containing the inverse of the permutation matrix, the lower factor, the diagonal multiplier, and the upper multiplier. If the matrix is singular, the diagonal multiplier is null.
```text
Gauss_Factorization {
    pi;
    l;
    d;
    u;
}
```

## Memory checking
I develop on a Mac, which doesn't play well with Valgrind. I use a Valgrind Docker container to do my memory checking.
```text
$ docker run --rm -it \
  -v ~/workspace/rmatrix:/workspace/rmatrix \
  -v ~/workspace/rashunal:/workspace/rashunal \
  valgrind-env
% cd rmatrix
% mkdir leak
% cd leak
% cmake ..
% make && make test
```
The error log (Testing/Temporary/LastTest.log) is visible in my IDE, so I can fix problems that are identified.