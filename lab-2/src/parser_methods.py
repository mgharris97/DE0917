import csv
import datetime


#CSV parser

errors_list = []
valid_flights = []
def csv_parse(file_path):
    print(f"Opening file: {file_path}")
    with open(file_path, newline='', mode = 'r') as f:
        csv_file = csv.reader(f)
        #line_num = 1;

        flight_id = i[0]
        origin = i[1]
        destination = i[2]
        departure = i[3]
        arrival = i[4]
        price = i[5]

        flight_dict = {
            "FLight ID": flight_id,
            "Origin": origin,
            "Destintion": destination,
            "Departure": departure,
            "Arrival": arrival,
            "Price": price
        }

        for line_num, i in enumerate(csv_file, start=1):   
            flight_id = i[0]
            origin = i[1]
            destination = i[2]
            departure = i[3]
            arrival = i[4]
            price = i[5] 
            if not i:
                continue 
            if len(i) != 6: 
                errors_list.append(f"Line {line_num}: → too many or too few data fields")
            if flight_id.startswith("#"):
                errors_list.append(f"Line {line_num}: {flight_id} → comment line, ignored for parsing")
                continue
            if not (len(2 <= i[0] <= 8) and i[0].isalpha):
                errors_list.append(f"Line {line_num}: {origin} → flight ID not 2-8 alphanumeric character")
                continue
            if not(destination.isupper() and len(destination) == 3 and destination.isalpha()):
                errors_list.append(f"Line {line_num}: {destination} → Invalid destiantion (not 3 uppercase letters)")
                continue
            try:
                d = datetime.strptime(departure, '%Y-%m-%d %H:%M')
                is_departure_date = True
            except ValueError:
                is_departure_date = False
            if not(is_departure_date):
                errors_list.append(f"Line {line_num}: {departure} → Invalid datetime")
                continue

            try:
                d = datetime.strptime(arrival, '%Y-%m-%d %H:%M')
                is_arrival_date = True
            except ValueError:
                is_arrival_date = False
            if not(is_arrival_date):
                errors_list.append


           


            
            


           

            


















              
            

                flight_dict = {
                    "flight_id": flight_id,
                    "origin": origin,
                    "destination": destination,
                    "departure": departure,
                    "arrival": arrival,
                    "price": price
                }
                data_list.append(flight_dict);
    
                

            #if current row is empty or if the first cell in the current row begins with #
            if not i or i[0].startswith("#"):
                continue
            print(i)

        

def parse_directory(dir_path):
    pass

def load_jason(json_path):
    pass