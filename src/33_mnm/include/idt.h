#pragma once
#include "libc/stdint.h"

#define IDT_ENTRIES 256

struct idt_entry_t {
    uint16_t base_low;
    uint16_t selector;       
    uint8_t zero;     
    uint8_t flags;       
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr_t {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void init_idt();
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void idt_load(struct idt_ptr_t *idt_ptr);