import cv2
import numpy as np

NUM=-100
CSV_PATH = f'{NUM}/pt{NUM}.csv'
VID_PATH = f'{NUM}/{NUM}_rs.mp4'

# Initialize a list to store points
points = []

# Mouse callback function to capture points
def click_event(event, x, y, flags, params):
    if event == cv2.EVENT_LBUTTONDOWN:
        points.append((x, y))
        cv2.circle(img, (x, y), 5, (0, 0, 255), -1)
        cv2.imshow('image', img)

# Load an image

cv2.namedWindow('image')
vid = cv2.VideoCapture(VID_PATH)

img = vid.read()[1]
#img = np.zeros((512, 512, 3), np.uint8)
cv2.imshow('image', img)
cv2.setMouseCallback('image', click_event)

# Wait until the user presses the 'q' key
while True:
    key = cv2.waitKey(1) & 0xFF
    if key == ord('q'):
        break

# Convert points to a numpy array
points = np.array(points, dtype=np.int32)

# Fit a curve to the points with some twist
if len(points) > 1:
    curve = cv2.polylines(img, [points], isClosed=False, color=(0, 255, 0), thickness=2)
    # Save the points to a file
    np.savetxt(CSV_PATH, points, fmt='%d', delimiter=',')

# Display the final image with the curve
cv2.imshow('image', img)
cv2.waitKey(0)
cv2.destroyAllWindows()