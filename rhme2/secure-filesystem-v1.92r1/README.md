# Secure Filesyste v1.92r1(Challenge 3, Crypto 150pts)

## Problem description

After the horrible debacle of the first file system, we got together again, invited our friend Mr. Wodka and waterproofed the secure file system. You can test it again, but this time it uses unbreakable encryption.

The filesystem allows you to request the contents of one or more available files by using the following
format:

    token#<filename>[:<filename>]

So for example, a request would be:

    897703036b2e18116b36353d92ac3dd978845fc99a735b8a3a3a9b3cc5239fdf4572157296903a0237a4aaeeaa8f3d15#joke.txt

Some example files (token | call):

    897703036b2e18116b36353d92ac3dd978845fc99a735b8a | dfd0f4a25b7d529e89ac030c2b681e93831e95a8186823b9 | cat.txt
    897703036b2e18116b36353d92ac3dd978845fc99a735b8a | f2bca35d472116dc6d5bebe96f1a3af249be78c63219a0dc | cat.txt:finances.csv
    897703036b2e18116b36353d92ac3dd978845fc99a735b8a | 7eed666977d3861dbaefd16b2ed7dc5b639e51853ca6e7b3 | cat.txt:finances.csv:joke.txt
    897703036b2e18116b36353d92ac3dd978845fc99a735b8a | 51d915246394ce976f8768cf3300087cb5b9958bbec30f9c | cat.txt:joke.txt
    897703036b2e18116b36353d92ac3dd978845fc99a735b8a | ae2a5a38b4d03f0103bce59874e41a0df19cb39b328b02fa | finances.csv
    897703036b2e18116b36353d92ac3dd978845fc99a735b8a | c66b5e48f5e600982724eca3804fb59b7b0f395a6e17e1ce | finances.csv:joke.txt
    897703036b2e18116b36353d92ac3dd978845fc99a735b8a | 3a3a9b3cc5239fdf4572157296903a0237a4aaeeaa8f3d15 | joke.txt

Can you access any file you're not supposed to?

## Solution

At first I thought that the solution would be similar to the  previous crypto challenge (hash length extension), but it didn't work. After watching [33C3 Nintendo hacking](https://media.ccc.de/v/33c3-8344-nintendo_hacking_2016), I looked at other console hacks in the past, and the [PS3 hack](https://events.ccc.de/congress/2010/Fahrplan/events/4087.en.html) gives me an idea that it might be similar. This is because there is this same number/nonce used in the input, and the  v1.92r1 now suddenly makes sense as ECC curve name.

Since I am not really sure if this is the attack that will work, and there are already several implementations of this attack available at github, I just tried one of solutions found on github (I didn't remember which), and got the answer.

