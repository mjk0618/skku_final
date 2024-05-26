import argparse
import os
import warnings

import ArcFace
import cv2
import matplotlib.pyplot as plt
import numpy as np
from mtcnn.mtcnn import MTCNN
from sklearn.metrics.pairwise import cosine_similarity
from tensorflow.keras.preprocessing import image

warnings.filterwarnings("ignore")

model = ArcFace.load_model()
face_detector = MTCNN()

def detect_face(img):
    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB) #mtcnn expects RGB but OpenCV read BGR
    detections = face_detector.detect_faces(img_rgb)
    detection = detections[0]
    x, y, w, h = detection["box"]
    detected_face = img[int(y):int(y+h), int(x):int(x+w)]
    return detected_face

def preprocess_face(img, target_size=(112,112)):
    img = cv2.imread(img)
    img = detect_face(img)
    img = cv2.resize(img, target_size)
    img_pixels = image.img_to_array(img)
    img_pixels = np.expand_dims(img_pixels, axis = 0)
    img_pixels /= 255 #normalize input in [0, 1]
    return img_pixels

def img_to_encoding(path, use_model=False):
    img = preprocess_face(path)
    if use_model:
        return model.predict(img)[0]
    else:
        return img
    
def calculate_distance(point1, point2):
    return np.linalg.norm(np.array(point1) - np.array(point2))

def calculate_cosine_similarity(array1, array2):
    return cosine_similarity(array1.reshape(1, -1), array2.reshape(1, -1))[0][0]
    

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Get the encoding of two images")
    parser.add_argument('--data_dir', default='data')
    parser.add_argument('--image1', default='img1.jpg')
    parser.add_argument('--image2', default='img2.jpg')
    parser.add_argument('--use_model', default=False)

    args = parser.parse_args()

    path_to_image1 = os.path.join(args.data_dir, args.image1)
    path_to_image2 = os.path.join(args.data_dir, args.image2)

    encoding1 = img_to_encoding(path_to_image1, args.use_model)
    encoding2 = img_to_encoding(path_to_image2, args.use_model)

    similarity = calculate_cosine_similarity(encoding1, encoding2)

    print(f"Cosine similarity between entity two entities: {similarity:.4f}")
