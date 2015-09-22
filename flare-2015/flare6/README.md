# Challenge 6

My way of solving this is a bit convoluted, but it works, and I don't need to understand the algorithm. By using `dex2jar` and `JD-GUI`, we understand that the Java code only calls native ARM code.

I don't have a deep understanding of ARM assembly, and I am afraid that I am going to get frustrated reimplementing the algorithm, so again: I let the code solve it.

From what I understand: the code takes 2 bytes of input at a time, does some computation to produce a chunk of memory, that is compared to the correct memory using `memcmp`. So this is how I attacked the problem:

1. create an `LD_PRELOAD` file to intercept `memcmp`
2. create a C code to call the `libvalidate.so`, passing my own function pointers for `JNIEnv`
3. create a Python script to generate possible pairs of characters from valid email characters (actually this can be done in C, I just want to see the list and be able to edit it before bruteforcing it, e.g: removing "@?" pairs  except "@f" because it must have "@flare-on.com" )

Here is the idea: we will brute force pair by pair. When bruteforcing first pair, I will set `_pos_` to 0, and i will try out all possible pairs by calling `validate`, when `memcmp` returns 0, i will set `_stop_` to be 1. When i set `_stop_` to 1, I am telling `strlen` to return 0, which will stop the loop.  Obtaining the first pair, I will go to the next position by setting `_pos_` to 1 and call `validate` again. This time `memcmp` will not imediatelly stop after comparing the first pair (because we already know the correct first pair).

One problem: how to set `_pos_` and `_stop_` from main? The first thing that occur to me is just to override a library function that is unused in the library, and for this i use `strrchr`. 

And I just run the script and wait.

It turns out that the string is not exactly what flare-on wants even though that it got accepted by the app.

I found `Should_havAYg0ne_to_tashi_$tation@flare-on.com` and the correct one should be: `“Should_have_g0ne_to_tashi_$tation@flare-on.com`
