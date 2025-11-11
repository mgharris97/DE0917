import csv


#CSV parser
def csv_parse(file_path):
    print(f"Opening file: {file_path}")
    with open(file_path, newline='', mode = 'r') as f:
        csv_file = csv.reader(f)
        for i in csv_file:
            if not i or i[0].startswith("#"):
                continue
            print(i)

def parse_directory(dir_path):
    pass

def load_jason(json_path):
    pass