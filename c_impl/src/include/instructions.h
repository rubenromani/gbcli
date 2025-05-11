#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include <stdint.h>

#define N_INSTRUCTIONS 0xFF

// Forward declarations
struct cpu;

typedef void(*ins_execution)(struct cpu *cpu);

extern const ins_execution execution[];

#endif
