# Challenge 5

In this challenge we are given a pcap file and an executable file. In the Pcap file we can see several HTTP Post, each is 4 bytes. If we merge them together, we got:

      UDYs1D7bNmdE1o3g5ms1V6RrYCVvODJF1DpxKTxAJ9xuZW==
      
It looks like bse64 encoded string, but when we try to decrypt it, it produces junk. 

Its time to run the file. When trying to run the file it says that `key.txt` not found. So I tested sending `abcdef  \r\n`, and watch the data sent. The data sent is: 

     X87e1SRiHyf/Fq==


I still haven't figured out what the algorithm is, so its time to open it in disassembler. Quickly looking at the code can see the basic stuff: it sends the content of the file using encryption key `flarebearstare`. I don't really understand what the encryption function does, it uses a lot of mmx instruction, with alphabet table, so it must have encoded something.

Like challenge no 2: I don't want to reimplement this, so again I just copy pasted the encryption code from `objdump`. I have a test input and output (`abcdef  \r\n` and the one that I received from network), so I can test the encryption code, and compare it. Running `flare5test`, I got the output:

    x87E1srIhYF/

Ok, some characters are missing, its probably because I didn't pad the data to 4 bytes alignment, so its fine. What we can immediatelly see, ist that it is base64 encoding, but we need to toggle the case (lower to upper and vice versa). I don't want to write a base64 decoder, this small script is enough to generate input for my C bruteforcer:
   
    echo UDYs1D7bNmdE1o3g5ms1V6RrYCVvODJF1DpxKTxAJ9xuZW== | tr A-Za-z a-zA-Z | base64 -d| hexdump -ve '1/1 "%.2X"'    

    B9DC92D5DEC19CC0DED4EDC6E4C4B5BFAAD1C9CBD5A1D8DFD5D3D792D5DA8FD5D4CF
    
So now we can start brute forcing this. Just put in `A`, encrypt it, compare the encrypted with the target `B9`, if not, try `B` and so on (see [flare5.c](flare.5))
