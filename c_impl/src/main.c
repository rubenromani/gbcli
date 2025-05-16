#include <stdio.h>
#include "cpu.h"
#include "bus.h"


int main()
{
        printf("Hello from GBcli\n");

        cpu.regs.word.pc++;   // fetch
        cpu.ops.execute[0x00](&cpu);
        
        cpu.regs.word.pc++;   // fetch
        cpu.bus->memory[0x0002] = 0x80;
        cpu.bus->memory[0x0003] = 0x55;
        cpu.ops.execute[0x01](&cpu);
        printf("BC reg: %#X\n", cpu.regs.words[BC]);
        
        cpu.regs.word.pc++;   // fetch
        cpu.bus->memory[0x8055] = 0;
        cpu.regs.bytes[A] = 13;
        cpu.ops.execute[0x02](&cpu);
        printf("data: %d\n", cpu.bus->memory[0x8055]);
        //uint8_t data = cpu.bus->ops.read_byte(cpu.bus, 0x0000);
        //printf("data: %d\n", data);
        return 0;
}
