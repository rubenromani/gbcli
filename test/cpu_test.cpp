#include <cpu.hpp>
#include <cstdint>
#include <cstring>
#include <gtest/gtest.h>

class CpuTest : public testing::Test {
public:
  CpuTest() {
    // You can do set-up work for each test here.
  }

  ~CpuTest() override {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  void SetUp() override {
    cpu_ = Cpu();
    resetRegs();
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  void resetRegs() {
    cpu_.reg.val[Cpu::RegName::a] = 0;
    cpu_.reg.val[Cpu::RegName::b] = 0;
    cpu_.reg.val[Cpu::RegName::c] = 0;
    cpu_.reg.val[Cpu::RegName::d] = 0;
    cpu_.reg.val[Cpu::RegName::e] = 0;
    cpu_.reg.val[Cpu::RegName::f] = 0;
    cpu_.reg.val[Cpu::RegName::h] = 0;
    cpu_.reg.val[Cpu::RegName::l] = 0;
    cpu_.reg.pc = 0;
    cpu_.reg.sp = 0;
  }

  void setMemory(const uint8_t src[4096]) {
    for (uint16_t i = 0; i < 4096; i++) {
      cpu_.mem.buffer[i] = src[i];
    }
  }

  Cpu cpu_;
};

TEST_F(CpuTest, Test_STORE_A_IND_BC_instruction) {
  cpu_.mem.buffer[0] = 0x02; // STORE_A_IND_BC
  cpu_.reg.val[Cpu::RegName::a] = 0xFF;
  cpu_.run(1);
  EXPECT_EQ(cpu_.mem.buffer[0], 0xFF);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
