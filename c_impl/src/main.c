#include <stdio.h>
#include "cpu.h"
#include "bus.h"


int main()
{
        printf("Hello from GBcli\n");
        cpu.ops.execute[0x00](&cpu);
        cpu.ops.execute[0x01](&cpu);
        
        cpu.bus->memory[0x0000] = 85;
        uint8_t data = cpu.bus->ops.read_byte(cpu.bus, 0x0000);
        printf("data: %d\n", data);
        return 0;
}
