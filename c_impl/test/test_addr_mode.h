#ifndef _TEST_ADDR_MODE_H
#define _TEST_ADDR_MODE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cpu.h"
#include "instructions.h"


// Data types
typedef bool (*test_fn)(void);

struct test_case{
        const char* name;
        test_fn test;
};

// Functions prototypes
bool test_addr_mode_none(void);
bool test_addr_mode_reg_bit8(void);
bool test_addr_mode_reg_bit16(void);
bool test_addr_mode_reg_ptr(void);
bool test_addr_mode_dir_u8(void);
bool test_addr_mode_dir_u16(void);
bool test_addr_mode_addr_u8(void);
bool test_addr_mode_addr_u16(void);
bool test_addr_mode_addr_s8(void);

// Functions to be tested
extern uint8_t* addr_mode_none(struct cpu_context * context, const struct ins_operand * operand);
extern uint8_t* addr_mode_reg(struct cpu_context * context, const struct ins_operand * operand);
extern uint8_t* addr_mode_reg_ptr(struct cpu_context * context, const struct ins_operand * operand);
extern uint8_t* addr_mode_dir_u8(struct cpu_context * context, const struct ins_operand * operand);
extern uint8_t* addr_mode_dir_u16(struct cpu_context * context, const struct ins_operand * operand);
extern uint8_t* addr_mode_addr_u8(struct cpu_context * context, const struct ins_operand * operand);
extern uint8_t* addr_mode_addr_u16(struct cpu_context * context, const struct ins_operand * operand);
extern uint8_t* addr_mode_addr_s8(struct cpu_context * context, const struct ins_operand * operand);

extern struct cpu_context context;
extern uint8_t mem[0xFFFF];

// Utilities
void reset_context()
{
        memset(&context.regs, 0, sizeof(union cpu_registers));
        memset(mem, 0, sizeof(mem));
}

int addr_mode_test_suite()
{
        printf("Running address mode tests ...\n");
        
        struct test_case tests[] = {
                {"addr_mode_none", test_addr_mode_none},
                {"addr_mode_reg_bit8", test_addr_mode_reg_bit8},
                {"addr_mode_reg_bit16", test_addr_mode_reg_bit16},
                {"addr_mode_reg_ptr", test_addr_mode_reg_ptr},
                {"addr_mode_dir_u8", test_addr_mode_dir_u8},
                {"addr_mode_dir_u16", test_addr_mode_dir_u16},
                {"addr_mode_addr_u8", test_addr_mode_addr_u8},
                {"addr_mode_addr_u16", test_addr_mode_addr_u16},
                {"addr_mode_addr_s8", test_addr_mode_addr_s8},             
        }; 

        size_t pass_count = 0;
        size_t total_tests = sizeof(tests) / sizeof(struct test_case);

        for(int i=0; i<total_tests; i++)
        {
                printf("Running test %d/%d: %s... ", i+1, total_tests, tests[i].name);
                bool result = tests[i].test();
                printf("%s\n", result ? "PASS" : "FAIL");

                if(result) pass_count++;
        }
        
        printf("\nTest summary: %d/%d test passed\n", pass_count, total_tests);

        return pass_count == total_tests ? 0 : 1;
}

bool test_addr_mode_none()
{
        reset_context();
        struct ins_operand operand = {
                .size = INS_SIZE_NONE,
                .addr_mode = INS_ADDR_NONE,
                .reg_name = INS_REG_NONE
        };

        uint8_t* result = addr_mode_none(&context, &operand);

        return true;
}

bool test_addr_mode_reg_bit8()
{
        reset_context();

        context.regs.bytes[A] = 0x42;
        context.regs.bytes[B] = 0x24;
        context.regs.bytes[C] = 0x56;

        struct ins_operand operand = {
                .size = INS_SIZE_BIT8,
                .addr_mode = INS_ADDR_REG,
                .reg_name = INS_REG_A
        };
        uint8_t* result = addr_mode_reg(&context, &operand);
        if(result != &context.regs.byte.a || *result != 0x42) return false;


        operand.reg_name = INS_REG_B;
        result = addr_mode_reg(&context, &operand);
        if(result != &context.regs.byte.b || *result != 0x24) return false;

        operand.reg_name = INS_REG_C;
        result = addr_mode_reg(&context, &operand);
        if(result != &context.regs.byte.c || *result != 0x56) return false;

        return true;
}

bool test_addr_mode_reg_bit16()
{
        reset_context();

        context.regs.words[BC] = 0x4241;
        context.regs.words[DE] = 0x2423;
        context.regs.words[HL] = 0x5655;

        struct ins_operand operand = {
                .size = INS_SIZE_BIT16,
                .addr_mode = INS_ADDR_REG,
                .reg_name = INS_REG_BC
        };
        uint16_t* result = (uint16_t*)addr_mode_reg(&context, &operand);
        if(result != &context.regs.word.bc || *result != 0x4241) return false;

        operand.reg_name = INS_REG_DE;
        result = (uint16_t*)addr_mode_reg(&context, &operand);
        if(result != &context.regs.word.de || *result != 0x2423) return false;

        operand.reg_name = INS_REG_HL;
        result = (uint16_t*)addr_mode_reg(&context, &operand);
        if(result != &context.regs.word.hl || *result != 0x5655) return false;

        return true;
}

bool test_addr_mode_reg_ptr(void)
{
        reset_context();
       
        context.regs.words[HL] = 0x1000;
        mem[0x1000] = 0xA1;

        struct ins_operand operand = {
                .size = INS_SIZE_BIT8,
                .addr_mode = INS_ADDR_REG_PTR,
                .reg_name = INS_REG_HL
        };
        uint8_t* result = addr_mode_reg_ptr(&context, &operand);
        if(result != &mem[0x1000] || *result != 0xA1) return false;

        return true;
}

bool test_addr_mode_dir_u8(void)
{
        reset_context();

        context.regs.words[PC] = 0x0100;
        mem[0x0100] = 0x42;

        struct ins_operand operand = {
                .size = INS_SIZE_BIT8,
                .addr_mode = INS_ADDR_DIR_U8,
                .reg_name = INS_REG_NONE
        };
        uint8_t* result = addr_mode_dir_u8(&context, &operand);
        if(result != &mem[0x0100] || *result != 0x42) return false;

        return true;
}

bool test_addr_mode_dir_u16(void)
{
        reset_context();

        context.regs.words[PC] = 0x0100;
        mem[0x0100] = 0x42;
        mem[0x0101] = 0x41;

        struct ins_operand operand = {
                .size = INS_SIZE_BIT16,
                .addr_mode = INS_ADDR_DIR_U16,
                .reg_name = INS_REG_NONE
        };
        uint8_t* result = addr_mode_dir_u16(&context, &operand);
        if(result != &mem[0x0100] || *(uint16_t*)result != 0x4142) return false;

        return true;
}

bool test_addr_mode_addr_u8(void)
{
        reset_context();
        
        context.regs.words[PC] = 0x0100;
        mem[0x0100] = 0x42;
        mem[0xFF42] = 0xAA;

        struct ins_operand operand = {
                .size = INS_SIZE_BIT8,
                .addr_mode = INS_ADDR_ADDR_U8,
                .reg_name = INS_REG_NONE
        };
        uint8_t* result = addr_mode_addr_u8(&context, &operand);
        if(result != &mem[0xFF42] || *result != 0xAA) return false;

        return true;
}

bool test_addr_mode_addr_u16(void)
{
        reset_context();

        context.regs.words[PC] = 0x0100;
        mem[0x0100] = 0x42;
        mem[0x0101] = 0x41;
        mem[0x4142] = 0xAA;

        struct ins_operand operand = {
                .size = INS_SIZE_BIT8,
                .addr_mode = INS_ADDR_ADDR_U16,
                .reg_name = INS_REG_NONE
        };
        uint8_t* result = addr_mode_addr_u16(&context, &operand);
        if(result != &mem[0x4142] || *result != 0xAA) return false;

        return true;
}

bool test_addr_mode_addr_s8(void)
{
        reset_context();

        context.regs.words[PC] = 0x1100;
        mem[0x1100] = 0xAA;
        mem[0x10AA] = 0x42;

        struct ins_operand operand = {
                .size = INS_SIZE_BIT8,
                .addr_mode = INS_ADDR_ADDR_S8,
                .reg_name = INS_REG_NONE
        };
        uint8_t* result = addr_mode_addr_s8(&context, &operand);
        if(result != &mem[0x10AA] || *result != 0x42) return false;

        return true;
}

#endif /* _TEST_ADDR_MODE_H */
