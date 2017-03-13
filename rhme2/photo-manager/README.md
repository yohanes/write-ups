# Photo Manager (Challenge 7, Exploitation 100pts)

## Problem Description

We have recently been informed that a group of hackers exploited a vulnerability in a PC within another very secure network. Our operative says the hacker in charge took a snapshot of the password, which they stored in their secret hidden-away database.

Today we found a photo manager service running on the internet. This service can be linked to the hacker who retrieved the passwords. From the size of the photo manager we can see they stored lots of pictures, so we are hoping they stored the password on their photo manager too. Can you breach their photo manager and take a quick look?

Keep in mind that the flag is 32 characters long and you should disregard the last ‘1’.


## Solution

Trying long input will show a message: 'Stack Cookie corrupted'. I made an assumption that the cookie is just one byte, and just tried sending 0-255 as cookie (excluding 10 and 13, because this is the ENTER). It turns out that the next byte after cookie controls the length of message to print, setting it to 0xff prints the FLAG. Please note that setting it itu some large positive doesn't print anything, the 0xff is considered as negative.

I didn't read the part about *disregard the last '1'*, and I got confused why my flag wasn't accepted, and I even dumped the whole Flash using "%S" format string, before I reread the problem description.

