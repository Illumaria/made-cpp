.text

.global count_det

count_det:

    push {r4-r7}

    ldr r1, [r0], #4
    mov r2, r1
    mov r3, r1
    ldr r1, [r0], #4
    mov r4, r1
    mov r5, r1
    ldr r1, [r0], #4
    mov r6, r1
    mov r7, r1
    ldr r1, [r0], #4
    mul r5, r1, r5
    mul r6, r1, r6
    ldr r1, [r0], #4
    mul r2, r1, r2
    mul r7, r1, r7
    ldr r1, [r0], #4
    mul r3, r1, r3
    mul r4, r1, r4
    ldr r1, [r0], #4
    mul r4, r1, r4
    mul r7, r1, r7
    ldr r1, [r0], #4
    mul r3, r1, r3
    mul r6, r1, r6
    ldr r1, [r0], #4
    mul r2, r1, r2
    mul r5, r1, r5

    sub r0, r2, r3
    add r0, r4
    sub r0, r5
    add r0, r6
    sub r0, r7

    pop {r4-r7}
    bx lr
