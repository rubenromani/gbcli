#include "instructions.h"
#include "instruction_set.h"
#include "bus.h"
#include "cpu.h"

#include <stdio.h>

static void load_r8_u8(struct cpu *cpu, enum cpu_reg_byte reg);
static void load_r8_u16(struct cpu *cpu, enum cpu_reg_word reg);
static void load_r8_ind8(struct cpu *cpu, enum cpu_reg_byte reg, uint8_t addr);
static void load_r8_ind16(struct cpu *cpu, enum cpu_reg_byte reg, uint16_t addr);
static void load_r16_u16(struct cpu *cpu, enum cpu_reg_word reg);

static void store_ind16_r8(struct cpu *cpu, enum cpu_reg_word addr_reg, enum cpu_reg_byte reg);

static void nop(struct cpu *cpu);
static void load_bc_u16(struct cpu *cpu);
static void load_ind_bc_a(struct cpu *cpu);

const ins_execution execution[N_INSTRUCTIONS] = {
        [NOP] = nop,
        [LD_BC_U16] = load_bc_u16,
        [LD_IND_BC_A] = load_ind_bc_a
};

static void load_r8_u8(struct cpu *cpu, enum cpu_reg_byte reg)
{
        return;
}

static void load_r16_u16(struct cpu *cpu, enum cpu_reg_word reg)
{      
        printf("pc: %d, bc: %#X, b: %#X, c: %#X\n", cpu->regs.word.pc, cpu->regs.words[BC], cpu->regs.bytes[B], cpu->regs.bytes[C]);
        cpu->regs.words[reg] = cpu->bus->ops.read_word_msb(cpu->bus, cpu->regs.word.pc);
        cpu->ops.update_pc(cpu, 2);
        printf("pc: %d, bc: %#X, b: %#X, c: %#X\n", cpu->regs.word.pc, cpu->regs.words[BC], cpu->regs.bytes[B], cpu->regs.bytes[C]);
}

static void store_ind16_r8(struct cpu *cpu, enum cpu_reg_word addr_reg, enum cpu_reg_byte reg)
{
        cpu->bus->ops.write_byte(cpu->bus, cpu->regs.words[addr_reg], cpu->regs.bytes[reg]); 
        cpu->ops.update_pc(cpu, 1);
}

static void nop(struct cpu *cpu)
{
        printf("NOP\n");
}

static void load_bc_u16(struct cpu *cpu)
{
        load_r16_u16(cpu, BC);
}

static void load_ind_bc_a(struct cpu *cpu)
{
        store_ind16_r8(cpu, BC, A);
}
 
