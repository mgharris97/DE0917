import glob
from csv_parser import csv_parse
import csv 
import os

def dir_parse(dir_path):
    files = glob.glob(dir_path + "/*.csv")
    with open("Errors.txt", 'w') as f:
        if not files:
            f.write(f"No CSV files in {dir_path}")
            print (f"No CSV files in {dir_path}")
            return
        for i in files:
            if i.endswith(".csv"):
                #f.write(f"---Start of file {os.path.basename(i)} ---\n")
                print(f"Parsing: {i}")
                csv_parse(i)
               #print(j + '\n')   
         
