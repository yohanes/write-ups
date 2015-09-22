import scipy.misc
import sys


a = scipy.misc.imread("input.png")

bitpos = 0
stegmin = 2**bitpos - 1
mask = 1<< bitpos

res = ''
tmp = ''
endian = 0 

perm = [0,1,2]

for i in range(0, a.shape[0]):
    for j in range(0, a.shape[1]):
        for k in range(0, 3):
            km = perm[k]
            rgb = a[i][j][km]
            #print >>sys.stderr, "got rgb ", rgb, rgb & mask
            onebit = (rgb & mask)>0
            if rgb>stegmin:
                if endian==1:
                    tmp = ("1" if onebit else "0") + tmp
                else:
                    tmp += ("1" if onebit else "0")
            else:
                #print >>sys.stderr, "ignore"
                if endian==1:
                    tmp = "0" + tmp
                else:
                    tmp += "0"
        if len(tmp)>=8:
            c = tmp[:8]
            c = "".join(list(reversed(c)))
            #print c, chr(int(c,2))
            tmp = tmp[8:]
            res += chr(int(c, 2))
 
with open("res.exe", "wb") as f:
        f.write(res)
