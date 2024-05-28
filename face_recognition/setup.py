import os
import urllib.request

from setuptools import setup


def download_arcface():
    url = "https://raw.githubusercontent.com/serengil/deepface/master/deepface/basemodels/ArcFace.py"
    filename = "ArcFace.py"

    with urllib.request.urlopen(url) as response, open(filename, "wb") as out_file:
        data = response.read()
        out_file.write(data)


def download_gesture_recognizer():
    url = "https://storage.googleapis.com/mediapipe-models/gesture_recognizer/gesture_recognizer/float16/1/gesture_recognizer.task"
    filename = "gesture_recognizer.task"

    with urllib.request.urlopen(url) as response, open(filename, "wb") as out_file:
        data = response.read()
        out_file.write(data)


# download_arcface()
download_gesture_recognizer()

# setup(
#     name="face_recognition_beta",
#     version="0.1",
#     install_requires=[
#         "mtcnn",
#         "matplotlib",
#         "opencv-python",
#         "tensorflow",
#         "numpy",
#         "mediapipe",
#         "tensorflow==2.15.0",
#         "keras==2.15.0",
#         "tf_keras==2.15.1",
#         "deepface",
#         "scikit-learn",
#     ],
# )
