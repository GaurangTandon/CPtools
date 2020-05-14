# One key code execution

This guide will help you setup one key code execution in your favorite editor. This is useful, for example, when you want to rerun your code several times on the same input file with minor changes while testing. Ideally, we prefer to have focus on:

1. usability: not required to leave the editor to see compilation logs/run output.
2. speed: use `makefile` where possible so as to not recompile without changes

## Sublime Text

TODO

## CLion

This is present by default. You can see the buttons on the top right and hover over them to get the keyboard shoftcut. (Alternatively, press Alt-Shift-A and type Debug or Run and you'll see the shortcut to the right side)

## VS Code

Install the Code Runner extension. Add this code to your `~./bashrc`:

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


## Vim/Neovim

Copy the following to the file `~/.vim/ftplugin/cpp.vim`:

```
nnoremap <F4> :w<CR>:vs \| te g++ % && ./a.out < in<CR>i
inoremap <F4> <esc>:w<CR>:vs \| te g++ % && ./a.out < in<CR>i
```

This will allow you to press F4 key to compile the currently open C++ file, and run it on an input file named `in`. Here's a short explanation of how this works:

1. The file only applies to c++ files (`ftplugin` => file type plugin)
2. The two remaps apply to normal mode and insert mode respectively.
3. The commmand on the right:

    1. Saves the file
    2. Launches a terminal in vertical split
    3. Runs the compilation and execution command in the newly launched terminal

## Atom

TODO
