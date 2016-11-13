# APEX ISA Semantics

| Opcode | Operands              | Semantics           |
|--------|-----------------------|---------------------|
| ADD    | `dest` `src1` `src2`  | dest := src1 + src2 |
| SUB    | `dest` `src1` `src2`  | dest := src1 - src2 |
| MOVC   | `dest` `#lit`         | dest := #lit + 0    |
| MUL    | `dest` `src1` `src2`  | dest := src1 * src2 |
| AND    | `dest` `src1` `src2`  | dest := src1 & src2 |
| OR     | `dest` `src1` `src2`  | dest := src1 &#124; src2 |
| EX-OR  | `dest` `src1` `src2`  | dest := src1 ^ src2 |
| LOAD   | `dest` `src1` `#lit`  | dest := M[src1 + #lit]|
| STORE  | `src1` `dest` `#lit`  | M[dest + #lit] := src1|
| BZ     | `#lit`| if(Z): PC := PC + #lit/4, else: PC := PC + 1 |
| BNZ    | `#lit`| if(Z): PC := PC + 1, else: PC := PC + #lit/4 |
| BAL    | `src` `#literal`| X := PC + 1; PC := src + #lit/4   |
| JUMP   | `src` `#literal`| PC := src + #lit                  |
| HALT   | _none_ | _execution is halted when this instruction reaches the WB stage_ |
| NOP    | _none_ | _idempotent_ |
