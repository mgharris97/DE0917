import glob
from csv_parser import csv_parse
import csv 


def dir_parse(dir_path):
    files = glob.glob(dir_path + "/*.csv")
    for i in files:
        if i.endswith(".csv"):
           csv_parse(i)
               #print(j + '\n')
           # 
         
