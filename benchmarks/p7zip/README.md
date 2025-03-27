# 7z benchmark

`AESIMC`, `AESENC`, `AESENCLAST`, `AESDEC` and `AESDECLAST` opcodes optimization effect is obvious for AArch64 due to A64 Cryptographic instructions, but AES instructions are not availble for RISCV or LoongArch, so the slow path (jump to native runtime) optimization effect is not obvious for [LoongArch](https://github.com/ptitSeb/box64/pull/2122).

```
/your/path/box64 ./7z b
/your/path/box64 ./7z b -mm=* -mmt=*
```

Please read [b (Benchmark) command](https://7-zip.opensource.jp/chm/cmdline/commands/bench.htm) for more details.
