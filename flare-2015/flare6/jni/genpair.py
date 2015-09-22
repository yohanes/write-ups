a = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
a += a.lower()
a += "0123456789!#%&'*+-/=?^_`{|}~.@"
for i in a:
    for j in a:
        print '"%s%s", ' %(i,j)
