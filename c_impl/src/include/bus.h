#ifndef _BUS_H
#define _BUS_H

#include <stdint.h>

#define MEMORY_SIZE 0xFFFF

struct system_bus;

typedef void (*write_byte_fn)(struct system_bus *bus, uint16_t addr, uint8_t data);
typedef void (*write_word_fn)(struct system_bus *bus, uint16_t addr, uint16_t data);
typedef uint8_t (*read_byte_fn)(struct system_bus *bus, uint16_t addr);
typedef uint16_t (*read_word_fn)(struct system_bus *bus, uint16_t addr);

struct system_bus_ops 
{
        const write_byte_fn write_byte;
        const write_word_fn write_word;
        const read_byte_fn read_byte;
        const read_word_fn read_word;
};

struct system_bus 
{
        uint8_t memory[MEMORY_SIZE];
        struct system_bus_ops ops;
};

extern struct system_bus bus;

#endif /* _BUS_S */
