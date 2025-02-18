import csv
import numpy as np

NUM = 175
NM_DATA = f'{NUM}/nm{NUM}.csv'
NM_POINTS = f'{NUM}/pt{NUM}.csv'
FINAL_PATH = f'{NUM}/final.txt'

# Example usage
# csv data
f_data = []
with open(NM_DATA, 'r') as f:
    reader = csv.reader(f)
    for row in reader:
        f_data.append(list(map(float, row)))
# base points
points_data = []
with open(NM_POINTS, 'r') as f:
    reader = csv.reader(f)
    for row in reader:
        points_data.append(list(map(float, row)))

# points_data をpolylinesとしたときf_data各点の距離を求める
distances = []
for p in f_data:
    p = np.array(p)
    d = []
    for i in range(len(points_data)-1):
        p1 = np.array(points_data[i])
        p2 = np.array(points_data[i+1])
        # p1p2の直線とpの距離を求める
        d1 = np.linalg.norm(np.cross(p2-p1, p1-p))/np.linalg.norm(p2-p1)
        d.append(d1)
    #print(d)
    distances.append(min(d))

# 距離から分散を求める
variance = np.var(distances)
print(variance)

# 距離の平均を求める
mean = np.mean(distances)
print(mean)

# 距離の最大値を求める
max_distance = max(distances)
print(max_distance)

#結果をファイルに書き込む
with open(FINAL_PATH, 'w') as f:
    f.write(f'{variance}\n')
    f.write(f'{mean}\n')
    f.write(f'{max_distance}\n')