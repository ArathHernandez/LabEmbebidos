                .data
x:              .int 0
result:         .word 0    
format_input:   .asciz "Enter value of x: "
format_scan:    .asciz "%d"
format_output:  .asciz "Result: %d\n"

.text
.global main
.extern printf
.extern scanf

main:
    push    {ip, lr} 
    LDR     r0, =format_input
    BL      printf

    LDR     r0, =format_scan
    LDR     r1, =x
    BL      scanf

    MOV     r3, #6
    LDR     r4, =x
    LDR     r4, [r4]
    MUL     r5, r4, r4
    MUL     r2, r5, r3

    MOV     r3, #9
    MUL     r6, r3, r4
    ADD     r7, r2, r6

    ADD     r7, r7, #2

    LDR     r1, =result
    str     r7, [r1]
    LDR     r0, =format_output
    LDR     r1, =result
    LDR     r1, [r1]
    BL      printf

    pop     {ip, pc}
