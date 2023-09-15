# apex-sim

This is a simulator for the Architecture Pipeline EXample (APEX) Instruction Set Architecture (ISA).

- Release version _1.x_ implemented an in-order execution pipeline with two parallel function units.
- Release version _2.x_ implements an out-of-order execution pipeline with four function units using register renaming and a unified register file (URF). To support out-of-order execution, APEX uses a centralized issue queue (IQ) and reorder buffer (ROB).

The ISA semantics can be found in [docs/semantics.md](https://github.com/colematt/apex-sim/blob/master/docs/semantics.md). The user interface commands can be found in [docs/commands.md](https://github.com/colematt/apex-sim/blob/master/docs/commands.md).


## Prerequisites
| Required | Version |
|----------|---------|
| C++ Compiler | Tested with Apple Clang 8.0.0 for x86_64 and Debian Clang 3.0-6.2 for x86_64. More recent compilers supporting the _C++11_ standard should be acceptable.|
| GNU Make | Tested with GNU Make 3.81. More recent versions should be acceptable. |

Note for Binghamton University users: this software is compatible with the `remote.cs.binghamton.edu` system. It is incompatible with the `bingsuns.binghamton.edu` system.

## Installation

In this project, `$(APEX_HOME)` is the path to the directory containing this file, which is the top-level project directory. The project specification and documentation are in `$(APEX_HOME)/docs`. The project source code is in `$(APEX_HOME)/srcs`.

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
