# APEX ISA Semantics		

| Opcode | Operands | Semantics | _dest_ set | _src_ set|
|--------|----------|-----------|------------|----------|		
| ADD    | `dest, src1, src2` | `dest` := `src1` + `src2` | 0 | 1, 2 |
| SUB    | `dest, src1, src2` | `dest` := `src1` - `src2` | 0 | 1, 2 |		
| MOVC   | `dest, #lit` | `dest` := `#lit` + 0      | 0 | |
| MUL    | `dest, src1, src2` | `dest` := `src1` * `src2` | 0 | 1, 2 |
| AND    | `dest, src1, src2` | `dest` := `src1` & `src2` | 0 | 1, 2 |
| OR     | `dest, src1, src2` | `dest` := `src1` &#124; `src2` |	0 | 1, 2 |
| EX-OR  | `dest, src1, src2` | `dest` := `src1` ^ `src2` | 0 | 1, 2 |
| LOAD   | `dest, src1, #lit` | `dest` := M[`src1` + `#lit`]| 0 | 1 |
| STORE  | `src1, src2, #lit` | M[`src2` + `#lit`] := `src1`| | 0,1 |
| BZ     | `#lit` | if(`Z`): `PC` := `PC` + `#lit`, else: `PC` := `PC` + 4 | | |		
| BNZ    | `#lit` | if(`Z`): `PC` := `PC` + 4, else: `PC` := `PC` + `#lit` |	| |
| BAL    | `src, #lit` | `X` := `PC` + 4; `PC` := `src` + `#lit` | | 0 |
| JUMP   | `src, #lit` | `PC` := `src` + `#lit` | | 0 |
| HALT   | _none_ | _execution is halted when the IQ and ROB are empty and this instruction advances to DRF2_ (no more instructions await dispatch)|
| NOP    | _none_ | _idempotent_ |
