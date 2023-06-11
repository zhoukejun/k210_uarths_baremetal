    .section .text.start, "ax"
    .global _start

_start:
    j 1f
    .word 0xdeadbeef
    .align 3
    .global g_wake_up
g_wake_up:
        .dword 1
        .dword 0
1:

    /* get cpu id */
    csrr a0, mhartid

    /* other cpu core, jump to cpu entry directly */
    bnez a0, secondary_cpu_entry
    j primary_cpu_entry

secondary_cpu_entry:
loop:
    wfi
    j loop

primary_cpu_entry:
//   tail main
    j main
