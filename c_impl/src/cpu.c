#include <stdio.h>
#include <stdlib.h>

#ifdef TESTING
#define static 
#endif

#include "cpu.h"
#include "instructions.h"

#define SET_FLAG(context_ptr, flag) (context_ptr->regs.bytes[F] |= (1 << (flag+FLAG_BIT_OFFSET)))
#define RESET_FLAG(context_ptr, flag) (context_ptr->regs.bytes[F] &= ~(1 << (flag+FLAG_BIT_OFFSET))) 

// Local types
typedef void(*exec_ins_fn)(struct cpu_context * context, const struct instruction * ins);
typedef uint8_t*(*addr_mode_fn)(struct cpu_context * context, const struct ins_operand * operand);
typedef void(*eval_flag_fn)(struct cpu_context * context, const uint8_t old_val, const uint8_t new_val);

// Local function protorypes
static void update_pc(struct cpu_context * context, uint8_t val);
static const struct instruction* fetch(struct cpu_context * context);

static void eval_flag_carry(struct cpu_context * context, const uint8_t old_val, const uint8_t new_val);
static void eval_flag_half_carry(struct cpu_context * context, const uint8_t old_val, const uint8_t new_val);
static void eval_flag_subtract(struct cpu_context * context, const uint8_t old_val, const uint8_t new_val);
static void eval_flag_zero(struct cpu_context * context, const uint8_t old_val, const uint8_t new_val);
static void eval_flags(struct cpu_context * context, const uint8_t old_val, const uint8_t new_val, const enum ins_flag_op * flag_ops);

static uint8_t* read_byte(struct cpu_context * context, uint16_t addr);
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

eval_flag_fn eval_flag[N_FLAGS] = {
        [CARRY] = eval_flag_carry,
        [HALF_CARRY] = eval_flag_half_carry,
        [SUBTRACT] = eval_flag_subtract,
        [ZERO] = eval_flag_zero,
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
        uint8_t opcode = *read_byte(context, context->regs.words[PC]);
        return get_instruction(opcode);
}

static void eval_flag_carry(struct cpu_context * context, const uint8_t old_val, const uint8_t new_val)
{
        if (context->regs.flags.subtract == 0){
                if (new_val < old_val) {
                        SET_FLAG(context, CARRY);
                } else {
                        RESET_FLAG(context, CARRY);
                }
        } else {
                if (new_val > old_val) {
                        SET_FLAG(context, CARRY);
                } else {
                        RESET_FLAG(context, CARRY);
                }
        }
}

static void eval_flag_half_carry(struct cpu_context * context, const uint8_t old_val, const uint8_t new_val)
{
        if (context->regs.flags.subtract == 0) {
                if ((new_val & 0x0F) < (old_val & 0x0F)){
                        SET_FLAG(context, HALF_CARRY);
                } else {
                        RESET_FLAG(context, HALF_CARRY);
                }
        } else {
                if ((new_val & 0x0F) > (old_val & 0x0F)) {
                        SET_FLAG(context, HALF_CARRY);
                } else {
                        RESET_FLAG(context, HALF_CARRY);
                }
        }
}

static void eval_flag_subtract(struct cpu_context * context, const uint8_t old_val, const uint8_t new_val)
{
        printf("UNREACHBLE");
}

static void eval_flag_zero(struct cpu_context * context, const uint8_t old_val, const uint8_t new_val)
{
        if (old_val != 0 && new_val == 0){
                SET_FLAG(context, ZERO);
        } else {
                RESET_FLAG(context, ZERO);
        }
}

static void eval_flags(struct cpu_context * context, const uint8_t old_val, const uint8_t new_val, const enum ins_flag_op * flag_ops)
{
        // starst from the back, the eval of the carry and half-carry requires the subtract flag
        for(size_t i = N_FLAGS; i>0; i--) {
                switch (flag_ops[i]){
                case SET:
                        SET_FLAG(context, i);
                        break;
                case RESET:
                        RESET_FLAG(context, i);
                        break;
                case EVAL:
                        eval_flag[i](context, old_val, new_val);
                        break;
                case NONE:
                        break;
                default:
                        printf("UNREACHBLE");
                }
        }
}

static uint8_t* read_byte(struct cpu_context * context, uint16_t addr)
{
         // read from memory -> to externalize
        return &mem[addr];
}

static uint16_t read_word(struct cpu_context * context, uint16_t addr)
{
        printf("NOT IMPLEMENTED");
}

static void write_byte(struct cpu_context * context, uint16_t addr, uint8_t val)
{
        // write to memory -> to externalize
        mem[addr] = val;
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
                        uint8_t new_value = *val+1;
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
        return &mem[0x00];
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
        uint16_t addr = context->regs.words[operand->reg_name & WORD_REG_MASK];
        return read_byte(context, addr);
}

static uint8_t* addr_mode_dir_u8(struct cpu_context * context, const struct ins_operand * operand)
{
        uint8_t* res = read_byte(context, context->regs.words[PC]);
        update_pc(context, 1);
        return res;
}

static uint8_t* addr_mode_dir_u16(struct cpu_context * context, const struct ins_operand * operand)
{
        uint8_t* res = read_byte(context, context->regs.words[PC]);
        update_pc(context, 2);
        return res;
}

static uint8_t* addr_mode_addr_u8(struct cpu_context * context, const struct ins_operand * operand)
{
        uint8_t* addr_low = read_byte(context, context->regs.words[PC]);
        uint16_t addr = 0xFF00 | (uint16_t)(*addr_low);
        uint8_t* res = read_byte(context, addr);
        update_pc(context, 1);
        return res;
}

static uint8_t* addr_mode_addr_u16(struct cpu_context * context, const struct ins_operand * operand)
{
        uint16_t addr = *(uint16_t*)read_byte(context, context->regs.words[PC]);
        uint8_t* res = read_byte(context, addr);
        update_pc(context, 2);
        return res;
}

static uint8_t* addr_mode_addr_s8(struct cpu_context * context, const struct ins_operand * operand)
{
        uint8_t* addr_s = read_byte(context, context->regs.words[PC]);
        uint16_t addr = context->regs.words[PC] + (int8_t)*addr_s;
        printf("pc: %x, addr: %x, offset: %d\n", context->regs.words[PC], addr, (int8_t)(*addr_s));
        return read_byte(context, addr);
}

#ifndef TESTING

int main()
{
        printf("Hello from CPU");
        return 0;
}

#endif
