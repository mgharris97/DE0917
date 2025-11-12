# main.py
# Matthew Harris
# 241ADB166
# 11 November, 2025
# GitHub repo: https://github.com/mgharris97/programming-languages/tree/main/lab-2

import argparse
import csv
import os
from csv_parser import csv_parse
def main():
    ##Adding arguments to the Argument Parser
    ##Specifying metavar display name for arguments to be empty to avoid --INPUT, etc.
    parser = argparse.ArgumentParser(description="Flight Schedule Parser and Query Tool")
    parser.add_argument("-i", "--input", metavar="", help="Parse a single CSV file. Format: -i path/to/file.csv")
    parser.add_argument("-d", "--directory", metavar="", help="Parse all .csv files in a folder and combine results. Format: -d path/to/folder/")
    parser.add_argument("-o", "--output", metavar="", help="Optional custom output path for valid flights JSON. Format: -o path/to/output.json")
    parser.add_argument("-j","--json", metavar="", help="Load existing JSON database instead of parsing CSVs. Format: -j path/to/db.json")
    parser.add_argument("-q", "--query", metavar="", help="Execute queries defined in a JSON file on the loaded database. Format: -q path/to/query.json	")
    args = parser.parse_args()
    single_file_path = None
    dir_path = None
    json_path = None
    
    if args.input:
        single_file_path = args.input
    elif args.directory:
        dir_path = args.directory
        parse_directory(dir_path) #implement parse_directory
    elif args.json:
        json_path = args.json
        load_jason(json_path) #implement load_json
    
    if single_file_path: 
        csv_parse(single_file_path)
    else:
        print ("No input file specified")




        






#call to main()    
if __name__ == "__main__":
    main()

