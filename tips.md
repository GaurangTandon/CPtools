# Tips for CP

Tips are separated by categories

## General code guidelines

1. Adding several `#include` statements to your code, or that innocent `#include<bits/stdc++.h>` can scale your code's compilation time to upto 2-3 seconds, which matter a lot in quickly solving A or B problems. So, include only those libraries which are necesary.

## General algo guidelines

1. **Stackoverflow**: The recursion stack is limited to around 350,000 on an average machine. This solution won't TLE, but will give a memory limit exceeded error. You'll get an error similar to `SIGSEGV: Invalid memory reference`, and in gdb, you will get the line number as the start of the method header. In general, avoid using recursion for such large cases, use iteration instead.

## Sieve

1. Do not create a sieve unless you want to check the primality of a number more than once. Besides that, decide at all if you actually require the number to be prime in your code.
   Refer to [bad solution](https://codeforces.com/contest/1076/submission/45601999), [best solution](https://codeforces.com/contest/1076/submission/45626302)

# TODO:

1. automated web scraper for downloading the test cases and diffing them with expected output on F8 press
2. a bash utility to cat the header file declarations and the actual file before compiling and running them. sort of like `cat fileHeaders actualCPP && gcc newfile`. Reason: so many fileHeaders are obstacly to look at.
