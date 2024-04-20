#include "include/cpu.hpp"

Cpu::Cpu() {}

uint16_t Cpu::Register::get_bc() const {
  return static_cast<uint16_t>(b) << 8 | static_cast<uint16_t>(c);
}

void Cpu::Register::set_bc(uint16_t value) {
  b = static_cast<uint8_t>(value >> 8);
  c = static_cast<uint8_t>(value);
}

uint16_t Cpu::Register::get_af() const {
  return static_cast<uint16_t>(a) << 8 | static_cast<uint16_t>(f);
}

void Cpu::Register::set_af(uint16_t value) {
  a = static_cast<uint8_t>(value >> 8);
  f = static_cast<uint8_t>(value);
}
