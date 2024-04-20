#include <cstdint>
#include <stdint.h>

class Cpu {

public:
  Cpu();

private:
  enum RegName {
    a = 0,
    b,
    c,
    d,
    e,
    f,
    h,
    l
  }

  struct Register {
    uint8_t val[8];

    uint16_t pc;
    uint16_t sp;

    uint16_t get_bc() const;
    void set_bc(uint16_t value);

    uint16_t get_af() const;
    void set_af(uint16_t value);

    uint16_t get_de() const;
    void set_de(uint16_t value);

    uint16_t get_hl() const;
    void set_hl(uint16_t value);

    uint16_t get_rr(RegName msb, RegName lsb) const;
    void set_rr(RegName msb, RegName lsb, uint16_t);
  };

  struct FlagRegister {
    uint8_t zero;
    uint8_t subtract;
    uint8_t half_carry;
    uint8_t carry;
  };

  enum Instruction {
    LOAD_REG_REG,
    LOAD_REG_IMM,
    LOAD_REG_IND_HL,
    LOAD_ACC_IND_BC,
    STORE_REG_IND_HL,
    STORE_IMM_IND_HL
  };

  void execute(Instruction ins);
};