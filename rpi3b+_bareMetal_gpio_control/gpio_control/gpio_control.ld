/* gpio_control.ld - Linker Script */
ENTRY(_start)

SECTIONS {
    . = 0x81000;
    
    .text : {
        *(.text*)
    }
    
    .data : {
        *(.data*)
    }
    
    .bss : {
        *(.bss*)
    }
}

