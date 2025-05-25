/*
 * instructions.h - CPU instruction definition and utilities
 *
 * This file defines the instructions, operand types, registers and addressing
 * modes used by the CPU emulator. The structures and enums provide a consistent
 * interface for decoding and executing CPU instructions.
 */

#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H
#include <stdint.h>

#define N_INSTRUCTIONS 0xFF  /* Maximum number of instruction opcodes */

#define N_INS_TYPE 7
#define N_ADDR_MODE 8
#define N_FLAGS 4

#define INCDEC_U8_MASK 0x01
#define INCDEC_U16_MASK 0x08
#define INC_MASK_VALUE 0x00
#define DEC_MASK_VALUE 0x01

#define WORD_REG_MASK 0x3


/*
 * ins_type - Instruction type categories
 *
 * Categorizes instructions by their general operation, allowing the emulator
 * to dispatch to appropriate handlers.
 */
enum ins_type {
        INS_TYPE_LOAD,     /* Register/memory load operations */
        INS_TYPE_ALU,      /* Arithmetic and logical operations */
        INS_TYPE_INCDEC,   /* Increment/decrement operations */
        INS_TYPE_JUMP,     /* Jump and branch operations */
        INS_TYPE_CALL,     /* Subroutine call operations */
        INS_TYPE_RET,      /* Return from subroutine operations */
        INS_TYPE_MISC,     /* Miscellaneous operations */
};

/*
 * ins_addr_mode - Addressing mode for instruction operands
 *
 * Defines how the operands are accessed and interpreted during instruction
 * execution.
 */
enum ins_addr_mode {
        INS_ADDR_NONE,        /* None */
        INS_ADDR_REG,         /* Register direct mode */
        INS_ADDR_REG_PTR,     /* Indirect register (pointer) mode */
        INS_ADDR_DIR_U8,      /* Direct 8-bit unsigned immediate value */
        INS_ADDR_DIR_U16,     /* Direct 16-bit unsigned immediate value */
        INS_ADDR_ADDR_U8,     /* 8-bit unsigned memory address */
        INS_ADDR_ADDR_U16,    /* 16-bit unsigned memory address */
        INS_ADDR_ADDR_S8      /* 8-bit signed relative address offset */
};

/*
 * ins_operand_size - Size of instruction operands
 *
 * Specifies whether an operation works on 8-bit or 16-bit data.
 */
enum ins_operand_size {
        INS_SIZE_NONE,        /* None */
        INS_SIZE_BIT8,        /* 8-bit operand */
        INS_SIZE_BIT16        /* 16-bit operand */
};

/*
 * ins_reg_name - CPU register identifiers
 *
 * Enumeration of available CPU registers. Registers 0-7 are 8-bit,
 * while 8-11 are 16-bit register pairs.
 */
enum ins_reg_name {
        INS_REG_A = 0,       /* Accumulator */
        INS_REG_F,           /* Flags register */
        INS_REG_C,           /* C register */
        INS_REG_B,           /* B register */
        INS_REG_E,           /* E register */
        INS_REG_D,           /* D register */
        INS_REG_L,           /* L register */
        INS_REG_H,           /* H register */
        INS_REG_AF,          /* AF register pair (A and F) */
        INS_REG_BC,          /* BC register pair (B and C) */
        INS_REG_DE,          /* DE register pair (D and E) */
        INS_REG_HL,          /* HL register pair (H and L) */
        INS_REG_NONE         /* None */
};

/*
 * ins_flag_op - Possible operation for a flag
 *
 * Used to determine wich operations has to be performed
 * on for a specific flag.
 * */
enum ins_flag_op {
        SET,                /* Set the flag */
        RESET,              /* Reset the flag */
        EVAL,               /* Evaluate the flag */
        NONE                /* No operation */
};

/*
 * ins_condition - Condition codes for conditional instructions
 *
 * Used by conditional operations to determine whether the instruction
 * should be executed based on CPU flag states.
 */
enum ins_condition {
        INS_COND_NONE,        /* Unconditional execution */
        INS_COND_CARRY,       /* Execute if carry flag is set */
        INS_COND_NO_CARRY,    /* Execute if carry flag is clear */
        INS_COND_ZERO,        /* Execute if zero flag is set */
        INS_COND_NO_ZERO      /* Execute if zero flag is clear */
};

/*
 * ins_operand - Structure defining an instruction operand
 *
 * Contains all information needed to interpret and access an instruction
 * operand, including its size, addressing mode and register reference.
 */
struct ins_operand
{
        enum ins_operand_size size;       /* Operand size (8/16-bit) */
        enum ins_addr_mode addr_mode;     /* Addressing mode */
        enum ins_reg_name reg_name;       /* Register identifier if applicable */
};

/*
 * instruction - Complete instruction definition
 *
 * Represents a fully decoded CPU instruction with all its properties including
 * operation type, operands, execution cycles, and conditional execution info.
 */
struct instruction
{
        uint8_t opcode;                       /* Instruction opcode */ 
        enum ins_type type;                   /* Instruction type */
        struct ins_operand operand1;          /* First operand */
        struct ins_operand operand2;          /* Second operand */
        enum ins_flag_op flag_ops[N_FLAGS];   /* Flag operations */
        uint8_t cycles;                       /* Clock cycles required for execution */
        enum ins_condition condition;         /* Execution condition (if any) */
};

/*
 * get_instruction - Decodes opcode into a complete instruction structure
 * @opcode: The raw opcode byte to decode
 *
 * Looks up the given opcode and returns a fully populated instruction
 * structure with all properties needed for execution.
 *
 * Return: Populated instruction structure representing the decoded opcode
 */
const struct instruction* get_instruction(uint8_t opcode);

#endif /* _INSTRUCTION_H */
