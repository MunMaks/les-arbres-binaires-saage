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
i = {1, 2, 3}, X = {B, C, D}
./algo -G A_i.saage X.saage
./algo -E new_file.saage < user_input.txt
./algo -E new_file.saage (input in format *)
./algo -DOT file.saage
./algo -BIG grand.saage
```
Input in format *
```
1 root
1 subTreeLeft
0 0 1 subTreeRight
0 0
/*
It means Inorder traversal 1 node exists and 0 don't
In this case root has two child subTreeLeft and subTreeRight
But "0" means child left or right is NULL so we switch to subTreeRight and doing the same. 
*/
```


## Requirements

- Linux Environment
- DOT Language "https://en.wikipedia.org/wiki/DOT_(graph_description_language)"
- Valgrind installed



## Authors

- Navarro Antony
- MUNAITPASOV Maksat

