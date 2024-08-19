    .text
    .globl bubble_sort
bubble_sort:
    # 输入: a0 = arr (数组的地址), a1 = len (数组长度)
    # 保存寄存器
    addi sp,sp,-32 #腾出栈，修改sp指针
    sd ra,16(sp) #设置返回地址ra
    sd s0,0(sp) #保存帧指针
    addi s0,sp,32 #设置新的帧指针
    li t0,0 #设置t0的值为-1
    j .outer_loop #进入外循环

.outer_loop:  #外循环    
    
    li t1,0 #初始化t1的值为0
    blt t0,a1,.inner_loop #if(t0<len)进入内循环
    j .end

.inner_loop:  #内循环
    slli t2,t1,3 #每个longlong为8字节
    add t2,a0,t2 #将t2置为&arr[t1]
    ld t3,0(t2) #加载t2中的值至t3,即t3=arr[t1]
    ld t4,8(t2) #加载t2+1中的值至t4,即t4=arr[t1+1]
    ble t3,t4,.no_swap #如果t3<t4,则跳过交换

    sd t3,8(t2) #交换元素
    sd t4,0(t2) 

.no_swap: #如果没有交换
    addi t1,t1,1 #t1+=1
    li a2,0
    add a2,a1,-1
    blt t1,a2,.inner_loop #如果t1<a1-1,则继续内循环
    addi t0,t0,1
    bne t0,a1,.outer_loop #如果a1>t0,则继续外循环
.end:  #程序结束，进行返回
    # 恢复寄存器并返回
    ld      ra, 16(sp)        # 恢复返回地址
    ld      s0, 0(sp)        # 恢复帧指针
    addi    sp, sp, 32     # 调整栈指针
    ret                      # 返回


