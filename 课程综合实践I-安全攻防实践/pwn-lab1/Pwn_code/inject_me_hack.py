from pwn import *
context.log_level ='DEBUG'
context.arch = 'x86'
p = remote("172.28.112.1","55187")
add_code = b"\xf3\x0f\x1e\xfa\x8d\x04\x37\xc3"
sub_code = b"\xf3\x0f\x1e\xfa\x89\xf8\x29\xf0\xc3"
and_code = b"\xf3\x0f\x1e\xfa\x89\xf8\x21\xf0\xc3"
or_code = b"\xf3\x0f\x1e\xfa\x89\xf8\x09\xf0\xc3"
xor_code = b"\xf3\x0f\x1e\xfa\x89\xf8\x31\xf0\xc3"
#p.interactive()
p.sendafter(b"Request-1: give me code that performing ADD",add_code)

p.sendafter(b"Request-2: give me code that performing SUB",sub_code)
p.sendafter(b"Request-3: give me code that performing AND",and_code)
p.sendafter(b"Request-4: give me code that performing OR",or_code)
p.sendafter(b"Request-5: give me code that performing XOR",xor_code)
p.interactive()
