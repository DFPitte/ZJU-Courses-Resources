from scapy.all import *

r = rdpcap("dnscap.pcap")

a = b""
b = b""
c = b""
new = b""

f = open("flag.png", "wb")

for i in range(0, len(r)):
    if r[i].haslayer(DNSQR) and not r[i].haslayer(DNSRR):
        a = r[i][DNSQR].qname
        b = a.replace(b".skullseclabs.org.", b"")
        b = b.replace(b".", b"")
        b = bytes.fromhex(b.decode())[9:]

        if b == c:
            continue

        c = b

        if 6 < i < 365:
            new += b

f.write(new)

f.close()