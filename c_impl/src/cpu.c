#include <stdio.h>

#include "cpu.h"
#include "instructions.h"

// external variables
struct cpu_context context = {
        .regs.bytes = {0} 
};

// Local function protorypes
static void update_pc(struct cpu_context * context, uint8_t val);
static uint8_t read_byte(struct cpu_context * context, uint16_t addr);
static uint16_t read_word(struct cpu_context * context, uint16_t addr);
static void write_byte(struct cpu_context * context, uint16_t addr, uint8_t val);
static void write_word(struct cpu_context * context, uint16_t addr, uint16_t val);
static struct instruction fetch(struct cpu_context * context);

// Public functions

void run(struct cpu_context * context)
{
        printf("Start running execution\n");
}

// Local functions

static void update_pc(struct cpu_context * context, uint8_t val)
{
        context->regs.words[PC] += val;
}

static uint8_t read_byte(struct cpu_context * context, uint16_t addr)
{
        update_pc(context, 1);
        
         // read from memory -> to externalize
        return mem[addr];
}

static uint16_t read_word(struct cpu_context * context, uint16_t addr)
{
        printf("NOT IMPLEMENTED");
}

static void write_byte(struct cpu_context * context, uint16_t addr, uint8_t val)
{
        printf("NOT IMPLEMENTED");
}

static void write_word(struct cpu_context * context, uint16_t addr, uint8_t val)
{
        printf("NOT IMPLEMENTED");
}

static instruction fetch(struct cpu_context * context)
{
        uint8_t opcode = read_byte(context, context->regs.words[PC]);
        return get_instruction(opcode);
}

int main()
{
        printf("Hello from CPU\n");
        run(&context);
        return 0;
}
