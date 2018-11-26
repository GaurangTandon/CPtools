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

1. Adding several `#include` statements to your code, or that innocent `#include<bits/stdc++.h>` can scale your code's compilation time to upto 2-3 seconds, which matter a lot in quickly solving A or B problems. So, include only those libraries which are necesary, commment out the rest.
2. Decide upon some standard variable names. Like, `a` for arrays, prefix sum array as `sum`, `s` for strings, etc. Avoid longer names. At max, competitive code has only six distinct variables in any scope, so there can't/shouldn't be much confusion.
3. Use vectors if you're using C++. There's no reason to not use vectors when they are available. They are not only [as fast as plain arrays](https://stackoverflow.com/questions/26189531/how-is-stdvector-faster-than-a-plain-array), but are also dynamically sized with constant access time. They also allow sorting operations, any index insertion/deletion, etc. on them.
4. Avoid `int`s in your code. There's no reason to use `int`s when `long long int` are available, which do the same task and also avoid the occassional overflow problem that you might forget to take care of.
5. Use as many keybindings, snippets, etc. as you can during the contest. Make your text editor your own.

## IO

1. When using `scanf`, always use `%llu` or `%lld` to take integer inputs. On codeforces custom invocation you can check that using `%lf` or `%f` to take integer inputs assigns it a value 0.000000.
2. Prefer `cin`/`cout` as far as possible over `scanf`/`printf`. With sync with stdio disabled, they're as fast as or even faster than the c analogs. Also, taking string input with cin is super easy. You might only need printf when formatting your long double answer to six decimal places, which is a bit messed up in cout.
3. Do not mix `cin`/`cout` with `scanf`/`printf`/`getchar` when sync with stdio is disabled.

## Using vectors

1. Make sure your index variable - with which you are looping over a vector - is bounded till the size of the vector. C++ fails without any warning in case of that, gives undefined behavior.

## General algo

1. **Stackoverflow**: The recursion stack is limited to around 350,000 on an average machine. This solution won't TLE, but will give a memory limit exceeded error. You'll get an error similar to `SIGSEGV: Invalid memory reference`, and in gdb, you will get the line number as the start of the method header. In general, avoid using recursion for such large cases, use iteration instead.

## Sieve

1. Do not create a sieve unless you want to check the primality of a number more than once. Besides that, decide at all if you actually require the number to be prime in your code.
   Refer to [bad solution](https://codeforces.com/contest/1076/submission/45601999), [best solution](https://codeforces.com/contest/1076/submission/45626302)

# TODO:

1. automated web scraper for downloading the test cases and diffing them with expected output on F8 press. Progress: found `hightail`, but it's not recognizing the jar file on ubuntu for now.
2. Create snippet for cumulative sum of 2d array,
