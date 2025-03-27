# btbench

For comparing different binary translators performance in [library wrapping](https://box86.org/2021/08/a-deep-dive-into-library-wrapping/) and translator JIT compilers such as box64 [DynaRec](https://box86.org/2021/07/inner-workings-a-high%e2%80%91level-view-of-box86-and-a-low%e2%80%91level-view-of-the-dynarec/), qemu [TCG](https://www.qemu.org/docs/master/devel/index-tcg.html) and [LATX translator](https://github.com/lat-opensource/lat/tree/master/target/i386/latx/translator).

## Workloads

@ptitSeb introduced [1](https://box86.org/2023/05/performances2022/)[2](https://archive.fosdem.org/2022/stands.fosdem.org/stands/box86/performances/) `7z`, `dav1d` and `glmark2` benchmarks. While `7z`, `dav1d` and `scimark4_c` workloads are able to compare translators JIT compilers performance. But `glmark2` mainly compares library wrapping performance. There are other benchmarks to compare translator compiler too, such as [scilab benchmark](https://help.scilab.org/bench_run.html).

## Usage

```
python3 btbench.py /your/path/translator
```

for example:
```
python3 btbench.py /usr/local/bin/box64
```
or
```
python3 btbench.py /usr/bin/latx-x86_64
```
