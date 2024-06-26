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
    resetMemory();
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

  void resetMemory() { memset(cpu_.mem.buffer, 0x00, 0xFFFF); }

  void setMemory(const uint8_t src[0xFFFF]) {
    for (uint16_t i = 0; i < 0xFFFF; i++) {
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

TEST_F(CpuTest, Test_STORE_A_IND_DE_instruction) {
  cpu_.mem.buffer[0] = 0x12; // STORE_A_IND_DE
  cpu_.reg.val[Cpu::RegName::a] = 0xFF;
  cpu_.run(1);
  EXPECT_EQ(cpu_.mem.buffer[0], 0xFF);
}

TEST_F(CpuTest, Test_LOAD_A_IND_BC_instruction) {
  cpu_.mem.buffer[0] = 0x0A; // LOAD_A_IND_BC
  cpu_.mem.buffer[1] = 0x33, cpu_.reg.val[Cpu::RegName::a] = 0x00;
  cpu_.reg.set_bc(0x0001);
  cpu_.run(1);
  EXPECT_EQ(cpu_.reg.val[Cpu::RegName::a], 0x33);
}

TEST_F(CpuTest, Test_LOAD_A_IND_DE_instruction) {
  cpu_.mem.buffer[0] = 0x1A; // LOAD_A_IND_DE
  cpu_.mem.buffer[1] = 0x33, cpu_.reg.val[Cpu::RegName::a] = 0x00;
  cpu_.reg.set_de(0x0001);
  cpu_.run(1);
  EXPECT_EQ(cpu_.reg.val[Cpu::RegName::a], 0x33);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
