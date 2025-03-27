#dav1d benchmark

dav1d is a transcoding application, heavily optimized for SIMD and make use of SSSE on x86 (or SSE4 if availble).
`PMULHRSW`, `PABSB`, `PABSW`, `PACKUSDW`, `PMINUW`, `PMAXSD`, `PMULLD`, `PBLENDW`, `PSRLW`, `PSUBUSB`, `PMINUB`, `PADDUSW`, `PMAXUB`, `PSRAD`, `PSUBSB`, `PSUBSW`, `PMINSW`, `PADDSB`, `PADDSW`, `PMAXSW` and `PMADDWD` opcodes optimization effect is obvious for [LoongArch](https://github.com/ptitSeb/box64/pull/2127):

|before                |after                  |                 |
|----------------------|-----------------------|-----------------|
|3.67/23.98 fps (0.15x)|89.06/23.98 fps (3.71x)|bigger is better |
|real	40m35.251s     |real	1m40.299s      |smaller is better|

Please download [Chimera-AV1-8bit-480x270-552kbps.ivf](http://dgql.org/~unlord/Netflix/Chimera/Chimera-AV1-8bit-480x270-552kbps.ivf) by youself.

```
export BOX64_LD_LIBRARY_PATH="/your/path/x86_64/sysroot"
/your/path/box64 ./dav1d /your/path/Chimera-AV1-8bit-480x270-552kbps.ivf
```
