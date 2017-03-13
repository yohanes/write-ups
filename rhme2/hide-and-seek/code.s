xor flag,flag
xor r1,r1
mov.h r1, 0007
mov.l r1, 0000
xor flag, r1
xor r1, r1
mov.l r3, 1
loop:
get r2, r1
puts r2
add r1, r3
jump4 loop
