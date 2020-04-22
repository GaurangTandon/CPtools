# Setting up single key press code execution in VS Code

## Prequisites:

-   VS Code 1.28 or above
-   Code Runner extension installed
-   GCC/G++ installed (preferably Linux distros)

## Setting it all up:

Add the code to your `~./bashrc`:

```
runC(){
    gcc -g -Wall -o $1 $2 -lm && ./$1 < $3
}
run(){
    g++ -o $1 $2 && ./$1 < $3
}
```

and that to your `"code-runner.executorMap"` setting like so:

```
"cpp": "run $fileNameWithoutExt $fileName inp.txt",
```

You might also want to change the default keybinding from Ctrl+Alt+N to just F8, via Ctrl-K Ctrl-S > Run Code setting.
