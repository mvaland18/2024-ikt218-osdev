#include "idt.h"
#include "./libc/string.h"
#include "memory.h"
#include "interrupts.h"
#include "libc/stddef.h"

// Define an IDT with 256 entries
static struct idt_entry_t idt[IDT_ENTRIES];
static struct idt_ptr_t idt_ptr;

extern void idt_flush(uint32_t);

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector = sel;
    idt[num].zero = 0;
    idt[num].flags = flags | 0x60;
}

void init_idt() {
    idt_ptr.limit = (sizeof(struct idt_entry_t) * IDT_ENTRIES) - 1;
    idt_ptr.base = (uint32_t)&idt;

    for (int i = 0; i < IDT_ENTRIES; i++) {
    idt[i].base_low = 0x0000;
    idt[i].base_high = 0x0000;
    idt[i].selector = 0x08;
    idt[i].zero = 0x00;
    idt[i].flags = 0x8E;

	int_handlers[i].handler = NULL;
  }

    memset(&idt, 0, sizeof(struct idt_entry_t) * IDT_ENTRIES);

    // Set individual IDT entries (ISR handlers)

    init_interrupts();

    
    idt_load(&idt_ptr);
}

void idt_load(struct idt_ptr_t *idt_ptr) {
    asm volatile("lidt (%0)" : : "r" (idt_ptr));
}
