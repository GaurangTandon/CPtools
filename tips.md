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

To enable 2x faster compilation, setup a precompiled header in your `bits` directory. In my case, it is located at `/usr/include/x86_64-linux-gnu/c++/7/bits`. `cd` into it and simply compile the stdc++.h file (`g++ stdc++.h`). You should now have a `stdc++.h.gch` file. Enjoy! ([more info](https://gcc.gnu.org/onlinedocs/gcc/Precompiled-Headers.html))

Don't use the `-O2` flag for compilation by default. It takes more time to compile and it enables several optimizations, but it demolishes the `print <local_variable>` output that is otherwise available in GDB. Interestingly, codeforces.com [already compiles](https://codeforces.com/blog/entry/79) the files with `-O2` flag.

To enable O2 anyway, since you don't get the command line for yourself, you can use pragma directives. The lines to stick at the top are:

    #pragma comment(linker, "/stack:200000000")
    #pragma GCC optimize ("Ofast")
    #pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

Read more compilation options on [this page](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#index-Ofast). How do the first and last line actually work?

## Time limit exceeded TLE

1. Converting the object syntax (like the one in prime sieve `Multiplicative`) into simple array based globals can actually help increase speed by over 0.2s, useful in problems like this one https://www.codechef.com/problems/LCM where TL is too tight
2. It is helpful to convert a digit segment tree into actual parts (`vv tree[len][dig_count]`) and can help improve time. Also, avoid returning more than a pair in query function of segment tree. Even sorting a vector of length 4 can result in tle! (tl: https://codeforces.com/contest/1217/submission/74391601, ac: https://codeforces.com/contest/1217/submission/74392081)

## General coding

1.  Decide upon some standard variable names. Like, `a` for arrays, prefix sum array as `sum`, `s` for strings, etc. Avoid longer names. At max, competitive code has only six distinct variables in any scope, so there can't/shouldn't be much confusion.
2.  Use vectors if you're using C++. There's no reason to not use vectors when they are available. They are not only [as fast as plain arrays](https://stackoverflow.com/questions/26189531/how-is-stdvector-faster-than-a-plain-array), but are also dynamically sized with constant access time. They also allow sorting operations, any index insertion/deletion, etc. on them.
3.  It is recommended to avoid writing functions that return more than one value, as it leads to harder debugging. However, this may sometimes be desirable, for example to return index of first occurrence of string that begins with "a", and the string itself. So, you can use `std::tie` and `std::tuple` for that.

        tuple<int, string> f(params) {
            // do some searching
            return {index, str};
        }

        int main(void) {
            int idx; string found;
            tie(idx, found) = f(params);
        }

4.  **Use of auto-keyword:** Instead of `set<pair<int, pair<int, int>>>::iterator` you can simply do `auto it = s.begin()`
5.  To exclude some code from executing in online judge (C++), you can use this:

        #ifndef ONLINE_JUDGE
        //code that should not execute in ONLINE JUDGE
        #else
        //code that should execute in ONLINE JUDGE
        #endif

8.  When using a function `newnode` to initialize a new struct pointer, note that values of arrays inside struct are not automatically initialized. So, `node->array[i]` is null. Hence, need to manually iniitialize each index of an array property. Else you get run error, [like here](https://codeforces.com/contest/514/submission/52626249).
9.  If you get a run error in a line where you shouldn't, especially `free()` related errors, that means you have undefined behavior somewhere above in your file. Compile with fsanitize debugging flags to find the problem.
10. **Instead of a binary search tree, if all insertions before all the queries, then please use 1d vector with binary search.**
11. If stuck and have a brute force, perform complexity analysis and it might even pass. (255C as well as 1229C)
12. If you have range queries and point updates, but the updates are offline (all queries occur after all updates), then consider using the "library question" approach (checkposts waala).

## Causes for TLE

1. Sorting a very large vector of pairs using a custom comparator function (`[](){}`) can cause TLE. [Example link](https://codeforces.com/contest/605/submission/54273199)
2. Using `long long` instead of `int` can cause TLE. ![Example](https://i.imgur.com/im2FJPK.png)
3. Using `pow(a, b)` is much much slower than using `1ll << power`, which is slightly slower than storing successive powers in a cumulative array, when used in a loop. (see submissions on D - https://codeforces.com/contest/1220/my)
4. Using a set of strings (`set<string>`) can give TLE in a lot of cases. Perform lots of optimizations in the code if you plan to use such a set. For example, an n^2 loop should be done in $n^2/2$ instead. Try to reduce number of other things being used, basically, think for two minutes and make it as optimized as possible. There is a very high possibility you will get TLE if you do not do this ([TLE](https://codeforces.com/contest/1287/submission/68256873) and [AC](https://codeforces.com/contest/1287/submission/68280463)). 
   1. Another example for $n^2$ TLE is [270807A](https://codeforces.com/gym/270807/submission/72146495).

## Causes for MLE

1. A 10^7 vector of long long ints takes roughly 400MB. So, consider using int instead, which takes 200MB.

## IO

1. When using `scanf`, always use `%llu` or `%lld` to take integer inputs. On codeforces custom invocation you can check that using `%lf` or `%f` to take integer inputs assigns it a value 0.000000.
2. Prefer `cin`/`cout` as far as possible over `scanf`/`printf`. With sync with stdio disabled, they're as fast as or even faster than the c analogs. Also, taking string input with cin is super easy.
3. Do not mix `cin`/`cout` with `scanf`/`printf`/`getchar` when sync with stdio is disabled.

## Using vectors

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

## Integers

1. Maximizing greedy consumptions occurs best in greedy space, consider modular groups always. (see 1244C - number theory solution)
2. Never print `!integer` directly in codeforces, instead of printing 0 or 1, have faced wrong answer (https://codeforces.com/contest/1010/submission/73504640), instead first assign to boolean and then apply ternary like this (https://codeforces.com/contest/1010/submission/73501156)

## Floats

1. Use epsilon when comparing floating point values, even when with ints. Do not use anything less than 1e-6 unless absolutely sure. See the problem https://codeforces.com/group/K3Zd1r0QSA/contest/102343/submission/61050721 and previous two submissions.
2. Be careful in python when using division and modulo together. Division `/` produces float values and modulo on float values gives very incorrect results. Always use `//` if using modulo (and cast 1e10 using `int`.)

## Strings

1. Always check size of string before applying integer parsing functions. For example, don't pass strings of length greater than 18 to `stoull`.
2. Use `<` or `>` when attempting lexicographical comparison. It is much better than writing a normal for loop for the same.
3. If $n^2$ complexity is permitted, consider using tries instead of hashing. [Hashing can give wrong answer.](https://codeforces.com/contest/271/my)
4. Inserting strings into set will give memory limit even if you use `int` and $n^2$ complexity is permitted. ([link](https://codeforces.com/contest/271/submission/62205689))

## Math

1. `std::pow` is a constant time operation. See [SO](https://stackoverflow.com/q/13418180) and [code submission](https://codeforces.com/contest/453/submission/55961090) that passes on Codeforces.
2. Do not use `multmod` as far as possible because it can lead to time limit.
3. For taking modulo, the following always works: `((value % MOD) + MOD) % MOD`
4. If mod value `= 1ll << 30`, (or any power of 2), then taking mod is not necessary as it will overflow on its own and adjust accordingly. (use unsigned int if necessary). In fact, doing `(1ll * a * b) % mod` will slow your code down.
5. When taking sqrt of very large numbers (10\*\*18), always verify that if `(int) x = sqrt(N)`, then `x * x <= N`, because, of these things: `sqrt((ll) (1e16-1)) = 1e8` (can check it's true)

## General algo

1. **Stackoverflow**: The recursion stack is limited to around 350,000 on an average machine. This solution won't TLE, but will give a memory limit exceeded error. You'll get an error similar to `SIGSEGV: Invalid memory reference`, and in gdb, you will get the line number as the start of the method header. In general, avoid using recursion for such large cases, use iteration instead.
2. When value of `n` is very large, try to come up with some patterns for lower values of `n` using brute force or dp. Like [this question](https://codeforces.com/gym/101612) can be solved in constant time, however, the formula is not immediately obvious. Use DP to observe a pattern. See my A.cpp submission.

## Bit manipulation

1. `1 << x` can overflow if `x` is greater than 31. Use `1ll << 31` instead.

## Sieve

1. Do not create a sieve unless you want to check the primality of a number more than once. Besides that, decide at all if you actually require the number to be prime in your code.
   Refer to [bad solution](https://codeforces.com/contest/1076/submission/45601999), [best solution](https://codeforces.com/contest/1076/submission/45626302)

## Codechef

1. When you receive an invalid answer output from an interactive problem, you should immediately terminate your program to receive a Wrong Answer verdict; otherwise, you may receive any verdict.
2. Don't forget to flush the output after printing each line! (`cout.flush();`)

## Graphs

1. Kosaraju's algo works better with stacks than with toposort. See [failed toposort](https://codeforces.com/contest/427/submission/55713667) and [accepted stacks](https://codeforces.com/contest/427/submission/55713974) solution.
2. `dfs` in a 2d grid: do not use pairs to keep track of coords and a `map<pll, bool> visited`.  Instead use `vector<vb> visited(1000, vb(1000,false))` and `x,y` separated arguments to do `dfs`. This can be the difference of a time limit and AC. Apparently, using pairs to do dfs with maps for visited array can TLE on 10^6 nodes. (see problem C https://codeforces.com/contest/374/my)
3. When there are only two paths in a grid possible (up and right OR down and right) and so on, consider using a nested for loop instead of bfs type queue to iterate over all elements in order.

# Specific kinds of problems

## Problems where the complement graph is inputted

1242B, 190E

Approaches:

1. DFS using a set that keeps self-deleting: this TLEd on 190E so go with DSU approach
2. DSU (I didn't understand this approach :/ explained in editorial of 1242B)

## Problems with `map` giving TLE

Using `unordered_map` instead will usually **NOT** fix your problem. Instead, focus on reworking your logic a bit so that you can get an AC. See problem 102411M (AC https://codeforces.com/gym/102411/submission/66275452).
Also, see https://codeforces.com/blog/entry/60737 but you probably won't ever need it.

## SPOJ TIPS

1. If problem says "Round answer to 6 decimal digits", it actually wants you to print exactly six decimal digits and not more! So, for your final answer, do `ans = std::round(1e6 * ans) / 1e6` and use `setprecision(6)`.
2. SPOJ always runs on all tests first and only then gives the verdict. So, it may be possible that you see "running (12)" even though your code failed on first test itself.
3. Python 2 is on SPOJ, and it uses `raw_input` instead of `input`.

## WTF

1. How to check for overflow in long long consecutive products? Why did this happen? https://codeforces.com/group/K3Zd1r0QSA/contest/101612/submission/60599572 -_-
                                
                ```
                bool of = false;
                ll x = 1;

                for (auto mult : prods) {
                    if (x > (ld)1e18 / mult) {
                        of = true;
                        break;
                    }
                    x *= mult;
                }
                ```

2. `log10(999999999999996448.0l)` is `18` :(
3. Never output `pow(a,b)` directly. Always convert to `ll` before doing `cout`.
