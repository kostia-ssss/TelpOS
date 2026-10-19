
#include "mouse.h"
#include "io.h"
#include <stdbool.h>
#include <stdint.h>

#define PS2_STATUS 0x64
#define PS2_DATA   0x60

#define PS2_OUTPUT_FULL  0x01
#define PS2_INPUT_FULL   0x02
#define PS2_AUX_DATA     0x20

#define MOUSE_ACK 0xFA

static bool mouse_data_ready(void) {
    uint8_t status = inb(PS2_STATUS);

    return (status & PS2_OUTPUT_FULL) != 0 &&
           (status & PS2_AUX_DATA) != 0;
}

bool mouse_try_read_byte(uint8_t *out) {
    if (!mouse_data_ready()) {
        return false;
    }

    *out = inb(PS2_DATA);
    return true;
}

static bool ps2_wait_write(void) {
    for (uint32_t i = 0; i < 1000000; i++) {
        if ((inb(PS2_STATUS) & PS2_INPUT_FULL) == 0) {
            return true;
        }
    }

    return false;
}

static bool ps2_read_controller_byte(uint8_t *out) {
    for (uint32_t i = 0; i < 1000000; i++) {
        if ((inb(PS2_STATUS) & PS2_OUTPUT_FULL) != 0) {
            *out = inb(PS2_DATA);
            return true;
        }
    }

    return false;
}

static bool mouse_write(uint8_t value) {
    if (!ps2_wait_write()) {
        return false;
    }

    outb(PS2_STATUS, 0xD4);

    if (!ps2_wait_write()) {
        return false;
    }

    outb(PS2_DATA, value);

    uint8_t response;

    for (uint32_t i = 0; i < 1000000; i++) {
        if (mouse_try_read_byte(&response)) {
            return response == MOUSE_ACK;
        }
    }

    return false;
}

bool mouse_init(void) {
    uint8_t config;

    // Увімкнути допоміжний канал.
    if (!ps2_wait_write()) {
        return false;
    }

    outb(PS2_STATUS, 0xA8);

    // Прочитати конфігурацію контролера.
    if (!ps2_wait_write()) {
        return false;
    }

    outb(PS2_STATUS, 0x20);

    if (!ps2_read_controller_byte(&config)) {
        return false;
    }

    // Увімкнути канал; поки не вмикаємо IRQ12.
    config &= (uint8_t)~0x20;
    config &= (uint8_t)~0x02;

    if (!ps2_wait_write()) {
        return false;
    }

    outb(PS2_STATUS, 0x60);

    if (!ps2_wait_write()) {
        return false;
    }

    outb(PS2_DATA, config);

    // Увімкнути надсилання пакетів руху.
    if (!mouse_write(0xF4)) {
        return false;
    }

    return true;
}
