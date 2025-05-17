#include "instructions.h"
#include "instruction_set.h"

#include <stdio.h>

const struct instruction instructions[N_INSTRUCTIONS] = {
        [NOP] = {NOP, INS_TYPE_MISC, {INS_SIZE_NONE, INS_ADDR_NONE, INS_REG_NONE}, {INS_SIZE_NONE, INS_ADDR_NONE, INS_REG_NONE}, 1, INS_COND_NONE},
        [LD_BC_U16] = {LD_BC_U16, INS_TYPE_MISC, {INS_SIZE_NONE, INS_ADDR_NONE, INS_REG_NONE}, {INS_SIZE_NONE, INS_ADDR_NONE, INS_REG_NONE}, 3, INS_COND_NONE},
        [LD_IND_BC_A] = {LD_IND_BC_A, INS_TYPE_MISC, {INS_SIZE_NONE, INS_ADDR_NONE, INS_REG_NONE}, {INS_SIZE_NONE, INS_ADDR_NONE, INS_REG_NONE}, 1, INS_COND_NONE},
        [INC_BC] = {INC_BC, INS_TYPE_INCDEC, {INS_SIZE_BIT16, INS_ADDR_REG, INS_REG_BC}, {INS_SIZE_NONE, INS_ADDR_NONE, INS_REG_NONE}, 2, INS_COND_NONE},
        [INC_B] = {INC_B, INS_TYPE_INCDEC, {INS_SIZE_BIT8, INS_ADDR_REG, INS_REG_B}, {INS_SIZE_NONE, INS_ADDR_NONE, INS_REG_NONE}, 1, INS_COND_NONE},
        [DEC_B] = {DEC_B, INS_TYPE_INCDEC, {INS_SIZE_BIT8, INS_ADDR_REG, INS_REG_B}, {INS_SIZE_NONE, INS_ADDR_NONE, INS_REG_NONE}, 1, INS_COND_NONE},
        [LD_B_U8] = {},
        [RLCA] = {},
        [LD_U16_SP] = {},
        [ADD_HL_BC] = {},
        [LD_A_IND_BC] = {},
        [DEC_BC] = {},
        [INC_C] = {},
        [DEC_C] = {},
        [LD_C_U8] = {},
        [RRCA] = {},
        [STOP] = {},
        [LD_IND_DE_U16] = {},
        [LD_DE_A] = {},
        [INC_DE] = {},
        [INC_D] = {},
        [DEC_D] = {},
        [LD_D_U8] = {},
        [RLA] = {},
        [JR_S8] = {},
        [ADD_HL_DE] = {},
        [LD_A_IND_DE] = {},
        [DEC_DE] = {},
        [INC_E] = {},
        [DEC_E] = {},
        [LD_E_D8] = {},
        [RRA] = {},
        [JR_NZ_S8] = {},
        [LD_HL_U16] = {},
        [LD_IND_HL_INC_A] = {},
        [INC_HL] = {},
        [INC_H] = {},
        [DEC_H] = {},
        [LD_H_U8] = {},
        [DAA] = {},
        [JR_Z_I8] = {},
        [ADD_HL_HL] = {},
        [LD_A_IND_HL_INC] = {},
        [DEC_HL] = {},
        [INC_L] = {},
        [DEC_L] = {},
        [LD_L_U8] = {},
        [CPL] = {},
};

const struct instruction* get_instruction(uint8_t opcode)
{
        return &instructions[NOP];
}
