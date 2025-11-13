import glob
from csv_parser import csv_parse
import csv 


def dir_parse(dir_path):
    files = glob.glob(dir_path + "/*.csv")
    for i in files:
        if i.endswith(".csv"):
           f=open(i, 'r')
           for j in f:
               print(j + '\n')
           #  perform calculation