# APEX ISA Semantics		

| Opcode | Operands              | Semantics           |		
|--------|-----------------------|---------------------|		
| ADD    | `dest` `src1` `src2`  | `dest` := `src1` + `src2` |		
| SUB    | `dest` `src1` `src2`  | `dest` := `src1` - `src2` |		
| MOVC   | `dest` `#lit`         | `dest` := `#lit` + 0      |		
| MUL    | `dest` `src1` `src2`  | `dest` := `src1` * `src2` |		
| AND    | `dest` `src1` `src2`  | `dest` := `src1` & `src2` |		
| OR     | `dest` `src1` `src2`  | `dest` := `src1` &#124; `src2` |		
| EX-OR  | `dest` `src1` `src2`  | `dest` := `src1` ^ `src2` |		
| LOAD   | `dest` `src1` `#lit`  | `dest` := M[`src1` + `#lit`]|		
| STORE  | `src1` `dest` `#lit`  | M[`dest` + `#lit`] := `src1`|		
| BZ     | `#lit`| if(`Z`): `PC` := `PC` + `#lit`, else: `PC` := `PC` + 4 |		
| BNZ    | `#lit`| if(`Z`): `PC` := `PC` + 4, else: `PC` := `PC` + `#lit` |		
| BAL    | `src` `#lit`| `X` := `PC` + 4; `PC` := `src` + `#lit` |		
| JUMP   | `src` `#lit`| `PC` := `src` + `#lit` |		
| HALT   | _none_ | _execution is halted when this instruction reaches the WB stage_ |		
| NOP    | _none_ | _idempotent_ |
