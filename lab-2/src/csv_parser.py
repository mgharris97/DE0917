import csv
from datetime import datetime


#CSV parser

errors_list = []
valid_flights = []
def csv_parse(file_path):
    print(f"Opening file: {file_path}")
    with open(file_path, newline='', mode = 'r') as f:
        csv_file = csv.reader(f)
        for line_num, i in enumerate(csv_file, start=1):   

            if not i:
                continue 
            if i[0].startswith("#"):
                errors_list.append(f"Line {line_num}: {i[0]} → comment line, ignored for parsing")
                continue
            if len(i) != 6: 
                errors_list.append(f"Line {line_num}: {i} → invalid format")
                continue
            
            flight_id = i[0]
            origin = i[1]
            destination = i[2]
            departure = i[3]
            arrival = i[4]
            price = i[5] 
            if not (2 <= len(i[0]) <= 8) and i[0].isalpha:
                errors_list.append(f"Line {line_num}: {flight_id} → flight ID not 2-8 alphanumeric character")
                continue
            if not(destination.isupper() and len(destination) == 3 and destination.isalpha()):
                errors_list.append(f"Line {line_num}: {destination} → Invalid destiantion (not 3 uppercase letters)")
                continue
            try:
                departure_time = datetime.strptime(departure, '%Y-%m-%d %H:%M')
                is_departure_date = True
            except ValueError:
                is_departure_date = False
            if not(is_departure_date):
                errors_list.append(f"Line {line_num}: {departure} → Invalid departure datetime")
                continue

            try:
                arrival_time = datetime.strptime(arrival, '%Y-%m-%d %H:%M')
                is_arrival_date = True
            except ValueError:
                is_arrival_date = False
            try:
                if not (arrival_time > departure_time):
                    errors_list.append(f"Line {line_num}: {arrival} → Arrival time occurs before departure → {departure}")
                    continue
            except ValueError:
                errors_list.append(f"Line {line_num}: {arrival} → Invalid arrival time")
                continue

            if not(isinstance(float(price), float)):
                errors_list.append(f"Line {line_num}: {price} → Price must be a positive float number")
                continue
        
        with open("Errors.txt", mode='w+') as error_file:
            for i in errors_list:
                error_file.write(i + "\n")



