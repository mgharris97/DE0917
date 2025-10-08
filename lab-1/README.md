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

- if ```-d/--dir``` is provided, **process all** ```*.txt``` files ***files in the DIR` (ignore subfolders)
- if ```-o/--output-dir``` is **omitted**, create a default output folder:
    ```<input_base>_<username>_<studentid>```