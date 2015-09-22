import time
current_milli_time = lambda: int(round(time.time() * 1000))


#a = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
a = "IJKLMNOPQRSTUVWXYZ"
a += "abcdefghijklmnopqrstuvwxyz"
#a += a.lower()
a += "0123456789!#%&'+-/=?^_`{|}~."
print a
print len(a)
import os

flare = '****************************@flare-on.com'

total = 0

def writeres(i):
    with open("res.txt", "a+") as f:
        f.write(i)

for i in a:
    print "testing ", i
    inx = flare.replace('*', i)
    with open("inp.txt", "w") as f:
        f.write(inx)        
    cmd = "c:\\pin-2.14-71313-msvc12-windows\\pin_bat.bat -t itrace.dll -- \\gitwork\\flare9\\you_are_very_good_at_this.exe < inp.txt"
    t1 = current_milli_time()
    os.system(cmd)
    t2 = current_milli_time()
    t = (t2-t1)/1000.0
    total += t
    print t, "second"
    print "total ", total, " second"
    with open("itrace.out", "r") as f:
        x = f.read()
        x = int(x.strip())
        x -= 13
        
    if x>0:
        print "IN USE: ", i, x
        writeres(i)
    else:
        print "NO: ", i
