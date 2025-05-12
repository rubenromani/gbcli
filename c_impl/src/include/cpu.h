#ifndef _CPU_H
#define _CPU_H

#include <stdint.h>

#include "instructions.h"
#include "bus.h"

enum cpu_reg_byte
{
        A = 0,
        F = 1,
        B = 2,
        C = 3,
        D = 4,
        E = 5,
        H = 6,
        L = 7
};

enum cpu_reg_word
{
        AF = 0,
        BC = 1,
        DE = 2,
        HL = 3
};

union cpu_registers
{
        // Access as 8 bit register
        struct 
        {
                uint8_t a;
                uint8_t f;
                uint8_t b;
                uint8_t c;
                uint8_t d;
                uint8_t e;
                uint8_t h;
                uint8_t l;
                uint8_t reserved[4];
        } byte;

        // access as 16 bit register
        struct 
        {
               uint16_t af;
               uint16_t bc;
               uint16_t de;
               uint16_t hl;
               uint16_t sp;
               uint16_t pc;
        } word;

        // access the flag register
        struct {
                uint8_t reserved_low;
                uint8_t flags_low : 4;
                uint8_t carry : 1;
                uint8_t half_carry : 1;
                uint8_t subtract : 1;
                uint8_t zero : 1;
                uint8_t reserved_high[10];
        } flags;

        // For loops
        uint8_t bytes[12];
        uint16_t words[6];
        
};

typedef void(*update_pc_fn)(struct cpu *cpu, uint8_t val);

struct cpu_ops{
        const ins_execution *execute;
        const update_pc_fn update_pc;
};

struct cpu
{
        union cpu_registers regs;
        struct cpu_ops ops;
        struct system_bus *bus;
};

extern struct cpu cpu;

#endif /* _CPU_H */
