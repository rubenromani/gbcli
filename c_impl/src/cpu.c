#include "cpu.h"
#include "bus.h"

struct cpu cpu = {
        .regs.bytes = {0x00},
        .ops = {
                .execute = execution
        },
        .bus = &bus
};

