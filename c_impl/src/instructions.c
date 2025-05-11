#include "instructions.h"
#include "instruction_set.h"
#include "bus.h"
#include "cpu.h"

#include <stdio.h>

static void load_r8_d8(struct cpu *cpu, enum cpu_reg_byte reg);
static void load_r8_d16(struct cpu *cpu, enum cpu_reg_word reg);
static void load_r8_a8(struct cpu *cpu, enum cpu_reg_byte reg, uint8_t addr);
static void load_r8_a16(struct cpu *cpu, enum cpu_reg_byte reg, uint16_t addr);
static void load_r16_d16(struct cpu *cpu, enum cpu_reg_word reg);

static void nop(struct cpu *cpu);
static void load_bc_d16(struct cpu *cpu);

const ins_execution execution[N_INSTRUCTIONS] = {
        [NOP] = nop,
        [LD_BC_D16] = load_bc_d16
};

static void load_r8_d8(struct cpu *cpu, enum cpu_reg_byte reg)
{
        printf("load_r8_d8 with byte reg: %d\n", reg);
}

static void load_r16_d16(struct cpu *cpu, enum cpu_reg_word reg)
{
        printf("load_r16_d16 with word reg: %d\n", reg);
}

static void nop(struct cpu *cpu)
{
        printf("NOP\n");
        cpu->regs.word.pc++;
}

static void load_bc_d16(struct cpu *cpu)
{
        load_r16_d16(cpu, BC);
}
 
