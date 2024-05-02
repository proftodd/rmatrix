# RMatrix

C implementation of basic matrix operations using integer arithmetic

To install (after cloning):
```
$ mkdir build
$ cd build
$ cmake .. -DRASHUNAL_LIB=<header location> -DRASHUNAL_INCLUDE_DIR=<Rashunal library location>
$ make && make test
```

For me, on my laptop, `RASHUNAL_LIB=/usr/local/lib/librashunal.dylib` and `RASHUNAL_INCLUDE_DIR=/usr/local/include`
If you like what you see,
`sudo make install`

I've only tested the build, compilation, testing, and installation on my Mac. CMake is supposed to be cross-platform, but YMMV.