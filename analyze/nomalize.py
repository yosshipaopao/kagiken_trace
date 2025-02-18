import csv
DATA_PATH = '101/dt101.csv'
WRITE_PATH = '101/nm101.csv'

f_data = []
with open(DATA_PATH, 'r') as f:
    reader = csv.reader(f)
    for row in reader:
        dt = []
        for r in row:
            dt.append(r.split(','))
        #print(dt)
        # average
        data = [sum([float(d[0]) for d in dt]) / len(dt), sum([float(d[1]) for d in dt]) / len(dt)]
        f_data.append(data)
# save as csv
with open(WRITE_PATH, 'w',newline="") as f:
    writer = csv.writer(f,delimiter=',')
    writer.writerows(f_data)