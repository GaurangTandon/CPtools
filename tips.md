# Tips for CP

Tips are separated by categories

## Contest

1. First read C problem and attempt to solve it, as it gives more poins, since fewer people had solved it. Case in point: [Contest 520](https://codeforces.com/contest/1062) had problem C only slightly tougher than problem A, and problem D was way easier than both B and C.

2. Be good at coming up with self test cases. Just because your code passes the pretests doesn't mean it will pass the system tests.

## Hacking

1. Only get down to hack problems once you have actually read all problems in the contest and made sure that you cannot solve them. In general, for div 2 problems, all problems without trees can be solved pretty easily.
   Case in point: [Contest 520](https://codeforces.com/contest/1062) had first four very easy problems, as opposed to generally two in usual div2 contests.

2. Attempt to hack those solutions which took less than five minutes to accepted. In general, they have a silly logic mistake that enables them to submit faster but incorrectly.
   Example: [this hacked solution](https://codeforces.com/contest/1062/hacks/502444/) was submitted in two minutes.

## General coding

1. Adding several `#include` statements to your code, or that innocent `#include<bits/stdc++.h>` can scale your code's compilation time to upto 2-3 seconds, which matter a lot in quickly solving A or B problems. So, include only those libraries which are necesary.
2. Always use %llu or %lld to take integer inputs. On codeforces custom invocation you can check that using %lf or %f to take integer inputs assigns it a value 0.000000.

## General algo

1. **Stackoverflow**: The recursion stack is limited to around 350,000 on an average machine. This solution won't TLE, but will give a memory limit exceeded error. You'll get an error similar to `SIGSEGV: Invalid memory reference`, and in gdb, you will get the line number as the start of the method header. In general, avoid using recursion for such large cases, use iteration instead.

## Sieve

1. Do not create a sieve unless you want to check the primality of a number more than once. Besides that, decide at all if you actually require the number to be prime in your code.
   Refer to [bad solution](https://codeforces.com/contest/1076/submission/45601999), [best solution](https://codeforces.com/contest/1076/submission/45626302)

# TODO:

1. automated web scraper for downloading the test cases and diffing them with expected output on F8 press
2. a bash utility to cat the header file declarations and the actual file before compiling and running them. sort of like `cat fileHeaders actualCPP && gcc newfile`. Reason: so many fileHeaders are obstacly to look at.
3.

Understand why cin fails for the following

cin >> n >> q;
vector<int> a(n);
getchar();
for(i = 0 to n-1)
a[i] = getchar();
fails for input
4 2 1101

4. learn strings in c++ and use them with cin. like in the case above.
