import cv2
import os
import time

# Open webcam
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FPS, 24)

# Output folder
output_dir = "auto_frames"
os.makedirs(output_dir, exist_ok=True)

# 🔥 DELETE OLD IMAGES BEFORE STARTING CAPTURE
for file in os.listdir(output_dir):
    file_path = os.path.join(output_dir, file)
    if os.path.isfile(file_path):
        os.remove(file_path)

frame_count = 0
fps = 24
interval = 1 / fps

print("Capturing frames automatically... Press CTRL+C to stop")

try:
    while True:
        start_time = time.time()

        ret, frame = cap.read()
        if not ret:
            print("Failed to grab frame")
            break

        filename = f"{output_dir}/frame_{frame_count:06d}.jpg"
        cv2.imwrite(filename, frame)
        frame_count += 1

        elapsed = time.time() - start_time
        sleep_time = interval - elapsed
        if sleep_time > 0:
            time.sleep(sleep_time)

except KeyboardInterrupt:
    print("\nStopped by user")

cap.release()
cv2.destroyAllWindows()

