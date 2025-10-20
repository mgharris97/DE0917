 ## DE0917 Labs

 This repository contains all lab assignments fro DE0917 class
 Each lab-x folder contains its README and all relevant files
 
## Folder Structure
```bash
├── lab-1
│   ├── calc
│   ├── include
│   ├── README.md
│   └── src
├── lab-2
│   ├── build
│   ├── include
│   ├── Makefile
│   ├── README.md
│   └── src
└── README.md
```

## 👷‍♂️ How to compile and build lab-1 👷‍♂️
Requirements
	- C Compiler: GCC (supports C17)
```bash
gcc -Wall -Wextra -std=c17 -o calc calc.c
```
- (-Wall -Wextra) shows useful warnings
- (-std=c17) enforeces C17 standard
- (-o calc) create an exe with the name calc

## How to Run
```bash
calc [-d DIR | --dir DIR] [-o OUTDIR | --output-dir OUTDIR] input.txt
```
For example:
```
./calc -d input_files -o results
```

Author
Matthew Harris 
Oct. 8, 2025
