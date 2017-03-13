import sys

op_len = {0: 1, 1: 2, 2: 2, 3: 2, 4: 4, 5: 4, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2, 11: 2, 12: 2, 13: 2, 14: 2, 15: 2, 16: 2, 17: 2, 18: 2, 19: 1, 20: 3, 21: 2, 22: 2, 23: 3, 24: 3, 25: 2, 26: 2, 27: 2, 28: 2, 29: 1, 30: 1, 31: 1};

opnames = [
	"NOP",
	"PUSH",
	"POP",
	"MOV",
	"MOV.L",
	"MOV.H",
	"GET",
	"PUT",
	"ADD",
	"SUB",
	"XOR",
	"AND",
	"OR",
	"COMP",
	"SHL",
	"SHR",
	"ROL",
	"ROR",
	"CALL",
	"RET",
	"JUMP4",
	"JUMP",
	"CMP",
	"JS",
	"JNZ",
	"OPCODE_19",
	"OPCODE_1a",
	"READ",
	"PUTS",
	"NOT",
	"OPCODE_1e",
	"OPCODE_1f",
	"OPCODE_20",
	"OPCODE_21"
]

regnames = [
	"R0",
	"R1",
	"R2",
	"R3",
	"R4",
	"R5",
	"SP",
	"IP",
	"FLAG"
]

class Line:

	def __init__(self, addr, sline):
		self.s = sline
		self.addr = addr

	def encode_r1(self,regname):
		c = regnames.index(regname.upper())
		return c << 4;

	def encode_r2(self,regname):
		return regnames.index(regname.upper()) 

	def asm(self, labels):
		m,o = self.s.split(" ", 1)
		m = m.upper()
		code = opnames.index(m)
		res = chr(code)
		if m=="MOV.L" or m=="MOV.H":
			a, b = o.split(",")
			a = a.strip()
			b = int(b.strip(), 16) 
			res += chr(self.encode_r1(a))
			res += chr((b&0xff00)>>8)
			res += chr(b&0xff)
		if m=="JNZ" or m=="JUMP4":
			b = o.strip()
			dst = labels[b]
			if dst % 4!=0:
				print "Dest not multiple of 4" , dst%4
				exit(0)

			b = dst/4
			res += chr((b&0xff00)>>8)
			res += chr(b&0xff)
	
		if m=="PUTS":
			a = o.strip()
			res += chr(self.encode_r1(a))
		if m in ["GET" ,"PUT", "CMP", "OR", "ADD", "SUB", "SHR", "SHL", "XOR", "MOV"]:
			a, b = o.split(",")
			a = a.strip()
			b = b.strip()
			res += chr(self.encode_r1(a)|self.encode_r2(b))

		return res	

	def __repr__(self):
		return self.s


with open(sys.argv[1]) as f:
 	lines = f.read().splitlines()


addr = 0
labels = {}	
codes = []
for line in lines:
	a = line.strip()
	if "#" in a:
		a = a[:a.index("#")]
	a = a.strip()
	if len(a)==0:
		continue
	if a.endswith(":"):
		labels[a[:-1]] = addr
	else:
		m,o = a.split(" ", 1)
		m = m.upper()
		code  = opnames.index(m)
		codelen = op_len[code]
		l = Line(addr, a)
		codes.append(l)
		addr += codelen

print codes
allres = ''
for code in codes:
	a = code.asm(labels)
	print code.s
	print a.encode("hex")
	allres += a

with open("res.bin", "wb") as f:
	f.write(allres)


