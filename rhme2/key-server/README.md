# Key Server (Challenge 1, Crypto 200pts)

>> We have received a portable asymmetric key storage for evaluation purposes. This portable device was manufactured by Ebian Corp to facilitate secure communications with customers. It generates and stores adminstrators' public keys. Customers can use this repository to find the public key of the admin they want to contact, and administrators can use this repository to update their key information. If this fancy keychain passes the test we are going to give them away like candy, secure candy.

It took me a while to read all the attacks against RSA until I found [common factor attacks](http://www.loyalty.org/~schoen/rsa/), at first I thought it might be [Bleichenbacher's Attack](https://www.ietf.org/mail-archive/web/openpgp/current/msg00999.html) but it didn't work.

Checking the GCD of all the keys, I found that Alice's and Gary's key have common GCD. The rest  is already documented in many places (for example [this](http://justrocketscience.com/post/rsa-common-prime))


