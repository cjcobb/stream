# stream
I'm taking an algorithms class at Penn, CIS 334, taught by Sudipto Guha.
We learn a lot of beautiful algorithms, most of which are streaming algorithms.
I've decided to implement some of them.

Currently I only have one algorithm:

Counting distinct items in a dataset (two algorithms)
1. Hash to 1...n^3. Output t*n^3/s, where t = 96 / eps^2 and s is tth smallest hash value
O(t*log(n)) space
2. Hash to 1...n^3. Find smallest t such that last t bits of hashed val are zero,
and less than s = 576 / eps^2 hash last t bits to 0. Output r * 2^t, where r is number of
elements where last t bits of hash are zero.
O(s*log(n))

