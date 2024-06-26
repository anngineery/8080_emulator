#ifndef EMULATOR_H
#define EMULATOR_H
#include <stdint.h>
typedef struct ConditionCodes {
    uint8_t    z:1;
    uint8_t    s:1;     // set if negative
    uint8_t    p:1;     // set if even
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
    uint8_t    *memory; // each memory location holds 8-bit data
    struct     ConditionCodes   cc;
    uint8_t    int_enable;
} State8080;

uint8_t parity(uint8_t data, uint8_t numBits);
void Emulate8080Op(State8080* state);
void UnimplementedInstruction(State8080* state); 
#endif
