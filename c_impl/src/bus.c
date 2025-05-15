#include "bus.h"

static uint8_t read_byte(struct system_bus *bus, uint16_t addr);
static void write_byte(struct system_bus *bus, uint16_t addr, uint8_t data);

struct system_bus bus = {
        .memory = {0},
        .ops = {
                .read_byte = read_byte,
                .write_byte = write_byte,
        }
};

static uint8_t read_byte(struct system_bus *bus, uint16_t addr)
{
        return bus->memory[addr];
}

static void write_byte(struct system_bus *bus, uint16_t addr, uint8_t data)
{
        bus->memory[addr] = data;
}

