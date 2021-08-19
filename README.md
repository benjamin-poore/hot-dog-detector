# Hot Dog Detector

## General Information
- This program uses OpenCV to detect if an image contains a hot dog
- If a hot dog it found, it will display the image with a square around the image and labeled as a hot dog. At the bottom of the screen, there will be a green box stating how many hot dogs were found as well and the top confidence level of any of the hot dogs that were found. If no hot dogs are found a red box will appear at the bottom of the screen with an error.
- Detection of objects is using tensorflow framework
- Config for tensorflow is ssd_mobilenet_v2_coco_2018_03_29.pbtxt.txt
- QT5 is used to create a graphical interface 
- This program was tested on Windows and Linux, Mac may be supported, but not tested

## Required Libraries 
- QT5
- OpenCV - 3.4.15
- cmake - minimum version 3.16
- - sudo apt-get update
- - sudo apt-get install cmake
- CXX_STANDARD 14

## Installation Instructions 
- Windows install

- Download QT from www.qt.io/download
- - go to site
- - click Download. Try.
- - Under try QT download qt now
- - fill out form for evaluation
- - download file
- - sign in with info from form
- - install qt5

- Download OpenCV from https://sourceforge.net/projects/opencvlibrary/files/3.4.15/opencv-3.4.15-vc14_vc15.exe/download
- - go through install of opencv

- install hot dog detecor
- - unzip project 
- - go to directory, create a build folder
- - open terminal in the build directory
- - execute cmake ..
- - execute make
- - execute ./capstone to run program

- Linux install
-  install QT
- - executing sudo apt-get install qt5-default
- install openCV 
- - cd ~/<my_working_directory>
- - git clone https://github.com/opencv/opencv.git
- - cd ~/opencv
- -mkdir build
- - cd build
- - cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
- - make -j7 # runs 7 jobs in parallel
- - sudo make install

- install hot dog detecor
- - git clone https://github.com/benjamin-poore/capstone.git
- - go to directory, create a build folder
- - open terminal in the build directory
- - execute cmake ..
- - execute make
- - execute ./capstone to run program

## Class Structure
- There are two classes in this program (OpenCV and MainWindow)
- MainWindow class accepts user input and updates the QT window
- OpenCV obtains information from MainWindow through the runClassification function
- MainWinow then gets the information back by using getter functions to update the view
- main.cpp starts the QT application

## Rubric Requirements 
- The project demonstrates an understanding of C++ functions and control structures.
- - opencv.cpp line 41 a for loop is used to loop through all obected dectections
- - opencv.cpp line 19 a while loop is used to obtain all class names and place into a vector of strings
- - opencv.cpp lines 46 and 48 have conditional if statements
- - mainwindow.cpp line 67 has an if statement
- - mainwindow.cpp line 72 has an else statement
- - functions are used throughout all of the classes and are seperated into source and header files

- The project reads data from a file and process the data, or the program writes data to a file.
- - opencv.cpp lines 17, 25 and 26  reads from file
- - mainwindow.cpp line 52 reads from file
- - opencv.cpp line 68 writes to file

- The project accepts user input and processes the input.
- - mainwindow.cpp line 35 accepts user input and sends input to opencv class to be processed

- The project uses Object Oriented Programming techniques.
- - program is sepereated into classed mainwindow.cpp, mainwindow.h, opencv.cpp and opencv.h
- - classes use setter and getters if necessary

- Classes use appropriate access specifiers for class members.
- - opencv.h includes public access on line 9 and private on line 16
- - mainwindow.h includes public access on line 22 and private on line 27

- Class constructors utilize member initialization lists.
- - opencv.h and mainwindow.h use {} initialization lists

- Classes encapsulate behavior.
- - mainwindow.cpp uses opencv.cpp getter methods on lines 67-76

- The project makes use of references in function declarations.
- - mainwindow.cpp lines 30 and 44 use pass by reference
- - most of mainwindow.cpp is done in pointers(not reference, just thought I would state that here :) )

- The project uses destructors appropriately.
- - mainwindow.cpp uses pointers on all labels and buttons, however they are tied to the parent Q_OBJECT and are automatically deleted once Q_OBJECT goes out of scope. No additional desturctor was necessary.


