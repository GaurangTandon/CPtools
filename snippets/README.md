# Snippets

## Environment and usage

These are the environments on which this was tested:

-   VS Code 1.28.2 or above
-   paste json files in /home/username/.config/Code/User/snippets/cpp.json; it would be better to create a hardlink just in case the git repo code changes. To do that, goto `/home/username/.config/Code/User/snippets`, open terminal and type `ln actualPathToThisRepoJSON cpp.json`. You can do this using wildcard `*` for all files.
