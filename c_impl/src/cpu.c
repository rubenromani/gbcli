#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "instructions.h"

// Local types
typedef void(*exec_ins_fn)(struct cpu_context * context, const struct instruction * ins);
typedef uint8_t*(*addr_mode_fn)(struct cpu_context * context, const struct ins_operand * operand);

// Local function protorypes
static void update_pc(struct cpu_context * context, uint8_t val);
static const struct instruction* fetch(struct cpu_context * context);

static uint8_t read_byte(struct cpu_context * context, uint16_t addr);
static uint16_t read_word(struct cpu_context * context, uint16_t addr);
static void write_byte(struct cpu_context * context, uint16_t addr, uint8_t val);
static void write_word(struct cpu_context * context, uint16_t addr, uint16_t val);

static void exec_load_ins(struct cpu_context * context, const struct instruction *  ins);
static void exec_alu_ins(struct cpu_context * context, const struct instruction * ins);
static void exec_incdec_ins(struct cpu_context * context, const struct instruction * ins);
static void exec_jump_ins(struct cpu_context * context, const struct instruction * ins);
static void exec_call_ins(struct cpu_context * context, const struct instruction * ins);
static void exec_ret_ins(struct cpu_context * context, const struct instruction * ins);
static void exec_misc_ins(struct cpu_context * context, const struct instruction * ins);

static uint8_t* addr_mode_none(struct cpu_context * context, const struct ins_operand * operand);
static uint8_t* addr_mode_reg(struct cpu_context * context, const struct ins_operand * operand);
static uint8_t* addr_mode_reg_ptr(struct cpu_context * context, const struct ins_operand * operand);
static uint8_t* addr_mode_dir_u8(struct cpu_context * context, const struct ins_operand * operand);
static uint8_t* addr_mode_dir_u16(struct cpu_context * context, const struct ins_operand * operand);
static uint8_t* addr_mode_addr_u8(struct cpu_context * context, const struct ins_operand * operand);
static uint8_t* addr_mode_addr_u16(struct cpu_context * context, const struct ins_operand * operand);
static uint8_t* addr_mode_addr_s8(struct cpu_context * context, const struct ins_operand * operand);

// external variables
struct cpu_context context = {
        .regs.bytes = {0} 
};

uint8_t mem[0xFFFF] = {0};

exec_ins_fn exec_ins[N_INS_TYPE] = {
        [INS_TYPE_LOAD] = exec_load_ins,
        [INS_TYPE_ALU] = exec_alu_ins,
        [INS_TYPE_INCDEC] = exec_incdec_ins,
        [INS_TYPE_JUMP] = exec_jump_ins,
        [INS_TYPE_CALL] = exec_call_ins,
        [INS_TYPE_RET] = exec_ret_ins,
        [INS_TYPE_MISC] = exec_misc_ins
};

addr_mode_fn addr_mode[N_ADDR_MODE] = {
        [INS_ADDR_NONE] = addr_mode_none,
        [INS_ADDR_REG] = addr_mode_reg,
        [INS_ADDR_REG_PTR] = addr_mode_reg_ptr,
        [INS_ADDR_DIR_U8] = addr_mode_dir_u8,
        [INS_ADDR_DIR_U16] = addr_mode_dir_u16,
        [INS_ADDR_ADDR_U8] = addr_mode_addr_u8,
        [INS_ADDR_ADDR_U16] = addr_mode_addr_u16,
        [INS_ADDR_ADDR_S8] = addr_mode_addr_s8
};

// Public functions

void run(struct cpu_context * context)
{
        while(0) {
                const struct instruction * ins = fetch(context);
                exec_ins[ins->type](context, ins);
        }
}

// Local functions

static void update_pc(struct cpu_context * context, uint8_t val)
{
        context->regs.words[PC] += val;
}

static const struct instruction* fetch(struct cpu_context * context)
{
        uint8_t opcode = read_byte(context, context->regs.words[PC]);
        return get_instruction(opcode);
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

static void write_word(struct cpu_context * context, uint16_t addr, uint16_t val)
{
        printf("NOT IMPLEMENTED");
}

static void exec_load_ins(struct cpu_context * context, const struct instruction * ins)
{
        printf("NOT IMPLEMENTED");
}

static void exec_alu_ins(struct cpu_context * context, const struct instruction * ins)
{
        printf("NOT IMPLEMENTED");
}

static void exec_incdec_ins(struct cpu_context * context, const struct instruction * ins)
{
        uint8_t* val = addr_mode[ins->operand1.addr_mode](context, &ins->operand1);

        switch (ins->operand1.size)
        {
        case INS_SIZE_BIT8:
                switch (ins->opcode & INCDEC_U8_MASK) {
                case INC_MASK_VALUE:
                        (*val)++;
                        break;
                case DEC_MASK_VALUE:
                        (*val)--;
                        break;
                default:
                        printf("UNREACHABLE");
                        exit(1);
                }
                break;
        case INS_SIZE_BIT16:
                switch (ins->opcode & INCDEC_U16_MASK) {
                case INC_MASK_VALUE:
                        (*(uint16_t*)val)++;
                        break;
                case DEC_MASK_VALUE:
                        (*(uint16_t*)val)--;
                        break;
                default:
                        printf("UNREACHABLE");
                        exit(1);
                }
                break;
        case INS_SIZE_NONE:
                printf("UNREACHBLE");
                exit(1);
        } 
}

static void exec_jump_ins(struct cpu_context * context, const struct instruction * ins)
{
        printf("NOT IMPLEMENTED");
}

static void exec_call_ins(struct cpu_context * context, const struct instruction * ins)
{
        printf("NOT IMPLEMENTED");
}

static void exec_ret_ins(struct cpu_context * context, const struct instruction * ins)
{
        printf("NOT IMPLEMENTED");
}

static void exec_misc_ins(struct cpu_context * context, const struct instruction * ins)
{
        printf("NOT IMPLEMENTED");
}

static uint8_t* addr_mode_none(struct cpu_context * context, const struct ins_operand * operand)
{
        printf("NOT_IMPLEMENTED");
}

static uint8_t* addr_mode_reg(struct cpu_context * context, const struct ins_operand * operand)
{
        switch (operand->size)
        {
        case INS_SIZE_BIT8:
                return &context->regs.bytes[operand->reg_name];
        case INS_SIZE_BIT16:
                return (uint8_t*)&context->regs.words[operand->reg_name & WORD_REG_MASK];
        default:
                printf("UNREACHABLE");
        }
}

static uint8_t* addr_mode_reg_ptr(struct cpu_context * context, const struct ins_operand * operand)
{
        printf("NOT IMPLEMENTED");
}

static uint8_t* addr_mode_dir_u8(struct cpu_context * context, const struct ins_operand * operand)
{
        printf("NOT IMPLEMENTED");
}

static uint8_t* addr_mode_dir_u16(struct cpu_context * context, const struct ins_operand * operand)
{
        printf("NOT IMPLEMENTED");
}

static uint8_t* addr_mode_addr_u8(struct cpu_context * context, const struct ins_operand * operand)
{
        printf("NOT IMPLEMENTED");
}

static uint8_t* addr_mode_addr_u16(struct cpu_context * context, const struct ins_operand * operand)
{
        printf("NOT IMPLEMENTED");
}

static uint8_t* addr_mode_addr_s8(struct cpu_context * context, const struct ins_operand * operand)
{
        printf("NOT IMPLEMENTED");
}

int main()
{
        printf("Hello from CPU\n");
        run(&context);
        return 0;
}
