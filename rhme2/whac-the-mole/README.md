# Whac the mole (Challenge 22, Other 200pts)

> Who doesn't like a classic game of whac-the-mole? This time the moles infiltrated deep into the backyard of a poor farmer's family. The moles are ruining the crops, which the farmer desperately needs to provide for his wife and 2 children. Any traveler able to help him by extinguishing the darn things will be greatly rewarded. Are you up for the task?

The first thing that I notice is that the led flashes several times when we are asked to "whack" the mole. I try to output to certain pin, and sometimes it works, sometimes it doesn't. It turns out that the mapping of number of LED flash to the PIN position is randomized on each board reset. So for example it could be that now the mapping is: 1 LED flash is Pin 3, 2 LED flash is Pin 5, and next time it could be different.


I was confused because after more than 20 tries, the mapping that was correct suddenly becomes "wrong". It turns out that I was not *fast* enough. Instead of using logic analyzer to read the LED, I used wiringPi directly, and everything works fine.
