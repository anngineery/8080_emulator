#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct ConditionCodes {
    uint8_t    z:1;
    uint8_t    s:1;
    uint8_t    p:1;
    uint8_t    cy:1;
    uint8_t    ac:1;    // Axiliary Carry is ignored, since I cannot test it
    uint8_t    pad:3;
} ConditionCodes;

typedef struct State8080 {
    uint8_t    a;
    uint8_t    b;
    uint8_t    c;
    uint8_t    d;
    uint8_t    e;
    uint8_t    h;
    uint8_t    l;
    uint16_t   sp;
    uint16_t   pc;
    uint8_t    *memory;
    struct     ConditionCodes   cc;
    uint8_t    int_enable;
} State8080;

uint8_t Parity(uint8_t data){
    ;
}

void UnimplementedInstruction(State8080* state) {
    //pc will have advanced one, so exit
    printf ("Error: Unimplemented instruction\n");
    exit(1);
   }

void Emulate8080Op(State8080* state) {
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode) {
        case 0x00: UnimplementedInstruction(state); break;
        case 0x01: UnimplementedInstruction(state); break;
        case 0x02: UnimplementedInstruction(state); break;
        case 0x03:  // INX B (rp is BC)
        {
            uint16_t value = (state->b) << 8 | (state->c);
            value++;
            state->c = value & 0xff;
            state->b = value >> 8;

            break;
        }

        case 0x04:  // INR B
        {
            uint8_t answer = state->b + 1;  // Store in 8 bits, bc we don't care about carry flag
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->b = answer;

            break;
        }

        case 0x05:  // DCR B
        {
            uint8_t answer = state->b - 1;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->b = answer;

            break;
        }


        case 0x06: UnimplementedInstruction(state); break;
        case 0x07: UnimplementedInstruction(state); break;
        case 0x08: UnimplementedInstruction(state); break;
        case 0x09:  // DAD B
        {
            uint16_t accumulator = (state->h<<8) | (state->l);
            uint16_t increment = (state->b<<8) | (state->c);
            uint32_t answer = accumulator + increment;
            state->cc.cy = (answer > 0xffff);
            state->l = answer & 0xff;
            state->h = answer >> 8;

            break;
        }

        case 0x0a: UnimplementedInstruction(state); break;
        case 0x0b:  // DCX B (rp is BC)
        {
            uint16_t value = (state->b) << 8 | (state->c);
            value--;
            state->c = value & 0xff;
            state->b = value >> 8;

            break;
        }

        case 0x0c:  // INR C
        {
            uint8_t answer = state->c + 1;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->c = answer;

            break;
        }

        case 0x0d:  // DCR C
        {
            uint8_t answer = state->c - 1;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->c = answer;

            break;
        }


        case 0x0e: UnimplementedInstruction(state); break;
        case 0x0f: UnimplementedInstruction(state); break;
        case 0x10: UnimplementedInstruction(state); break;
        case 0x11: UnimplementedInstruction(state); break;
        case 0x12: UnimplementedInstruction(state); break;
        case 0x13:  // INX D (rp is DE)
        {
            uint16_t value = (state->d) << 8 | (state->e);
            value++;
            state->e = value & 0xff;
            state->d = value >> 8;

            break;
        }

        case 0x14:  // INR D
        {
            uint8_t answer = state->d + 1;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->d = answer;

            break;
        }

        case 0x15:  // DCR D
        {
            uint8_t answer = state->d - 1;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->d = answer;

            break;
        }

        case 0x16: UnimplementedInstruction(state); break;
        case 0x17: UnimplementedInstruction(state); break;
        case 0x18: UnimplementedInstruction(state); break;
        case 0x19:  // DAD D
        {
            uint16_t accumulator = (state->h<<8) | (state->l);
            uint16_t increment = (state->d<<8) | (state->e);
            uint32_t answer = accumulator + increment;
            state->cc.cy = (answer > 0xffff);
            state->l = answer & 0xff;
            state->h = answer >> 8;

            break;
        }

        case 0x1a: UnimplementedInstruction(state); break;
        case 0x1b:  // DCX D (rp is DE)
        {
            uint16_t value = (state->d) << 8 | (state->e);
            value--;
            state->e = value & 0xff;
            state->d = value >> 8;

            break;
        }

        case 0x1c:  // INR E
        {
            uint8_t answer = state->e + 1;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->e = answer;

            break;
        }

        case 0x1d:  // DCR E
        {
            uint8_t answer = state->e - 1;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->e = answer;

            break;
        }

        case 0x1e: UnimplementedInstruction(state); break;
        case 0x1f: UnimplementedInstruction(state); break;
        case 0x20: UnimplementedInstruction(state); break;
        case 0x21: UnimplementedInstruction(state); break;
        case 0x22: UnimplementedInstruction(state); break;
        case 0x23:  // INX H (rp is HL)
        {
            uint16_t value = (state->h) << 8 | (state->l);
            value++;
            state->l = value & 0xff;
            state->h = value >> 8;

            break;
        }

        case 0x24:  // INR H
        {
            uint8_t answer = state->h + 1;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->h = answer;

            break;
        }

        case 0x25:  // DCR H
        {
            uint8_t answer = state->h - 1;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->h = answer;

            break;
        }

        case 0x26: UnimplementedInstruction(state); break;
        case 0x27: UnimplementedInstruction(state); break;
        case 0x28: UnimplementedInstruction(state); break;
        case 0x29:  // DAD H
        {
            uint16_t accumulator = (state->h<<8) | (state->l);
            uint32_t answer = accumulator << 1;
            state->cc.cy = (answer > 0xffff);
            state->l = answer & 0xff;
            state->h = answer >> 8;

            break;
        }

        case 0x2a: UnimplementedInstruction(state); break;
        case 0x2b:  // DCX H (rp is HL)
        {
            uint16_t value = (state->h) << 8 | (state->l);
            value--;
            state->l = value & 0xff;
            state->h = value >> 8;

            break;
        }

        case 0x2c:  // INR L
        {
            uint8_t answer = state->l + 1;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->l = answer;

            break;
        }

        case 0x2d:  // DCR L
        {
            uint8_t answer = state->l - 1;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->l = answer;

            break;
        }

        case 0x2e: UnimplementedInstruction(state); break;
        case 0x2f: UnimplementedInstruction(state); break;
        case 0x30: UnimplementedInstruction(state); break;
        case 0x31: UnimplementedInstruction(state); break;
        case 0x32: UnimplementedInstruction(state); break;
        case 0x33:  // INX SP
        {
            uint16_t value = state->sp + 1;
            state->sp = value;

            break;
        }

        case 0x34:  // INR M
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint8_t answer = state->memory[offset] + 1;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->memory[offset] = answer;

            break;
        }

        case 0x35:  // DCR M
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint8_t answer = state->memory[offset] - 1;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->memory[offset] = answer;

            break;
        }

        case 0x36: UnimplementedInstruction(state); break;
        case 0x37: UnimplementedInstruction(state); break;
        case 0x38: UnimplementedInstruction(state); break;
        case 0x39:  // DAD SP
        {
            uint16_t accumulator = (state->h<<8) | (state->l);
            uint32_t answer = accumulator + state->sp;
            state->cc.cy = (answer > 0xffff);
            state->l = answer & 0xff;
            state->h = answer >> 8;

            break;
        }

        case 0x3a: UnimplementedInstruction(state); break;
        case 0x3b:  // DCX SP
        {
            uint16_t value = state->sp - 1;
            state->sp = value;

            break;
        }

        case 0x3c:  // INR A
        {
            uint8_t answer = state->a + 1;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->a = answer;

            break;
        }

        case 0x3d:  // DCR A
        {
            uint8_t answer = state->a - 1;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->a = answer;

            break;
        }
        case 0x3e: UnimplementedInstruction(state); break;
        case 0x3f: UnimplementedInstruction(state); break;
        case 0x40: UnimplementedInstruction(state); break;
        case 0x41: UnimplementedInstruction(state); break;
        case 0x42: UnimplementedInstruction(state); break;
        case 0x43: UnimplementedInstruction(state); break;
        case 0x44: UnimplementedInstruction(state); break;
        case 0x45: UnimplementedInstruction(state); break;
        case 0x46: UnimplementedInstruction(state); break;
        case 0x47: UnimplementedInstruction(state); break;
        case 0x48: UnimplementedInstruction(state); break;
        case 0x49: UnimplementedInstruction(state); break;
        case 0x4a: UnimplementedInstruction(state); break;
        case 0x4b: UnimplementedInstruction(state); break;
        case 0x4c: UnimplementedInstruction(state); break;
        case 0x4d: UnimplementedInstruction(state); break;
        case 0x4e: UnimplementedInstruction(state); break;
        case 0x4f: UnimplementedInstruction(state); break;
        case 0x50: UnimplementedInstruction(state); break;
        case 0x51: UnimplementedInstruction(state); break;
        case 0x52: UnimplementedInstruction(state); break;
        case 0x53: UnimplementedInstruction(state); break;
        case 0x54: UnimplementedInstruction(state); break;
        case 0x55: UnimplementedInstruction(state); break;
        case 0x56: UnimplementedInstruction(state); break;
        case 0x57: UnimplementedInstruction(state); break;
        case 0x58: UnimplementedInstruction(state); break;
        case 0x59: UnimplementedInstruction(state); break;
        case 0x5a: UnimplementedInstruction(state); break;
        case 0x5b: UnimplementedInstruction(state); break;
        case 0x5c: UnimplementedInstruction(state); break;
        case 0x5d: UnimplementedInstruction(state); break;
        case 0x5e: UnimplementedInstruction(state); break;
        case 0x5f: UnimplementedInstruction(state); break;
        case 0x60: UnimplementedInstruction(state); break;
        case 0x61: UnimplementedInstruction(state); break;
        case 0x62: UnimplementedInstruction(state); break;
        case 0x63: UnimplementedInstruction(state); break;
        case 0x64: UnimplementedInstruction(state); break;
        case 0x65: UnimplementedInstruction(state); break;
        case 0x66: UnimplementedInstruction(state); break;
        case 0x67: UnimplementedInstruction(state); break;
        case 0x68: UnimplementedInstruction(state); break;
        case 0x69: UnimplementedInstruction(state); break;
        case 0x6a: UnimplementedInstruction(state); break;
        case 0x6b: UnimplementedInstruction(state); break;
        case 0x6c: UnimplementedInstruction(state); break;
        case 0x6d: UnimplementedInstruction(state); break;
        case 0x6e: UnimplementedInstruction(state); break;
        case 0x6f: UnimplementedInstruction(state); break;
        case 0x70: UnimplementedInstruction(state); break;
        case 0x71: UnimplementedInstruction(state); break;
        case 0x72: UnimplementedInstruction(state); break;
        case 0x73: UnimplementedInstruction(state); break;
        case 0x74: UnimplementedInstruction(state); break;
        case 0x75: UnimplementedInstruction(state); break;
        case 0x76: UnimplementedInstruction(state); break;
        case 0x77: UnimplementedInstruction(state); break;
        case 0x78: UnimplementedInstruction(state); break;
        case 0x79: UnimplementedInstruction(state); break;
        case 0x7a: UnimplementedInstruction(state); break;
        case 0x7b: UnimplementedInstruction(state); break;
        case 0x7c: UnimplementedInstruction(state); break;
        case 0x7d: UnimplementedInstruction(state); break;
        case 0x7e: UnimplementedInstruction(state); break;
        case 0x7f: UnimplementedInstruction(state); break;

        case 0x80:  // ADD B
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->b;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x81:  // ADD C
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->c;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x82:  // ADD D
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->d;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x83:  // ADD E
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->e;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x84:  // ADD H
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->h;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x85:  // ADD L
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->l;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x86:  // ADD M
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t answer = (uint16_t) state->a + state->memory[offset];
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x87:  // ADD A
        {
            uint16_t answer = ((uint16_t) state->a) << 1;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x88:  // ADC B
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->b + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x89:  // ADC C
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->c + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x8a:  // ADC D
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->d + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x8b:  // ADC E
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->e + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x8c:  // ADC H
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->h + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x8d:  // ADC L
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->l + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x8e:  // ADC M
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t answer = (uint16_t) state->a + state->memory[offset] + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x8f:  // ADC A
        {
            uint16_t answer = ((uint16_t) state->a << 1) + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x90:  // SUB B
        {
            uint16_t answer = (uint16_t) state->a - (uint16_t) state->b;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x91:  // SUB C
        {
            uint16_t answer = (uint16_t) state->a - (uint16_t) state->c;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x92:  // SUB D
        {
            uint16_t answer = (uint16_t) state->a - (uint16_t) state->d;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x93:  // SUB E
        {
            uint16_t answer = (uint16_t) state->a - (uint16_t) state->e;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x94:  // SUB H
        {
            uint16_t answer = (uint16_t) state->a - (uint16_t) state->h;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x95:  // SUB L
        {
            uint16_t answer = (uint16_t) state->a - (uint16_t) state->l;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x96:  // SUB M
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t answer = (uint16_t) state->a - state->memory[offset];
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x97:  // SUB A
        {
            uint16_t answer = (uint16_t) state->a - (uint16_t) state->a;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x98:  // SBB B
        {
            uint16_t answer = (uint16_t) state->a - (uint16_t) state->b - (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x99:  // SBB C
        {
            uint16_t answer = (uint16_t) state->a - (uint16_t) state->c - (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x9a:  // SBB D
        {
            uint16_t answer = (uint16_t) state->a - (uint16_t) state->d - (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x9b:  // SBB E
        {
            uint16_t answer = (uint16_t) state->a - (uint16_t) state->e - (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x9c:  // SBB H
        {
            uint16_t answer = (uint16_t) state->a - (uint16_t) state->h - (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x9d:  // SBB L
        {
            uint16_t answer = (uint16_t) state->a - (uint16_t) state->l - (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x9e:  // SBB M
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t answer = (uint16_t) state->a - state->memory[offset] - (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0x9f:  // SBB A
        {
            uint16_t answer = (uint16_t) state->a - (uint16_t) state->a - (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0xa0: UnimplementedInstruction(state); break;
        case 0xa1: UnimplementedInstruction(state); break;
        case 0xa2: UnimplementedInstruction(state); break;
        case 0xa3: UnimplementedInstruction(state); break;
        case 0xa4: UnimplementedInstruction(state); break;
        case 0xa5: UnimplementedInstruction(state); break;
        case 0xa6: UnimplementedInstruction(state); break;
        case 0xa7: UnimplementedInstruction(state); break;
        case 0xa8: UnimplementedInstruction(state); break;
        case 0xa9: UnimplementedInstruction(state); break;
        case 0xaa: UnimplementedInstruction(state); break;
        case 0xab: UnimplementedInstruction(state); break;
        case 0xac: UnimplementedInstruction(state); break;
        case 0xad: UnimplementedInstruction(state); break;
        case 0xae: UnimplementedInstruction(state); break;
        case 0xaf: UnimplementedInstruction(state); break;
        case 0xb0: UnimplementedInstruction(state); break;
        case 0xb1: UnimplementedInstruction(state); break;
        case 0xb2: UnimplementedInstruction(state); break;
        case 0xb3: UnimplementedInstruction(state); break;
        case 0xb4: UnimplementedInstruction(state); break;
        case 0xb5: UnimplementedInstruction(state); break;
        case 0xb6: UnimplementedInstruction(state); break;
        case 0xb7: UnimplementedInstruction(state); break;
        case 0xb8: UnimplementedInstruction(state); break;
        case 0xb9: UnimplementedInstruction(state); break;
        case 0xba: UnimplementedInstruction(state); break;
        case 0xbb: UnimplementedInstruction(state); break;
        case 0xbc: UnimplementedInstruction(state); break;
        case 0xbd: UnimplementedInstruction(state); break;
        case 0xbe: UnimplementedInstruction(state); break;
        case 0xbf: UnimplementedInstruction(state); break;
        case 0xc0: UnimplementedInstruction(state); break;
        case 0xc1: UnimplementedInstruction(state); break;
        case 0xc2: UnimplementedInstruction(state); break;
        case 0xc3: UnimplementedInstruction(state); break;
        case 0xc4: UnimplementedInstruction(state); break;
        case 0xc5: UnimplementedInstruction(state); break;

        case 0xc6:  // ADI D8 = ADD Immediate (1 byte)
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) opcode[1];
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0xc7: UnimplementedInstruction(state); break;
        case 0xc8: UnimplementedInstruction(state); break;
        case 0xc9: UnimplementedInstruction(state); break;
        case 0xca: UnimplementedInstruction(state); break;
        case 0xcb: UnimplementedInstruction(state); break;
        case 0xcc: UnimplementedInstruction(state); break;
        case 0xcd: UnimplementedInstruction(state); break;
        case 0xce:  // ACI D8 = ADD Immediate with Carry (1 byte)
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) opcode[1] + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer&0xff);
            state->a = answer & 0xff;

            break;
        }

        case 0xcf: UnimplementedInstruction(state); break;
        case 0xd0: UnimplementedInstruction(state); break;
        case 0xd1: UnimplementedInstruction(state); break;
        case 0xd2: UnimplementedInstruction(state); break;
        case 0xd3: UnimplementedInstruction(state); break;
        case 0xd4: UnimplementedInstruction(state); break;
        case 0xd5: UnimplementedInstruction(state); break;
        case 0xd6: UnimplementedInstruction(state); break;
        case 0xd7: UnimplementedInstruction(state); break;
        case 0xd8: UnimplementedInstruction(state); break;
        case 0xd9: UnimplementedInstruction(state); break;
        case 0xda: UnimplementedInstruction(state); break;
        case 0xdb: UnimplementedInstruction(state); break;
        case 0xdc: UnimplementedInstruction(state); break;
        case 0xdd: UnimplementedInstruction(state); break;
        case 0xde: UnimplementedInstruction(state); break;
        case 0xdf: UnimplementedInstruction(state); break;
        case 0xe0: UnimplementedInstruction(state); break;
        case 0xe1: UnimplementedInstruction(state); break;
        case 0xe2: UnimplementedInstruction(state); break;
        case 0xe3: UnimplementedInstruction(state); break;
        case 0xe4: UnimplementedInstruction(state); break;
        case 0xe5: UnimplementedInstruction(state); break;
        case 0xe6: UnimplementedInstruction(state); break;
        case 0xe7: UnimplementedInstruction(state); break;
        case 0xe8: UnimplementedInstruction(state); break;
        case 0xe9: UnimplementedInstruction(state); break;
        case 0xea: UnimplementedInstruction(state); break;
        case 0xeb: UnimplementedInstruction(state); break;
        case 0xec: UnimplementedInstruction(state); break;
        case 0xed: UnimplementedInstruction(state); break;
        case 0xee: UnimplementedInstruction(state); break;
        case 0xef: UnimplementedInstruction(state); break;
        case 0xf0: UnimplementedInstruction(state); break;
        case 0xf1: UnimplementedInstruction(state); break;
        case 0xf2: UnimplementedInstruction(state); break;
        case 0xf3: UnimplementedInstruction(state); break;
        case 0xf4: UnimplementedInstruction(state); break;
        case 0xf5: UnimplementedInstruction(state); break;
        case 0xf6: UnimplementedInstruction(state); break;
        case 0xf7: UnimplementedInstruction(state); break;
        case 0xf8: UnimplementedInstruction(state); break;
        case 0xf9: UnimplementedInstruction(state); break;
        case 0xfa: UnimplementedInstruction(state); break;
        case 0xfb: UnimplementedInstruction(state); break;
        case 0xfc: UnimplementedInstruction(state); break;
        case 0xfd: UnimplementedInstruction(state); break;
        case 0xfe: UnimplementedInstruction(state); break;
        case 0xff: UnimplementedInstruction(state); break;
    }
    state->pc+=1;  //for the opcode
}
