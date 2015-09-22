import os

with open("CryptoGraph2.exe", "rb") as f:
    r = f.read()

n = 0xcc2    #patch loop count
r = r[:n] + chr(0xA) + r[n+1:]
    
n = 0x11B0    
for i in range(0, 64):
    c = chr(i)
	#patch bit count
    new = r[:n] + c + r[n+1:]
    name = "c-%d.exe" % i
    with open(name, "wb") as f:
        f.write(new)
    os.system(name + " 205")
    os.rename("secret.jpg", name + ".jpg");


