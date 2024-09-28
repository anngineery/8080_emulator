/*
 * 8080 has 16 address pins. Address 0 - 0xffff.
 * Memory map of Spade Invader
 * ROM = address 0
 * 0x0000-0x07ff: invaders.h
 * 0x0800-0x0fff: invaders.g
 * 0x1000-0x17ff: invaders.f
 * 0x1800-0x1fff: invaders.e
 *
 * RAM = address 0x2000 (8k in size)
 * 0x2000-0x23ff: work RAM
 * 0x2400-0x3fff: video ram
 * 0x4000-      : RAM mirror
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "emulator.h"
#include "disassembler.h"

void loadROM(uint8_t *memory, FILE* instructions){
    long fsize;

	// move the file position indicator to EOF to determine the size
	fseek(instructions, 0, SEEK_END);
	fsize = ftell(instructions);
    
    // bring the file position indicator to the beginning of the file again
	fseek(instructions, 0, SEEK_SET); 

	// Read file into a buffer and add the null terminator
	fread(memory, 1, fsize, instructions);
	memory[fsize] = 0;
}

State8080* initState(uint8_t* memory){
    State8080 *state = (State8080 *)calloc(1, sizeof(State8080)); // init to 0
    state->sp = 0x2000;
    state->memory = memory;

    return state;
}

void printState(State8080 state){
    printf("A $%02x B $%02x C $%02x D $%02x E $%02x H $%02x L $%02x SP %04x\n", state.a, state.b, state.c, state.d, state.e, state.h, state.l, state.sp); 
}

int main(int argc, char *argv[]) {
    bool debug = true;
    uint8_t limit = 50;
    uint8_t ctr = 0;
	FILE* f = fopen(argv[1], "rb");

	if (!f){
		printf("File pointer is null");
    }

    uint8_t *memory = (uint8_t *)malloc(0x10000);    // 64k in size, holds 8-bit data
    State8080 *state8080;

    loadROM(memory, f);
	fclose(f);
    state8080 = initState(memory);

	while (true){
		Disassemble8080Op(state8080->memory, state8080->pc);
        Emulate8080Op(state8080);
        printState(*state8080);

        if (debug && ctr > limit)   break;
        ctr++;
    }
}
