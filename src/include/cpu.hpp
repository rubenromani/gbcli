#include <cstdint>
#include <stdint.h>

class Memory {
public:
  Memory();
  ~Memory();
  uint8_t buffer[0xFFFF];
};

class Cpu {

public:
  Cpu();
  void run(uint32_t n_exec);

  enum RegName { a = 0, b, c, d, e, f, h, l };

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
    STORE_A_IND_BC = 0x02,
    LOAD_A_IND_BC = 0x0A,
    STORE_A_IND_DE = 0x12,
    LOAD_A_IND_DE = 0x1A,
    STORE_IMM_IND_HL = 0x36,
    STORE_A_DIR = 0xEA,
    LOADH_A_IND_C = 0xF2,
    LOAD_A_DIR = 0xFA,
  };

  Instruction fetch();
  void execute(Instruction ins);

  void write_byte(uint8_t data, uint16_t addr, Memory &mem);
  void write_word(uint16_t data, uint16_t addr, Memory &mem);
  uint8_t read_byte(uint16_t addr, Memory &mem);
  uint16_t read_word(uint16_t addr, Memory &mem);

  Memory mem;
  Register reg;
  FlagRegister flagReg;
};
