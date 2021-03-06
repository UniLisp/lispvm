# The LispVM Intepreter


This program inteprets LispVM bytecode, which is currently a ASCII format,
both for the object files and the actual asm.

## Object format
Each LispVM executable object file starts with the magic sequence "lispvm".
Currently, there is no header.
LispVM load instructions appear in the object, and instructs the VM how to initialise the program.

Slanted text in the format indicates a variable sized argument, regular text inidcates literal text in the program.
### Loader ops
| Op | Format           | Description                                                                        |
|----|------------------|------------------------------------------------------------------------------------|
| p  | *string*;        | Prints *string*                                                                    |
| q  |                  | Quit instead of executing the program                                              |
| #  | *hex*;           | Sets the current loading address                                                   |
| m  | *hex*;           | Initialises the instruction pointer                                                |
| l  | *decimal*;*code* | Loads *code* of size *decimal* into memory starting at the current loading address |
| g  |                  | Starts program exeuction at the already specified IP                               |


## LispVM
Instruction arguments appear inline, since there is no memory or register access yet.

### Current instruction set
| Op   | Format    | Description       |
|------|-----------|-------------------|
| p    | *string*; | Prints *string*   |
| q    |           | Quits gracefully. |
| '\0' |           | Aborts execution. |
