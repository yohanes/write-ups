import os
for i in range(0, 1000):
    print "i = ", i
    n =  os.system("CryptoGraph-patched.exe %d" % i)
    if (n<=100):
        print "-------", n
        with open("result.xt", "a+") as f:
            f.write(str(i)+"\n");
    
