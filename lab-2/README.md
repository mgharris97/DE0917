## Python Final Assignment: Flight Schedule Parser and Query Tool

**Submit:** 
A '.zip' file with all source code .py files with correct stucture and anything else needed, OR/AND submit URL of your github repository.

---
## Overview 
Write a Python program that can:

1. Parse one or more flight schedule `.csv` files  
2. Validate and separate **valid** and **invalid** records  
3. Export results as:
   - `db.json` → valid flights  
   - `errors.txt` → invalid lines  
4. Optionally **load an existing JSON database** instead of reparsing  
5. Execute queries from a JSON file and save results
---
## Command-Line Interface

| Argument | Description | 
|----------|-------------|
| `-i path/to/file.csv` | 	Parse a single CSV file. |
| `-d path/to/folder/` | Parse all `.csv` files in a folder and combine results. |
| `-o path/to/output.json` | Optional custom output path for valid flights JSON. |
| `-j path/to/db.json` | Load existing JSON database instead of parsing CSVs. |
| `-q path/to/query.json` | 	Execute queries defined in a JSON file on the loaded database. |
| `-h` | 	Show help message. |

