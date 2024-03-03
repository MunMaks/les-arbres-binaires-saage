# Trees Algorithm Homework

The program "./algo" is a program that allows you to work with trees and their grafts. It offers various functionalities to manipulate these data structures, including the addition and removal of grafts, reading and writing files, and displaying trees and grafts as graphs using .dot.

## Compilation

To compile the program, run the following command:

`make`


## Usage

The program can be used with different options to perform specific operations on trees and grafts. Here are the available options:

- `-G` : Displays the graft of the tree path_tree in the tree path_graft.
- `-E` : The user's standard input (from the keyboard or a non-saage file) is added to path_file.
- `-DOT` : Takes a valid path and displays the tree using the DOT function.
- `-BIG` : Takes a valid path (grand.saage or immense.saage) and returns the graft of a tree and displays it with DOT.

### Usage Examples:

```
./algo -G A_1.saage X.saage
./algo -E new_file.saage < user_input.txt
./algo -DOT file.saage
./algo -BIG grand.saage
```


## Requirements

- Linux Environment
- Valgrind installed



## Authors

- Navarro Antony
- MUNAITPASOV Maksat

