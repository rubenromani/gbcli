#include "include/cpu.hpp"
#include <cstdio>

Cpu::Cpu() {}

void Cpu::execute(Instruction opcode) {
  switch (ins) {

  default:
    printf("Error: Unknown instruction");
    break;
  }
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
