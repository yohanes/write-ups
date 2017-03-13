# Secret Sauce (Challenge 19, Other, 300pts)

## Problem Description
We managed to capture a group of spies at our premises. Our specialists in enhanced interrogation techniques worked through the entire night but did not manage to retrieve any information.

Luckily, we intercepted the spy as they were trying to chew and swallow the Arduino Nano device that they were carrying in their pocket. The device is protected with a password and the Pure Software Exploitation Team applied all the tricks they have but did not find any way to guess the secret password.

Can you find the correct password and get the secret data stored on the device?

## Solution

At first I was quite sure that this will involve SPI, because of the word "spies" and also "secret sauce" (SS = slave select in SPI). But I was wrong, this has nothing to do with SPI, but this is just a timing attack. The challenge asks for a password:

    Welcome to Secure Encryption System(SES)!
    Authentication step.
    Input provided secret password.
    If you lost your password call the customer service. >

I always used the same algorithm when brute forcing the challenges:

* try sending chr(0) to chr(255) to see if output is changed
* try sending increasing number of 'A's (A, AA, AAA)

While doing this, I recorded the time by dumping the request/response using sigrok. The timing changes slightly when the length is 15 characters. So I started to do timing attack, and the result is: `TImInG@ttAkw0rk`. I was a bit disappointed that it opens up a new challenge.


    Password is correct!
    ************************************************
    Authentication complete. Welcome to the system!
    Now you can encrypt messages up to 32 bytes.
    Input data to encrypt:

Entering something shows something about true random nonce. 
 
    True Random Nonce: 0b72680fa33d76ac9c03a0573de6e4c3
    Encryption:     04d462e17f2d7edc64bc872f886edd64dde278b2b253d87faf4252229c9ed882
    Input data to encrypt:


Since reading the solution of last year challenges, I always try to put all analog PINS to ground everytime I found a random number generator. Having done that, I got a fixed nonce. I did several experiments:

* encrypting a character produce 32 byte output (64 hex characters)
* entering blank string only produces 16 byte output
* encrypting single character only changes the first byte (for example: encrypting 'a' then 'b', only the first byte changes)
* encrypting two characters changes a lot of bytes compared to one character
* encrypting two characters that differs a bit ('aa' and 'ab') produces input that only differs one byte (aa vs ab: only the second byte changes)

It seems that the output is: encryption of blank ^ plaintext ^ something

I still don't understand what or how the flag will show up, but I made a guess: may be "something" is the flag, so by doing input ^ ouput ^ encryption of blank, I got the flag.


