# Tips for CP

Tips are separated by categories

## Interactive problems

### **Checking interactive problems**

There is already a [script](https://storage.googleapis.com/coding-competitions.appspot.com/interactive_runner.py) provided (by [Google here](https://codingcompetitions.withgoogle.com/codejam/faq?#interactive-problems)). Usage instructions are inside the script. Of course, though, you would have to write the judge script too when using this, not just the solution.

To be fair, in general it is far easier for you to "be the judge yourself" and simulate the judging process, rather than writing out the judge from scratch. Most of the time you can find the mistake in your code that way.

### Flushing methods

1. `cout.flush()` in C++
2. `fflush(stdout)` in C.

## Compilation tricks

### Fixing undefined behavior

Using this compilation command (note the flags): `g++ -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG file.cpp`, you can catch out-of-bounds index accesses at runtime. So, you will get an error for them and they will not pass undetected.

For example, try catching the error in [this code](https://codeforces.com/blog/entry/75082?#comment-591976) with and without the above compilation flags, and you'll see the difference yourself :)

### Precompiled header 

To enable 2x faster compilation, setup a precompiled header in your `bits` directory. In Ubuntu, it is usually located at `/usr/include/x86_64-linux-gnu/c++/7/bits`. `cd` into it and simply compile the stdc++.h file (`g++ stdc++.h`). You should now have a `stdc++.h.gch` file. Enjoy! ([more info](https://gcc.gnu.org/onlinedocs/gcc/Precompiled-Headers.html))

### Do not use O2 flag

Don't use the `-O2` flag for compilation by default. It takes more time to compile and it enables several optimizations, but it demolishes the `print <local_variable>` output that is otherwise available in GDB. Interestingly, codeforces.com [already compiles](https://codeforces.com/blog/entry/79) the files with `-O2` flag.

To enable O2 anyway, since you don't get the command line for yourself, you can use pragma directives. The lines to stick at the top are:

    #pragma comment(linker, "/stack:200000000")
    #pragma GCC optimize ("Ofast")
    #pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

Read more compilation options on [this page](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#index-Ofast). How do the first and last line actually work?

## Fixing Time Limit Exceeded

### Using int throughout

In several questions where time limit is tight and you need to perform several modulo operations, using `long long` datatype can increase your time and memory taken by factor of 2. Most questions can be solved with int type in general. Here is [one code](https://www.codechef.com/viewsolution/31263439) for example, that efficiently mixes `int` and `long long` datatype.

### Digit segment tree

Converting a digit segment tree into actual parts (`int tree[len][dig_count]`) reduces time taken significantly.  

### Query function of segment tree

Avoid returning more than a pair in query function of segment tree. Even sorting a vector of length 4 can result in tle! ([tl code](https://codeforces.com/contest/1217/submission/74391601), [ac](https://codeforces.com/contest/1217/submission/74392081))

### `cerr`

Even a very innocent looking `cerr` can cause your code to TLE. Here is [AC](https://codeforces.com/contest/343/submission/85612330) and [TLE](https://codeforces.com/contest/343/submission/85612428) code. The only difference in TLE code is that I'm printing two integers to `cerr`. So, always remove all your `cerr` statements.

### Other miscellaneous problems

1. Sorting a very large vector of pairs using a custom comparator function can cause TLE. [Example link](https://codeforces.com/contest/605/submission/54273199)
2. Using `long long` instead of `int` can cause TLE. ![Example](https://i.imgur.com/im2FJPK.png)
3. Using a set of strings (`set<string>`) can give TLE in a lot of cases. Perform lots of optimizations in the code if you plan to use such a set. For example, an n^2 loop should be done in $n^2/2$ instead. Try to reduce number of other things being used, basically, think for two minutes and make it as optimized as possible. There is a very high possibility you will get TLE if you do not do this ([TLE](https://codeforces.com/contest/1287/submission/68256873) and [AC](https://codeforces.com/contest/1287/submission/68280463)). 
   1. Another example for $n^2$ TLE is [270807A](https://codeforces.com/gym/270807/submission/72146495).
4. Using binary search with sets results in a $\log^2n$ factor and can lead to TLE. [Example submission](https://codeforces.com/contest/514/submission/79273659). Use **two pointer** approach to AC such questions wherever possible ([submission](https://codeforces.com/contest/514/submission/79274584))

## General coding

### Use of auto-keyword

Instead of `set<pair<int, pair<int, int>>>::iterator` you can simply do `auto it = s.begin()`, similarly, instead of `vector<int> row = grid[index]` you can simply do `auto row = grid[index]`

### Local setup code

To exclude some code from executing in online judge (C++), you can use this:

    #ifndef ONLINE_JUDGE
    //code that should not execute in ONLINE JUDGE
    #else
    //code that should execute in ONLINE JUDGE
    #endif

### Uninitialized values inside struct array

Note that values of arrays inside struct are not automatically initialized. So, `(struct)->array[i]` is null. Hence, need to manually iniitialize each index of an array property. Else you get run error, [like here](https://codeforces.com/contest/514/submission/52626249).

### Nonsensical output/Unexpected runtime error

If you get a run error in a line where you shouldn't, especially `free()` related errors, or you are seeing some nonsensical outputs, that means you have **undefined behavior** somewhere above in your file.

Compile with fsanitize debugging flags to find the problem. See the section on compilation.

10. **Instead of a binary search tree, if all insertions before all the queries, then please use 1d vector with binary search.**
11. If stuck and have a brute force, perform complexity analysis and it might even pass. (255C as well as 1229C)
12. If you have range queries and point updates, but the updates are offline (all queries occur after all updates), then consider using the "library question" approach (checkposts waala).

## Causes for RE

1. Accessing an element out of range or an invalidated iterator.
2. Popping/accessing elements from empty container.
3. Miswritten sorting function (should return true iff a < b)
4. `lower_bound` called on a container which was sorted with a different criterion. For example, container is sorted by `PII.second` but your `lower_bound` comparator searches by `PII.first`.

## Causes for MLE

1. A 10^7 vector of long long ints takes roughly 400MB. So, consider using int instead, which takes 200MB.
2. Inserting strings into set may give memory limit even if you use `int` and $n^2$ complexity is permitted. ([link](https://codeforces.com/contest/271/submission/62205689))

## IO

1. When using `scanf`, always use `%llu` or `%lld` to take integer inputs. On codeforces custom invocation you can check that using `%lf` or `%f` to take integer inputs assigns it a value 0.000000.
2. Prefer `cin`/`cout` as far as possible over `scanf`/`printf`. With sync with stdio disabled, they're as fast as or even faster than the C analogs. Also, taking string input with cin is super easy.
3. Do not mix `cin`/`cout` with `scanf`/`printf`/`getchar` when sync with stdio is disabled. The latter literally means `cin`/`cout` (which are part of `iostream`) will NOT be in sync with the others (which are in `cstdio`). 

    For example, the following code may result in unexpected behavior:

    ```cpp
    scanf("%d", &a);
    cin >> b;
    cout << b;
    printf("%d", a);
    ```

## Using vectors

1.  Always pass large vectors, with roughly $10^6$ elements, to methods in reference form (using the ampersand argument format).
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

## `memset`s

`memset` is a string function, so it fills values **byte-by-byte**. It won't work for integer arrays! (unless you set to 0) So, a simple code like following:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    const int sz = 1;
    int nums[sz];
    memset(nums, 1, sizeof(nums));
    cout << nums[sz - 1] << endl;
    return 0;
}
```

produces `16843009`, which is `0x01010101`, basically, the single byte value `0x01` copied four times over. Note that this is the same in both `memset` from C and from C++, they both are string functions only.

**Fix:** use `std::fill(dest, dest + n, val)`.

## Multisets

1. `multiset.erase(value)` erases all copies of `value` in `multiset`. To delete just one value use `multiset.erase(multiset.find(value))` (but first ensure the value exists in multiset).

## Integers

1. Maximizing greedy consumptions occurs best in greedy space, consider modular groups always. (see 1244C - number theory solution)
2. Never print `!integer` directly in codeforces, instead of printing 0 or 1, have faced [WA](https://codeforces.com/contest/1010/submission/73504640), instead first assign to boolean and then apply ternary like this [AC](https://codeforces.com/contest/1010/submission/73501156)

## Floats

1. Use epsilon when comparing floating point values, even when with ints. Do not use anything less than 1e-6 unless absolutely sure. See the problem https://codeforces.com/group/K3Zd1r0QSA/contest/102343/submission/61050721 and previous two submissions.
2. Be careful in Python when using division and modulo together. Division `/` produces float values and modulo on float values gives very incorrect results. Always use `//` if using modulo (and cast 1e10 using `int`.)

## Strings

1. Always check size of string before applying integer parsing functions. For example, don't pass strings of length greater than 18 to `stoull`.
2. Use `<` or `>` when attempting lexicographical comparison. It is much better than writing a normal for loop for the same. For example, `"abc" > "def"` is `false`.
3. If $n^2$ complexity is permitted, consider using tries instead of hashing. [Hashing can give wrong answer.](https://codeforces.com/contest/271/my)

## Math

1. `std::pow` is a constant time operation. See [SO](https://stackoverflow.com/q/13418180) and [code submission](https://codeforces.com/contest/453/submission/55961090) that passes on Codeforces.
2. For taking modulo, the following works for both negative or positive integers: `((value % MOD) + MOD) % MOD`. Simply using `value % MOD` produces negative remainder for negative integers and may not be desired.
4. If mod value `= 1ll << 30`, (or any power of 2), then taking mod is not necessary as it will overflow on its own and adjust accordingly. (use unsigned int if necessary). In fact, doing `(1ll * a * b) % mod` will slow your code down.
5. Never print `pow(a,b)` directly. Always convert to integer first. This is because `pow` returns double type which prints in a different format (`1e+6.0`) compared to integers (`1000000`).
6. Do not use `log10(num) / log10(base) + 1` to find number of digits in number in base b. It can give a wrong answer, use the trivial while loop instead. Example [WA](https://codeforces.com/contest/49/submission/80280102), [AC](https://codeforces.com/contest/49/submission/80280370)

### Square roots of very large numbers

When taking sqrt of very large numbers (order $10^16$), you can get erroneous with `sqrt` or `log10` style functions. 
Always verify that if `(int) x = sqrt(N)`, then `x * x <= N`, because, of these things: `sqrt((ll) (1e16-1)) = 1e8` (can check it's true)
In similar vein, `x = log10(999999999999996448.0l)` means `x = 18`, so you can double check with `pow(10, x)` to be sure the output was incorrect.

## General algo

1. **Stackoverflow**: The recursion stack is limited to around 350,000 on an average machine. This solution won't TLE, but will give a memory limit exceeded error. You'll get an error similar to `SIGSEGV: Invalid memory reference`, and in gdb, you will get the line number as the start of the method header. In general, avoid using recursion for such large cases, use iteration instead.
2. When value of `n` is very large, try to come up with some patterns for lower values of `n` using brute force or dp. Like [this question](https://codeforces.com/gym/101612) can be solved in constant time, however, the formula is not immediately obvious. Use DP to observe a pattern. See my A.cpp submission.

## Bit manipulation

1. `1 << x` can overflow if `x` is greater than 31. Use `1ll << 31` instead.

## Sieve

1. Do not create a sieve unless you want to check the primality of a number more than once. Besides that, decide at all if you actually require the number to be prime in your code.  Refer to [bad solution](https://codeforces.com/contest/1076/submission/45601999), [best solution](https://codeforces.com/contest/1076/submission/45626302) In most cases you can get away with a simple square root based for loop, like so:

    ```cpp
    for(int i = 2; 1ll * i * i <= x;){
            if(x % i == 0){
                x /= i;
            } else i++;
        }
    }
    ```
    since at each step the value of $x$ reduces, in the worst case the complexity is $\sqrt{x}$ when $x$ is prime.

## Flows

1. Practically, all flow algos (dinics, push relabel, or even edmonds-karp) have complexity `= min( (V + E) * mf, ...)` (mf = max flow).
2. In practice, even if N=800 and M=1e4, Dinics or even EK might work, so do not hesitate in coding them up. (The problem might have weak testcases, or see the previous point, it is possible that their max flow bound is lower)
3. CLRS question 26.2-13 is nice. "Given graph G, propose modification so that among all current mincuts, in the new graph G', any mincut will also have least number of edges". [Solution](https://www.slader.com/discussion/question/suppose-that-you-wish-to-find-among-all-minimum-cuts-in-a-flow-network-g-with/). Short answer: scale all capacities by 2|E| and add one.

## Graphs

1. Kosaraju's algo works better with stacks than with toposort. See [failed toposort](https://codeforces.com/contest/427/submission/55713667) and [accepted stacks](https://codeforces.com/contest/427/submission/55713974) solution.
2. When there are only two paths in a grid possible (up and right OR down and right) and so on, consider using a nested for loop instead of bfs type queue to iterate over all elements in order. See, [example submission](https://codeforces.com/contest/1353/submission/80164554)

## Gaussian elimination

It has two techniques: full pivoting and partial pivoting. It is known that full pivoting is slower, although guarantees stability in output (see [discussion here](https://codeforces.com/blog/entry/65787)). Stability means that the error term in the output will not grow too large as compared to correct output. There exists certain matrices - with negative terms in their lower triangle - that fail stability when computed with partial pivoting.

[Blog](https://codeforces.com/blog/entry/60003) on using gaussian to solve for probabilities and xor values.

## Randomization tasks

Use this line: `mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());`. Have previously got WA when using `rand()` or `(1ll * rand() * rand() % n + n) % n + 1` ([WA](https://codeforces.com/contest/843/submission/81008035), [AC](https://codeforces.com/contest/843/submission/81008530))
 

## Specific kinds of problems

### Problems where the complement graph is inputted

1242B, 190E

Approaches:

1. DFS using a set that keeps self-deleting: this TLEd on 190E so go with DSU approach
2. DSU (I didn't understand this approach :/ explained in editorial of 1242B)

### Problems with `map` giving TLE

Using `unordered_map` instead will usually **NOT** fix your problem. Instead, focus on reworking your logic a bit so that you can get an AC. See problem 102411M (AC https://codeforces.com/gym/102411/submission/66275452).
Also, see https://codeforces.com/blog/entry/60737 but you probably won't ever need it.

### SPOJ TIPS

1. If problem says "Round answer to 6 decimal digits", it actually wants you to print exactly six decimal digits and not more! So, for your final answer, do `ans = std::round(1e6 * ans) / 1e6` and use `setprecision(6)`.
2. SPOJ always runs on all tests first and only then gives the verdict. So, it may be possible that you see "running (12)" even though your code failed on first test itself.
3. Python 2 is on SPOJ, and it uses `raw_input` instead of `input`.
