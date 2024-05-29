#include "interrupts.h"
#include "common.h"
#include "libc/stddef.h"
#include "libc/stdio.h"
#include "monitor.h"
#include "libc/string.h"
#include "input.h"
#include "pit.h"

#define TICKS_PER_SECOND 200

void timer_handler(registers_t* regs, void* data) {//Printer hvert 10sekund
    static uint32_t tick = 0;
    tick+=10;  

    if (tick % (TICKS_PER_SECOND * 10) == 0) {  
        char buffer[50];
        int_to_string((tick) / TICKS_PER_SECOND, buffer);
        monitor_write("Uptime: ", 10);
        monitor_write(buffer, strlen(buffer));
        monitor_write(" seconds\n", 9);
    }
}

void keyboard_handler(registers_t* regs, void* data) {
    uint8_t scancode = inb(0x60);
    char c = scancode_to_ascii(&scancode);

    if (c) {
        monitor_put(c);
    }
}

void irq2_handler(registers_t* regs, void* data) {
    monitor_write("IRQ2 handled\n", 13);
}

void init_irq() {
    for (int i = 0; i < IRQ_COUNT; i++) {
        irq_handlers[i].data = NULL;
        irq_handlers[i].handler = NULL;
        irq_handlers[i].num = i;
    }
    register_irq_handler(IRQ1, keyboard_handler, NULL);
    register_irq_handler(IRQ2, irq2_handler, NULL);
}


void register_irq_handler(int irq, isr_t handler, void* ctx) {
    irq_handlers[irq].handler = handler;
    irq_handlers[irq].data = ctx;
}

void irq_handler(registers_t regs) {
    if (regs.int_no >= 40) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);

    struct int_handler_t intrpt = irq_handlers[regs.int_no];
    if (intrpt.handler != 0) {
        intrpt.handler(&regs, intrpt.data);
    }
}
