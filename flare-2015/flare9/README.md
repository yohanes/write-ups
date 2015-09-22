# Challenge 9

This is a complicated binary that is very hard to debug manually, so I didn't try to debug it. It is also very difficul to understand using a disassembler (so I didn't really try that one either), and it is impossible to decompile. Well, actually I am just very lazy :)

What I did: i use the itrace.dll from intel PIN to see the decision taken by the program. I looked at the last few instructions, and go back to find the branch that decides whether I pass or not.

The interesting thing is: this program compares eax with 41 decimal (which is about the right length for @flare-on.com emails) at 00401C27. My theory is that eax will contain the number of correct characters (in correct position). I modified the trace.cpp to print EAX value at that point. First test is:

     ****************************@flare-on.com

Which should generate 13 (the @flare-on.com should be correct), asterisk is not a valid email character. One problem: this is slow, it takes about 5.5 seconds on my laptop.

In retrospect, I should have just patched with exitcode (like what you can see in my solution to the last challenge).

I can brute for it the dumb way, but it will take many hours. So I did it in two steps, first, I will test which characters are used in the email address. So I tested:

    aaaaaaaaaaaaaaaaaaaaaaaaaaaa@flare-on.com 
    
and see how many character are correct

    bbbbbbbbbbbbbbbbbbbbbbbbbbbb@flare-on.com 

and see how many character are correct. 

and so on. If `eax` value is 13, then the character is not used. I waited about 6 seconds times 72 character (set of valid email addreses) which is around 8 minutes for this first stage. You can see [my script](stage1.py) for this.

I found that the characters used are:

    chars = "_afhilmnorstuv13I"

Only 17 characters, at most I will need 17*28 characters = 476 tries. With 6 seconds per try, it will take less than an hour. I could have optimized it but decided that I just run it, and within about 20 minutes, I got the answer. The code is in [stage2.py](stage2.py).
