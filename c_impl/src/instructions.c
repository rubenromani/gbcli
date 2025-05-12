#include "instructions.h"
#include "instruction_set.h"

#include <stdio.h>

const struct instruction instructions[N_INSTRUCTIONS] = {
        [NOP] = {INS_TYPE_MISC, {INS_SIZE_NONE, INS_ADDR_NONE, INS_REG_NONE}, {INS_SIZE_NONE, INS_ADDR_NONE, INS_REG_NONE}, 1, INS_COND_NONE},
        [LD_BC_U16] = {INS_TYPE_MISC, {INS_SIZE_NONE, INS_ADDR_NONE, INS_REG_NONE}, {INS_SIZE_NONE, INS_ADDR_NONE, INS_REG_NONE}, 1, INS_COND_NONE},
        [LD_IND_BC_A] = {INS_TYPE_MISC, {INS_SIZE_NONE, INS_ADDR_NONE, INS_REG_NONE}, {INS_SIZE_NONE, INS_ADDR_NONE, INS_REG_NONE}, 1, INS_COND_NONE}
};

struct instruction get_instruction(uint8_t opcode)
{
        return instructions[NOP];
}

int main()
{
        printf("Hello from instructions.c\n");
        return 0;
}
