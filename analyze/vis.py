import csv
import cv2
import numpy as np


NUM = -100
DATA_PATH = f'{NUM}/nm{NUM}.csv'
PT_PATH   = f'{NUM}/pt{NUM}.csv'
VID_PATH    = f'{NUM}/{NUM}_rs.mp4'
IMG_PATH    = f'{NUM}/{NUM}.jpg'
# import csv data
f_data = []
with open(DATA_PATH, 'r') as f:
    reader = csv.reader(f)
    for row in reader:
        f_data.append(list(map(float, row)))

pt_data = []
with open(PT_PATH, 'r') as f:
    reader = csv.reader(f)
    for row in reader:
        pt_data.append(list(map(float, row)))


cv2.namedWindow('image')
vid = cv2.VideoCapture(VID_PATH)

vid_frame = vid.read()[1]

# show the first frame
#cv2.imshow('image', vid_frame)
# mapping csv data to the first frame
for feature in f_data:
    cv2.circle(vid_frame, (int(feature[0]), int(feature[1])), 5, (0, 0, 255), -1)

cv2.polylines(vid_frame, [np.array(pt_data, np.int32)], False, (0, 255, 0), 2)

cv2.imshow('image', vid_frame)
cv2.waitKey(0)

#save the image
cv2.imwrite(IMG_PATH, vid_frame)
