# Overview
A [project](http://emulator101.com/) for making an emulator for Intel 8080 microprocessor

# Useful Documents
- [System User's Manual](http://bitsavers.trailing-edge.com/components/intel/MCS80/98-153B_Intel_8080_Microcomputer_Systems_Users_Manual_197509.pdf)
- [Assembly Language Programming Manual](http://dunfield.classiccmp.org/r/8080asm.pdf)

## Basic information
- 8-bit processor (word size is 8 bits)
- predecessor: 8008, later influenced x86 architecture (8086 microprocessor)
- launched in 1974
- 16-bit address bus, 8-bit data bus
- 64KB memory (64 * 1024 = 2^16)

## Registers
- seven 8-bit registers: A, B, C, D, E, H, L
  -  A: primary 8-bit accumulator
  -  others can be used as three 16-bit register pairs (BC, DE, HL)
  -  HL: can be used as a 16-bit accumulator for some instructions
-  M (pseudo register): dereferenced memory lication pointed to by HL
- dedicated 16-bit SP register

## Flags
indicate the result of arithmetic/logical operations
1. Sign (S): if result < 0
2. Zero (Z): if result == 0
3. Parity (P): if # of (bit == 1) is even
4. Carry (C): if an addition resulted in a carry OR a subtraction required a borrow
5. Auxiliary Carry (AC): ?
* A accumulator + flags = Program Status Word (PSW)

