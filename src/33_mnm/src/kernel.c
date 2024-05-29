#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
#include "../include/gdt.h"
#include "libc/string.h"
#include <libc/stdio.h>
#include "../include/idt.h"
#include "../include/interrupts.h"
#include "monitor.h"
#include "memory.h"
#include "pit.h"
#include "song.h"


    struct multiboot_info {
        uint32_t size;
        uint32_t reserved;
        struct multiboot_tag *first;
    };

    int kernel_main();
    // End of the kernel image, defined elsewhere.
    extern uint32_t end;




    int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
      // Initialize the monitor (screen output)
    monitor_initialize();
    init_gdt();
    init_idt();

    init_irq();
    init_kernel_memory(&end);
    init_paging();
    print_memory_layout();
    init_pit();

    asm volatile("sti");
        
        return kernel_main();
    }