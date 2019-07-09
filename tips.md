# Tips for CP

Tips are separated by categories

## Contest

1. First read C problem and attempt to solve it, as it gives more poins, since fewer people had solved it. Case in point: [Contest 520](https://codeforces.com/contest/1062) had problem C only slightly tougher than problem A, and problem D was way easier than both B and C.

2. Be good at coming up with self test cases. Just because your code passes the pretests doesn't mean it will pass the system tests.

3. **Hightail**: is a program that scrapes and downloads sample test cases from a problem/contest, and then can run your executable against that problem. Use it to quickly determine if your program passes the given inputs.

4. **Checking interactive problems**: is tricky. For C++, you can however achieve that as follows.

    1. You first need to write both a `solution.cpp` and then a `grader.cpp` that verifies if the solution is correct.
    2. Then, execute the compiled executables like so:

        mkfifo myfifo
        ./grader < myfifo | ./solution > myfifo

        `mkfifo` creates a named fifo (`myfifo` in this case) which we can use for queuing the output of `solution` into the `grader`. One small problem is that you cannot view the contents of `myfifo` unless you close the output connection, which I do not know how to.
        So, you can simply write the output to a separate file via an `ofstream` (use `sol.txt` for one and `grad.txt` for another)

## Hacking

1. Only get down to hack problems once you have actually read all problems in the contest and made sure that you cannot solve them. In general, for div 2 problems, all problems without trees can be solved pretty easily.
   Case in point: [Contest 520](https://codeforces.com/contest/1062) had first four very easy problems, as opposed to generally two in usual div2 contests.
2. Attempt to hack those solutions which took less than five minutes to accepted. In general, they have a silly logic mistake that enables them to submit faster but incorrectly.
   Example: [this hacked solution](https://codeforces.com/contest/1062/hacks/502444/) was submitted in two minutes.

## Compilation

Don't use the `-O2` flag for compilation by default. It takes more time to compile and it enables several optimizations, but it demolishes the `print <local_variable>` output that is otherwise available in GDB. Interestingly, codeforces.com [already compiles](https://codeforces.com/blog/entry/79) the files with `-O2` flag.

To enable O2 anyway, since you don't get the command line for yourself, you can use pragma directives. The lines to stick at the top are:

    #pragma comment(linker, "/stack:200000000")
    #pragma GCC optimize ("Ofast")
    #pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

Read more compilation options on [this page](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#index-Ofast). How do the first and last line actually work?

## General coding

1.  Decide upon some standard variable names. Like, `a` for arrays, prefix sum array as `sum`, `s` for strings, etc. Avoid longer names. At max, competitive code has only six distinct variables in any scope, so there can't/shouldn't be much confusion.
2.  Use vectors if you're using C++. There's no reason to not use vectors when they are available. They are not only [as fast as plain arrays](https://stackoverflow.com/questions/26189531/how-is-stdvector-faster-than-a-plain-array), but are also dynamically sized with constant access time. They also allow sorting operations, any index insertion/deletion, etc. on them.
3.  Avoid `int`s in your code. There's no reason to use `int`s when `long long int` are available, which do the same task and also avoid the occassional overflow problem that you might forget to take care of.
4.  Use as many keybindings, snippets, etc. as you can during the contest. Make your text editor your own.
5.  It is recommended to avoid writing functions that return more than one value, as it leads to harder debugging. However, this may sometimes be desirable, for example to return index of first occurrence of string that begins with "a", and the string itself. So, you can use `std::tie` and `std::tuple` for that.

        tuple<int, string> f(params) {
            // do some searching
            return {index, str};
        }

        int main(void) {
            int idx; string found;
            tie(idx, found) = f(params);
        }

6.  **Use of auto-keyword:** Instead of `set<pair<int, pair<int, int>>>::iterator` you can simply do `auto it = s.begin()`
7.  To exclude some code from executing in online judge (C++), you can use this:

        #ifndef ONLINE_JUDGE
        //code that should not execute in ONLINE JUDGE
        #else
        //code that should execute in ONLINE JUDGE
        #endif

8.  When using a function `newnode` to initialize a new struct pointer, note that values of arrays inside struct are not automatically initialized. So, `node->array[i]` is null. Hence, need to manually iniitialize each index of an array property. Else you get run error, [like here](https://codeforces.com/contest/514/submission/52626249).
9.  If you get a run error in a line where you shouldn't, especially `free()` related errors, that means you have undefined behavior somewhere above in your file. Comment out parts of your file and run the debugger to understand where it is.

## Causes for TLE

1. Sorting a very large vector of pairs using a custom comparator function (`[](){}`) can cause TLE. [Example link](https://codeforces.com/contest/605/submission/54273199)
2. Using `long long` instead of `int` can cause TLE. ![Example](https://i.imgur.com/im2FJPK.png)

## Causes for MLE

1. A 10^7 vector of long long ints takes roughly 400MB. So, consider using int instead, which takes 200MB.

## IO

1. When using `scanf`, always use `%llu` or `%lld` to take integer inputs. On codeforces custom invocation you can check that using `%lf` or `%f` to take integer inputs assigns it a value 0.000000.
2. Prefer `cin`/`cout` as far as possible over `scanf`/`printf`. With sync with stdio disabled, they're as fast as or even faster than the c analogs. Also, taking string input with cin is super easy. You might only need printf when formatting your long double answer to six decimal places, which is a bit messed up in cout.
3. Do not mix `cin`/`cout` with `scanf`/`printf`/`getchar` when sync with stdio is disabled.

## Using vectors

1.  Make sure your index variable - with which you are looping over a vector - is bounded till the size of the vector. C++ fails without any warning in case of that, gives undefined behavior.
2.  Use `emplace_back` instead of `push_back` for [marked performance improvement](https://stackoverflow.com/questions/26860749/efficiency-of-c11-push-back-with-stdmove-versus-emplace-back-for-already). The bug (mainly typesafety) involved with emplace_back is not our concern in CP ([post](https://stackoverflow.com/questions/10890653/why-would-i-ever-use-push-back-instead-of-emplace-back/28435599)).
3.  Always pass large vectors, especially large 2D vectors (think `1000x1000`), to methods using the ampersand argument format. Also, if the total number of elements exceeds `10^6`, declare them globally and convert from `lu` to possibly `int` or `long int`. Otherwise you will get MLE.
4.  Always initialize very large vectors outside of your main loop. For example, the time complexity of the following program is `O(n * k)`, which will TLE if n and k are both very large:

        for(int i = 0; i < n; i++){
            vu freq(k + 1, 0);
        }

    Instead of this, consider doing this:

        vu freq(k + 1, 0);
        for(int i = 0; i < n; i++){
            // keep track of which values are
            // changed from 0
            set<lu> usedValues;

            // every time we use a value
            // we insert it
            usedValues.insert(<any used value>);

            // reset used values
            for(auto x : usedValues)
                freq[x] = 0;
        }

    The same problem plagues array initialization (`int arr[k] = {0};`) and cannot be avoided by doing `memset(arr, k, 0);` as the latter also takes `O(k)`.

## Multisets

1. `multiset.erase(value)` erases all copies of `value` in `multiset`. To delete just one value use `multiset.erase(multiset.find(value))` (but first ensure the value exists in multiset).

## Floats

1. Use epsilon when comparing floating point values, even when with ints. For example, 1e-10

## Strings

1. Always check size of string before applying integer parsing functions. For example, don't pass strings of length greater than 18 to `stoull`.

## Math

1. `std::pow` is a constant time operation. See [SO](https://stackoverflow.com/q/13418180) and [code submission](https://codeforces.com/contest/453/submission/55961090) that passes on Codeforces.

## General algo

1. **Stackoverflow**: The recursion stack is limited to around 350,000 on an average machine. This solution won't TLE, but will give a memory limit exceeded error. You'll get an error similar to `SIGSEGV: Invalid memory reference`, and in gdb, you will get the line number as the start of the method header. In general, avoid using recursion for such large cases, use iteration instead.

## Bit manipulation

1. `1 << x` can overflow if `x` is greater than 31. Use `1ll << 31` instead.

## Sieve

1. Do not create a sieve unless you want to check the primality of a number more than once. Besides that, decide at all if you actually require the number to be prime in your code.
   Refer to [bad solution](https://codeforces.com/contest/1076/submission/45601999), [best solution](https://codeforces.com/contest/1076/submission/45626302)

## Codechef

1. When you receive an invalid answer output from an interactive problem, you should immediately terminate your program to receive a Wrong Answer verdict; otherwise, you may receive any verdict.
2. Don't forget to flush the output after printing each line!

## Graphs

1. Kosaraju's algo works better with stacks than with toposort. See [failed toposort](https://codeforces.com/contest/427/submission/55713667) and [accepted stacks](https://codeforces.com/contest/427/submission/55713974) solution.

# TODO:

1. Create snippet for cumulative sum of 2d array,
