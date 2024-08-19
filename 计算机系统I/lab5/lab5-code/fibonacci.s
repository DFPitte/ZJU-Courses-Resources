    .text
    .globl fibonacci
fibonacci:
    # 检查基础情况
    li      t0, 2
    blt     a0, t0, base_case  # 如果 n < 2, 进入基本情况处理

    # 为递归调用保存必要的寄存器
    addi sp, sp, -24 # 为ra, a0, t1腾出空间
    sd ra, 16(sp) # 保存返回地址
    sd a0, 8(sp)  # 保存当前的n值
    sd t1, 0(sp)  # 保存t1

    # 计算 fibonacci(n-1)
    addi a0, a0, -1
    call fibonacci
    mv  t1, a0 # 将结果保存到t1

    # 计算 fibonacci(n-2)
    ld a0, 8(sp) # 从栈恢复原始的n
    addi a0, a0, -2
    call fibonacci
    add  a0, a0, t1 # a0 = fibonacci(n-1) + fibonacci(n-2)

    # 恢复寄存器并从递归返回
    ld  t1, 0(sp)  # 恢复t1
    ld  ra, 16(sp)  # 恢复ra
    addi sp, sp, 24 # 释放栈空间
    ret

base_case:
    li      a0, 1               # 对于 n = 0 或 n = 1，返回 1
    ret
