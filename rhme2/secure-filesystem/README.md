# Secure Filesystem (Challenge 2, Crypto 100pts)

## Problem description

We don't remember why, but we wanted a file system on an AVR328p. After the system was completed we discovered that it lacked basic security. A couple of beers later we came up with what we think is a revolutionary way to do file system permissions. It is now your task to fill in our shoes and test its security.

The filesystem allows you to request the contents of one or more available files by using the following
format:

    token#<filename>[:<filename>]

So for example, a request would be:

    933d86ae930c9a5d6d3a334297d9e72852f05c57#cat.txt:finances.csv

Some example files (token | call):

    96103df3b928d9edc5a103d690639c94628824f5 | cat.txt
    933d86ae930c9a5d6d3a334297d9e72852f05c57 | cat.txt:finances.csv
    83f86c0ba1d2d5d60d055064256cd95a5ae6bb7d | cat.txt:finances.csv:joke.txt
    ba2e8af09b57080549180a32ac1ff1dde4d30b14 | cat.txt:joke.txt
    0b939251f4c781f43efef804ee8faec0212f1144 | finances.csv
    4b0972ec7282ad9e991414d1845ceee546eac7a1 | finances.csv:joke.txt
    715b21027dca61235e2663e59a9bdfb387ca7997 | joke.txt

Can you access any file you're not supposed to?


## Solution

I made several trial to see how the hash works, for example, can I send `cat.txt:cat.txt` with the same hash as `cat.txt`? it turns out we can't. Does adding `:` at the end invalidates the hash? yes. It means that the right side is not parsed then hashed, it is hashed entirely and compared to the left side. The first attack that I could think of is [Length extension attack](https://en.wikipedia.org/wiki/Length_extension_attack), I used [HashPump](https://github.com/bwall/HashPump) using Python API.

I used the default (automatic guessing) feature of hashpump to guess the hash type, and just bruteforced the length, fortunately its a small number (8).


```python
a, b = hashpumpy.hashpump("96103df3b928d9edc5a103d690639c94628824f5", "cat.txt", ":passwd:pepper", 8)
r = a+"#"+b
request(r+"\r\n")
```

The `passwd` file contains the FLAG, the `pepper` file content is `Notasalt`

