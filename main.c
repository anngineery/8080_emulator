#include <stdio.h>
#include <stdlib.h>
#include "emulator.h"
#include "disassembler.h"

int main(int argc, char *argv[]) {

	FILE* f = fopen(argv[1], "rb");

	if (f){
		int offset = 0;

		// Determine the size of file
		fseek(f, 0, SEEK_END);
		long fsize = ftell(f);
		fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

		// Read file into a buffer and add the null terminator
		char *code = malloc(fsize + 1);
		fread(code, 1, fsize, f);
		fclose(f);
		code[fsize] = 0;

        // Create a State object
        struct ConditionCodes cc = {0, 0, 0, 0, 0, 0};
        struct State8080 state = {0, 0, 0, 0, 0, 0, 0, 0xf000, offset, code, cc, 0};
		while (offset < fsize){
			offset += Disassemble8080Op(state.memory, state.pc);
            Emulate8080Op(&state);
            //printf("offset: %d, pc: %d", offset, state.pc);
            state.pc = offset;
		}
	}
	else{
		printf("File pointer is null");
	}


}
