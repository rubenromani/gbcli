#include "bus.h"

static void write_byte(struct system_bus *bus, uint16_t addr, uint8_t data);
static void write_word(struct system_bus *bus, uint16_t addr, uint16_t data);
static uint8_t read_byte(struct system_bus *bus, uint16_t addr);
static uint16_t read_word(struct system_bus *bus, uint16_t addr);

struct system_bus bus = {
        .memory = {0},
        .ops = {
                .write_byte = write_byte,
                .write_word = write_word,
                .read_byte = read_byte,
                .read_word = read_word
        }
};

static void write_byte(struct system_bus *bus, uint16_t addr, uint8_t data)
{
        bus->memory[addr] = data;
}

static void write_word(struct system_bus *bus, uint16_t addr, uint16_t data)
{
        bus->memory[addr] = data & 0xFF;
        bus->memory[addr] = (data >> 8) & 0xFF; 
}

static uint8_t read_byte(struct system_bus *bus, uint16_t addr)
{
        return bus->memory[addr];
}

static uint16_t read_word(struct system_bus *bus, uint16_t addr)
{
        return ((uint16_t)bus->memory[addr+1] << 8 ) | (uint16_t)bus->memory[addr];
}


