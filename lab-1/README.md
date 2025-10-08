## Pythonic Arithmetic Parser in C
## Goal

Write a C program that evaluates arithmetic expressions from text files using (mostly) Python’s operator rules and standard C (similar to Java) arithmetic semantics. The program must:

- Read an input file (or a directory of files).

- Parse and evaluate expressions.

- Report either the numeric result or a precise error location.

- Write the result to an output file with a specific naming convention.

## CLI & I/O
## Invocation

```
calc [-d DIR | --dir DIR] [-o OUTDIR | --output-dir OUTDIR] input.txt
```

<<<<<<< HEAD
- if `-d/--dir` is provided, **process all** `*.txt` files ***files in the DIR` (ignore subfolders)
=======
- if `-d/--dir` is provided, **process all** ```*.txt``` files ***files in the DIR` (ignore subfolders)
>>>>>>> 29c7236e2dce1d0b01212aa1fc33ea07fab4e05b
- if `-o/--output-dir` is **omitted**, create a default output folder:
    `<input_base>_<username>_<studentid>`
    Example: `labs_valdis_12345/`
- if `-o/--output-dir` **is provided** and doe snot exist, create it

## Output file name
<<<<<<< HEAD
for each input `task1.txt`, produce
=======
for each input ```task1.txt```, produce
>>>>>>> 29c7236e2dce1d0b01212aa1fc33ea07fab4e05b
```task1_<name>_<lastname>_<studentid>.txt```
The file contains **either** the result (single line) **or** `ERROR:<pos>`
> **Character position** is **1-based,** counting every char in the file, including `\n` as one character

## Input Assumptions (Baseline)
- **ASCII** only.
- Whitespace may appear anywhere.
- At minimum (grade 4-6) inputs are **single line ≤ 100 chars** (later grades extend this)
<<<<<<< HEAD
- Expressions can be **integer** and, for higher grades, **float*8 (IEEE 754 double)

## Features by Grade (Rubric)
## Grade 4/10 - Minimal Pass
- Single line (≤ 100 chats)
- **Integers** only (base-10, optional leading `+`/`-`)
- **Operators:** `+``-` (binary)
- Output: numeric results (via integer text)
- On any parse/eval error: `ERROR:<pos>` (1-based char index)

## Grade 5/10 - Positioned Errors
- Same grade 4 **plus**
- **Accurate error position:** if the first error is at character 57, output `ERROR:57`.
    - Examples of errors: invalid token, unexpected end, two operators in a row, leading operator without operand, etc.

## Grade 6/10 - Multiplication (+ optional floats)
- Add `*` (binary).
- **Additional challenge:** support **floats (64-bit)** mixed with ints.
    - If floats are supported, print using `%.15g` (see Output formatting below).
- Still single line ≤ 100 chars.

# Grade 7/10 - Division 

=======
>>>>>>> 29c7236e2dce1d0b01212aa1fc33ea07fab4e05b
