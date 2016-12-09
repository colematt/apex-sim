# apex-sim
This is a simulator for the Architecture Pipeline EXample (APEX) Instruction Set Architecture (ISA).

In this project, `$(APEX_HOME)` is the path to the directory containing this file, which is the top-level project directory. The project specification and documentation are in `$(APEX_HOME)/docs`. The ISA semantics can be found in `$(APEX_HOME)/docs/semantics.md`.


## Prerequisites
| Required | Version |
|----------|---------|
| C++ Compiler | Tested with Apple Clang 8.0.0 for x86_64 and Debian Clang 3.0-6.2 for x86_64. More recent compilers supporting the _C++11_ standard should be acceptable.|
| GNU Make | Tested with GNU Make 3.81. More recent versions should be acceptable. |

Note for Binghamton University users: this software is compatible with the `remote.cs.binghamton.edu` system. It is incompatible with the `bingsuns.binghamton.edu` system.

## Installation

In the makefile, set the value of the `CXX` variable to your C++ compiler path. Build the software using the `apex-sim` or `all` target.

```
$ make -C $(APEX_HOME)
```

To remove build files, use the `clean` target.

```
$ make -C $(APEX_HOME) clean
```

## Usage

```
$ apex-sim <instruction input file path>
```

Sample instruction input files are located in `$(APEX_HOME)/inputs`.

Once execution begins, the following commands can be used:

|Command          | Action |
|:---------------:|--------|
| i               | Initialize the simulator state |
| s <n>           | Simulate <n> number of cycles |
| d all           | Display the full simulator internal state |
| d cpu           | Display CPU stage contents |
| d rt            | Display Front-end and Back-end Register Tables |
| d iq            |Display Issue Queue entries and status |
| d rob           |Display ROB contents |
| d mem <a1> <a2> |Display memory from address <a1> to <a2> |
| d stats         |Display Stats |
| urf <n>         |Set URF Size to <n> physical registers |
| q               |Quit the simulator |
| h               |Display this help message" |
