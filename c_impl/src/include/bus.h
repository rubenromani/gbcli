#ifndef _BUS_H
#define _BUS_H

#include <stdint.h>

#define MEMORY_SIZE 0xFFFF

struct system_bus;

typedef uint8_t (*read_byte_fn)(struct system_bus * bus, uint16_t addr);
typedef void (*write_byte_fn)(struct system_bus * bus, uint16_t addr, uint8_t val);

struct system_bus_ops
{
        read_byte_fn read_byte;
        write_byte_fn write_byte;
};

struct system_bus 
{
        uint8_t memory[MEMORY_SIZE];
        struct system_bus_ops ops;
};

extern struct system_bus bus;

#define bus_read_byte(addr) \
        bus.ops.read_byte(&bus, addr)

#define bus_write_byte(addr, val) \
        bus.ops.write_byte(&bus, addr, val)

#endif /* _BUS_S */
