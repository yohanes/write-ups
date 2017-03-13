#Casino (Challenge 9, Exploitation, 150 pts)

## Problem Description
Welcome to our casino, Riscure Royale! Please enjoy your stay by playing a game, or drink something at our bar. Reach 1000 credits and you will be rewarded with a special prize.

We have seen loads of cheaters lately, so we have extra guards walking around. Do not feel threatened by them, they will only kick out the people that cheat. Of course, once you earn a lot of money they will start investigating the matter. Better spend some money at our bar if this happens.

PS. We all know casinos are scams.

## Solution

At first I didn't know what to do since all inputs seems to be checked, but when we have a coupon we can exchange it for a drink, and here we found a format string bug.

We just need to play until we get a coupon, and dump a section of RAM everytime, play again until we get a coupon, until we get the flag in memory.


