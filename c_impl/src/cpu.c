#include "cpu.h"
#include "bus.h"

static void update_pc(struct cpu *cpu, uint8_t val);

struct cpu cpu = {
        .regs.bytes = {0x00},
        .ops = {
                .execute = execution,
                .update_pc = update_pc
        },
        .bus = &bus
};

static void update_pc(struct cpu *cpu, uint8_t val)
{
        cpu->regs.word.pc += val;
}

