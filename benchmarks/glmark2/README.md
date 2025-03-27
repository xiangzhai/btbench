#glmark2 benchmark

`glmark2` is a program to test OpenGL speed.
More [library wrapping](https://box86.org/2021/08/a-deep-dive-into-library-wrapping/) AKA [KZT](https://github.com/lat-opensource/lat/tree/master/target/i386/latx/context) optimization effect is obvious.

```
export BOX64_LD_LIBRARY_PATH="/your/path/x86_64/sysroot"
/your/path/box64 ./bin/glmark2 --data-path ./share/glmark2
```
