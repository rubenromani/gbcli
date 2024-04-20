#include <cstdint>
#include <stdint.h>

class Cpu {

public:
  Cpu();

private:
  struct Register {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t f;
    uint8_t h;
    uint8_t l;

    uint16_t get_bc() const;
    void set_bc(uint16_t value);

    uint16_t get_af() const;
    void set_af(uint16_t value);
  };

  struct FlagRegister {
    uint8_t zero;
    uint8_t subtract;
    uint8_t half_carry;
    uint8_t carry;
  };
};
