# Imago
Multithreaded CLI Image Editor

## How to run using interactive command-line interface
1. Clone the repository
2. Drag and drop the image you want to edit inside the 'input-images' folder
3. Using terminal, navigate to the directory of the repository
4. Run the following:
```shell script
./imago
```
5. Follow the prompts
6. Your edited images will be exported to the 'exported-images' folder

Note: You can only use png images. If your image isn't png, convert it.

## How to run by passing command-line arguments
1. Clone the repository
2. Drag and drop the png image you want to edit inside the 'input-images' folder
3. Using terminal, navigate to the directory of the repository
4. Run by passing the arguments straight from the command-line

The arguments are:
```shell script
./imago imageFileName luminance saturation hue highlights shadows vignette
```
You need to pass an integer in range \[-100, 100\] (inclusive). For example:
```shell script
./imago image2 -15 10 0 -10 0 10
```
Note: Do not include the file type in the first argumnet. i.e. if the file is called 'image2.png', don't including the '.png' part in the argumnet.

6. Your edited images will be exported to the 'exported-images' folder

Note: You can only use png images. If your image isn't png, convert it.

## How to compile

The compiled files are already in the repository, but if you make changes, you can compile the project again.

To compile the project, navigate to the repository using terminal, and run the following:
```shell script
make
```

## Before vs After
<img src="https://user-images.githubusercontent.com/48306717/167314755-9f64d83c-b088-4ba1-a637-ed5de7efe5e7.png" alt="image2" width="50%"/><img src="https://user-images.githubusercontent.com/48306717/167314782-ed218062-7c70-443a-a851-dc20a0ba35e5.png" alt="out-image2" width="50%"/>

<img src="https://user-images.githubusercontent.com/48306717/167314763-11cb2195-5bf8-4d85-b4a4-8d7f21ee3e27.png" alt="image3" width="50%"/><img src="https://user-images.githubusercontent.com/48306717/167314785-306aed5f-e49f-4a46-b0c1-54f63b2d600e.png" alt="out-image3" width="50%"/>

Settings for above: luminance: -10, saturation: 10, hue: 0, highlights: -10, shadows: 0 vignette: 10 (-10 10 0 -10 0 10)

## Citation
Used help from the cs221util library for png and pixel structures. I used them to read and write png files and minipulate the pixels. Created by CPSC 221 from UBC.
