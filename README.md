# apex-sim
A simulator for the Architecture Pipeline EXample (APEX) ISA

## Prerequisites
| Required | Version |
|----------|---------|
| Clang    | Tested with Apple Clang 8.0.0 for x86_64 and Debian Clang 3.0-6.2 for x86_64.|
| GNU Make | Tested with GNU Make 3.81 |

Note for Binghamton University users: this software is compatible with the `remote.cs.binghamton.edu` system. It is incompatible with the `bingsuns.binghamton.edu` system.

## Installation

1. In the makefile, set the value of the `CC` variable to your C++ compiler path.
2. Build the software using the `apex-sim` or `all` make target.
3. To remove build files, use the `clean` target.

## Usage
        apex-sim <instruction input file path>

Sample instruction input files are located in `$(APEX_HOME)/inputs`.

Once execution begins, the following commands can be used:

| Command | Action                         |
|---------|--------------------------------|
| `i`     | Initialize the simulator state |
|`s n`    | Simulate `n` number of cycles  |
| `d`     | Display simulator internal state |
| `q`     | Quit the simulator             |
| `h`     | Display a help message         |

## Instruction Semantics
See `$(APEX_HOME)\docs\semantics.md`
