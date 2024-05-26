# Setup
1. Run the following command to install required packages.

    ```shell
    pip install .
    ```

2. Access the `ArcFace.py` and modify `load_model` function as descripted below.

    ```python
    # Original Code
    def load_model():
        ...
        home = folder_utils.get_deepface_home()

        file_name = "arcface_weights.h5"
        output = home + "/.deepface/weights/" + file_name
        ...
    ```

    ```python
    # Modified Code
    def load_model():
        ...
        os.makedirs('weights', exist_ok=True) # Remove the code defining `home` variable.

        file_name = "arcface_weights.h5"
        output = 'weights' + file_name
        ...
    ```

# Execution
## Face Recognition
Run the following command to get the similarity between two images.

```shell
python face_recognition.py `
    --data_dir {data_dir} `
    --image1 {image file name 1} `
    --image2 {image file name 2}

# Example
python face_recognition.py `
    --data_dir "data" `
    --image1 "person_1_1.jpg" `
    --image2 "person_2_1.jpg"
```

## Hand Gesture
Run the following command to get the landmarks and pre-defined hand gestures.

```shell
python hand_gesture.py `
    --data_dir {data_dir} `
    --image {image file name}

# Example
python hand_gesture.py `
    --data_dir "data" `
    --image "hand.jpg"
```