# Overview
A [project](http://emulator101.com/) for making an emulator for Intel 8080 microprocessor

# Useful Documents
- [System User's Manual](http://bitsavers.trailing-edge.com/components/intel/MCS80/98-153B_Intel_8080_Microcomputer_Systems_Users_Manual_197509.pdf)
- [Assembly Language Programming Manual](http://dunfield.classiccmp.org/r/8080asm.pdf)

# Some Conventions to Note
In assembly,
- # : indicates a literal number (immediate value)  `LXI SP, #$2400 // set SP to 0x2400`
- (): indicates a memory location `(HL) means the memory location pointed by HL register pair`
- $: denote a hex number `CALL $01e6  // same as CALL 0x01e6` 

https://academic-accelerator.com/encyclopedia/intel-8080
## Basic information
- 8-bit processor (word size is 8 bits)
- predecessor: 8008, later influenced x86 architecture (8086 microprocessor)
- launched in 1974
- 16-bit address bus, 8-bit data bus
- 64KB memory (64 * 1024 = 2^16)
- little endian (LSB goes first in the memory)

## Registers
- seven 8-bit registers: A, B, C, D, E, H, L
  -  A: primary 8-bit accumulator
  -  others can be used as three 16-bit register pairs (BC, DE, HL)
  -  HL: can be used as a 16-bit accumulator for some instructions
-  M (pseudo register): dereferenced memory lication pointed to by HL
- dedicated 16-bit SP register

## Flags (Condition Code)
indicate the result of arithmetic/logical operations. Used for conditional branching.
1. Sign (S): if result < 0
2. Zero (Z): if result == 0
3. Parity (P): if # of (bit == 1) is even
4. Carry (CY): if an addition resulted in a carry OR a subtraction required a borrow
5. Auxiliary Carry (AC): indicates the carry-out of bit 3. It exists only for the DAA instruction, which is not used in Spade Invaders. So it will be ignored in this project
* A (accumulator) + flags = Program Status Word (PSW)

## Instructions
### Arithmetic
Often involve A register, the accumualtor. In this case, A is one of the operands and where the result gets stored.
Some instructions affects flags and some not. See data book to see which instruction affects which flags
3 different formats:
1. Register
```
// ADD <register>
A = A + <register>
```
2. Immediate
```
// ADI byte
A = A + byte after opcode
```
3. Memory
```
// use HL register pair as a pointer to a memory location
// ADD M
A = A + MEM[HL]
```
What other instructions under this category are there?
- add (/w or /wo carry)
- subtract (/w or /wo carry)
- increment/decrement register pair or a register
- double add (aka HL = HL + another register pair)

*observation: `X` in opcode means register pair; `R` means a single register

### Branching
2 reasons to branch instead of execute the subsequent instruction
1. (conditonal or unconditional) jump - jump to a specific memory location based on flags
2. call - calling a subroutine; In a way, I think calling a subroutine is like executing an unconditional jump + extra chores (saving the caller's state in a frame) ---> TODO: link to Week 8 of Nand2Tetris