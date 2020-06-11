# My readelf

# Step 0 : open elf file read header

- On linux you can use mmap(3) to read you file.

# Step 1 : print section

```
$ readelf -x .rodata hello_world.do | head

Hex dump of section '.rodata':
  0x00000000 48656c6c 6f20776f 726c6400          Hello world.

```

## Bonus : Ou est ma string ?

```
$ gcc -c -O3 hello_world.c
$ readelf -x .rodata hello_world.o
readelf: Warning: Section '.rodata' was not dumped because it does not exist!
```

# Step 2 : print symbol

```
$ readelf -s /usr/lib/libm.so.6 | grep cosf
    19: 0000000000066db0   125 FUNC    WEAK   DEFAULT   16 ccosf128@@GLIBC_2.26
    68: 0000000000047cd0    46 IFUNC   WEAK   DEFAULT   16 cosf32@@GLIBC_2.27
    75: 000000000001c340   554 FUNC    WEAK   DEFAULT   16 sincosf64x@@GLIBC_2.27
    85: 0000000000042bb0   722 FUNC    GLOBAL DEFAULT   16 __acosf_finite@GLIBC_2.15
   165: 0000000000034af0    77 IFUNC   WEAK   DEFAULT   16 cosf64@@GLIBC_2.27
   180: 000000000003dc50   311 FUNC    WEAK   DEFAULT   16 cacosf32x@@GLIBC_2.27
   241: 000000000005e390   344 FUNC    WEAK   DEFAULT   16 cosf128@@GLIBC_2.26
   303: 000000000003df80    29 FUNC    WEAK   DEFAULT   16 ccosf32x@@GLIBC_2.27
   340: 0000000000049930    46 IFUNC   WEAK   DEFAULT   16 sincosf@@GLIBC_2.2.5
   374: 0000000000010140    96 FUNC    WEAK   DEFAULT   16 acosf64x@@GLIBC_2.27
   477: 0000000000015220    65 FUNC    WEAK   DEFAULT   16 acosf32@@GLIBC_2.27
   508: 0000000000061dc0   468 FUNC    WEAK   DEFAULT   16 sincosf128@@GLIBC_2.26
   532: 0000000000034af0    77 IFUNC   WEAK   DEFAULT   16 cosf32x@@GLIBC_2.27
   538: 0000000000015220    65 FUNC    WEAK   DEFAULT   16 acosf@@GLIBC_2.2.5
   572: 000000000004b380   367 FUNC    WEAK   DEFAULT   16 cacosf@@GLIBC_2.2.5
   582: 000000000001f2e0   368 FUNC    WEAK   DEFAULT   16 cacosf64x@@GLIBC_2.27
   583: 000000000004b740    52 FUNC    WEAK   DEFAULT   16 ccosf32@@GLIBC_2.27
   587: 00000000000119c0    66 FUNC    WEAK   DEFAULT   16 acosf64@@GLIBC_2.27
   596: 0000000000049930    46 IFUNC   WEAK   DEFAULT   16 sincosf32@@GLIBC_2.27
   683: 000000000001f710    27 FUNC    WEAK   DEFAULT   16 ccosf64x@@GLIBC_2.27
   691: 000000000003df80    29 FUNC    WEAK   DEFAULT   16 ccosf64@@GLIBC_2.27
   707: 000000000003a870  2639 FUNC    WEAK   DEFAULT   16 sincosf64@@GLIBC_2.27
   715: 000000000004b740    52 FUNC    WEAK   DEFAULT   16 ccosf@@GLIBC_2.2.5
   783: 000000000003a870  2639 FUNC    WEAK   DEFAULT   16 sincosf32x@@GLIBC_2.27
   802: 000000000006e420   116 FUNC    WEAK   DEFAULT   16 acosf128@@GLIBC_2.26
   870: 0000000000047cd0    46 IFUNC   WEAK   DEFAULT   16 cosf@@GLIBC_2.2.5
   926: 000000000001a9c0   348 FUNC    WEAK   DEFAULT   16 cosf64x@@GLIBC_2.27
   960: 000000000004b380   367 FUNC    WEAK   DEFAULT   16 cacosf32@@GLIBC_2.27
  1015: 0000000000066710   664 FUNC    WEAK   DEFAULT   16 cacosf128@@GLIBC_2.26
  1047: 000000000004fe60  2726 FUNC    GLOBAL DEFAULT   16 __acosf128_finite@GLIBC_2.26
  1072: 000000000003dc50   311 FUNC    WEAK   DEFAULT   16 cacosf64@@GLIBC_2.27
  1091: 00000000000119c0    66 FUNC    WEAK   DEFAULT   16 acosf32x@@GLIBC_2.27
```

# Step 3 : Print elf to hex

- Learn about the hex format https://en.wikipedia.org/wiki/Intel_HEX
- use your elf library to write a minimal objcopy

```
objcopy -O ihex input.elf output.hex
```

# Bonus stage

Use your library to patch the bomb binary, and diffuse the bomb.

```
$ ./bomb
Welcome to my fiendish little bomb. You have 6 phases with
which to blow yourself up. Have a nice day!
test

BOOM!!!
The bomb has blown up.

$ make patch-bomb
$ ./patch-bomb
$ ./bomb-patched
Welcome to my fiendish little bomb. You have 6 phases with
which to blow yourself up. Have a nice day!
Phase 1 defused. How about the next one?
...
```
