# Jumpy (Chal 5, 100pts)

>> We really need access to this lab protected with an Arduino-based access control system. Our operatives obtained a flash dump from a non-personalized engineering sample, but we are having trouble reverse engineering it.
>> Can you help us get the password to get through?

Please note: after solving this outside of the device, you need to enter the password *on* the RHME device to get the flag.

In this task we are given a hex and ELF file. This is one of the tasks that can be solved without having the RHME device.  When we run the ELF, using another Arduino Nano or using simulavr, we will be presented with a password query.

The "Jumpy" in the title is because the program seems to jump around checking if our password is correct. This is accomplished by setting up stack contents so that when a subroutine returns, it will return to another subroutine.

Since this is the first AVR program that I reversed, I was not really sure about my static analysis capability, so the easiest way for me was to run `simulavr`. Using the trace option, I was able to see all the addresses of the subroutines.

The checks are done per two characters, overlapping with previous check, for example, the first check is: `ord(password[0])*ord(password[1])==0x13b7`. We can find that the factor is 7, 7, and 103, and since passwords uses printable characters we can guess that first character and second character is `1` and `g`, but the order may be `g` then `1`.


    620:   cf 93           push    r28
    622:   df 93           push    r29
    624:   cd b7           in      r28, 0x3d       ; 61
    626:   de b7           in      r29, 0x3e       ; 62
    628:   80 91 2e 01     lds     r24, 0x012E     ;  0x80012e   -> first char
    62c:   48 2f           mov     r20, r24
    62e:   50 e0           ldi     r21, 0x00       ; 0
    630:   80 91 2f 01     lds     r24, 0x012F     ;  0x80012f  -> second char
    634:   28 2f           mov     r18, r24
    636:   30 e0           ldi     r19, 0x00       ; 0
    638:   42 9f           mul     r20, r18        ; a*b
    63a:   c0 01           movw    r24, r0         ; copy to r25:24
    63c:   43 9f           mul     r20, r19        ; *0
    63e:   90 0d           add     r25, r0         ;
    640:   52 9f           mul     r21, r18        ; *0
    642:   90 0d           add     r25, r0         ;
    644:   11 24           eor     r1, r1
    646:   87 3b           cpi     r24, 0xB7       ; 183     'g' '1' or '1' 'g'
    648:   93 41           sbci    r25, 0x13       ; 19


The second check is `ord(password[1]) + ord(password[2]) == 0xA7`. We were not sure if `password[1]` is `1` or `g`, if it is `1`, then the second character will be `v`, otherwise it will be `@`. 

    5a0:   80 91 2f 01     lds     r24, 0x012F     ;  0x80012f 'char 1'
    5a4:   28 2f           mov     r18, r24
    5a6:   30 e0           ldi     r19, 0x00       ; 0
    5a8:   80 91 30 01     lds     r24, 0x0130     ;  0x800130  'char 2'
    5ac:   88 2f           mov     r24, r24
    5ae:   90 e0           ldi     r25, 0x00       ; 0
    5b0:   82 0f           add     r24, r18
    5b2:   93 1f           adc     r25, r19
    5b4:   87 3a           cpi     r24, 0xA7       ; 167  '@' or 'v'
    5b6:   91 05           cpc     r25, r1
    5b8:   51 f4           brne    .+20            ;  0x5ce

There are more series of checks like these. If you didn't solve the first challenge, this is a good simple exercise to do the rest.

The final password is `g1v3_1t_t0_m3`

