#include "include/cpu.hpp"
#include <cstdint>
#include <cstdio>

Memory::Memory(uint16_t size) { buffer = new uint8_t[size]; }
Memory::~Memory() { delete buffer; }

Cpu::Cpu() : mem(Memory(0xFFFF)) {}

void Cpu::execute(Instruction opcode) {
  switch (opcode) {
  case STORE_A_IND_BC: {
    write_byte(reg.val[RegName::a], reg.get_bc(), mem);
    break;
  }
  case STORE_A_IND_DE: {
    write_byte(reg.val[RegName::a], reg.get_de(), mem);
    break;
  }
  case LOAD_A_IND_BC: {
    reg.val[RegName::a] = read_byte(reg.get_bc(), mem);
    break;
  }
  case LOAD_A_IND_DE: {
    reg.val[RegName::a] = read_byte(reg.get_de(), mem);
    break;
  }
  case STORE_IMM_IND_HL: {
    uint8_t data = read_byte(reg.pc, mem);
    write_byte(data, reg.get_hl(), mem);
    break;
  }
  case STORE_A_DIR: {
    uint16_t addr = read_word(reg.pc, mem);
    reg.pc++;
    write_byte(reg.val[RegName::a], addr, mem);
  }
  case LOADH_A_IND_C: {
    uint16_t addr = 0xFF00 | reg.val[RegName::c];
    reg.val[RegName::a] = read_byte(addr, mem);
  }
  case LOAD_A_DIR: {
    uint16_t addr = read_word(reg.pc, mem);
    reg.pc++;
    reg.val[RegName::a] = read_byte(addr, mem);
  }
  default: {
    printf("Error: Unknown instruction");
    break;
  }
  }
}

void Cpu::write_byte(uint8_t data, uint16_t addr, Memory &mem) {
  reg.pc++;
  mem.buffer[addr] = data;
}

void Cpu::write_word(uint16_t data, uint16_t addr, Memory &mem) {
  reg.pc += 2;
  mem.buffer[addr] = static_cast<uint8_t>(data);
  mem.buffer[addr + 1] = static_cast<uint8_t>(data >> 8);
}

uint8_t Cpu::read_byte(uint16_t addr, Memory &mem) {
  reg.pc++;
  return mem.buffer[addr];
}

uint16_t Cpu::read_word(uint16_t addr, Memory &mem) {
  reg.pc += 2;
  return static_cast<uint16_t>(mem.buffer[addr]) |
         static_cast<uint8_t>(mem.buffer[addr + 1] << 8);
}

uint16_t Cpu::Register::get_bc() const {
  return get_rr(RegName::b, RegName::c);
}

void Cpu::Register::set_bc(uint16_t value) {
  set_rr(RegName::b, RegName::c, value);
}

uint16_t Cpu::Register::get_af() const {
  return get_rr(RegName::a, RegName::f);
}

void Cpu::Register::set_af(uint16_t value) {
  set_rr(RegName::a, RegName::f, value);
}

uint16_t Cpu::Register::get_de() const {
  return get_rr(RegName::d, RegName::e);
}

void Cpu::Register::set_de(uint16_t value) {
  set_rr(RegName::d, RegName::e, value);
}

uint16_t Cpu::Register::get_hl() const {
  return get_rr(RegName::h, RegName::l);
}

void Cpu::Register::set_hl(uint16_t value) {
  set_rr(RegName::h, RegName::l, value);
}

uint16_t Cpu::Register::get_rr(RegName msb, RegName lsb) const {
  return static_cast<uint16_t>(val[msb]) << 8 | static_cast<uint16_t>(val[lsb]);
}

void Cpu::Register::set_rr(RegName msb, RegName lsb, uint16_t value) {
  val[msb] = static_cast<uint8_t>(value >> 8);
  val[lsb] = static_cast<uint8_t>(value);
}
