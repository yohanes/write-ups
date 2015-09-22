import time
current_milli_time = lambda: int(round(time.time() * 1000))

import os

chars = "_afhilmnorstuv13I"

flare = '****************************@flare-on.com'

total = 0

def check(inx):
    global total
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
    return x


idx = 0
last_correct = 13
while '*' in flare:
    lflare = list(flare)    
    for i in chars:
        lflare[idx] = i
        test = "".join(lflare)
        print "testing ", test
        a = check(test)
        print "Result ", a
        if a>last_correct:
            print "Good ", test
            last_correct = a
            flare = test
            break
    idx += 1
