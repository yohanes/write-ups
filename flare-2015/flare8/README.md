# Challenge 8

This is a steganography challenge. I never liked these kinds of challenges.

The first part is easy: extracting the base64 text to get the image. I used `stegsolve` and saw that there is something strange in the top part of the image for the bit 0 of R, G and B component. I tried clicking many combinations in `stegsolve` but It didn't produce something meaningful.

I tried looking for `"fireeye steganography"` on Google and saw some articles about embedding executable inside an image. So I tried to do things manually:

1. I extracted several bits  from R, and G, and B (the 0th bit of each component)
2. I made a guess that the content should be another EXE file, so it should start with MZ (or 01001101 01011010 in binary)
3. I tried to make an arrangement such that the bits from R, G and B forms the MZ

The result is [steg.py](steg.py) a very slow python script (it was a very quick and dirty solution).

Looking at the result, the first thing to try is:

    strings res.exe     
    Im_in_ur_p1cs@flare-on.com

Great, no need to reverse anything
