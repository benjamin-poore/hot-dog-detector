//
// Created by bp on 8/13/21.
//

#include <QFileDialog>
#include <QLabel>
#include "mainwindow.h"
#include <QHBoxLayout>
#include "opencv.h"
#include <QWidget>

#include <memory>

MainWindow::MainWindow(OpenCV& cv, QWidget *parent) : QMainWindow(parent){
    // use QWidget to have all heap elements deleted once scope leaves
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    image_->setFixedHeight(500);

    layout->addWidget(image_button_);
    layout->addWidget(image_);
    layout->addWidget(image_label_);
    layout->addWidget(found_label_);

    widget->show();
    // pass MainWindow by reference
    // connect image selection button to image selection
    connect(image_button_, &QPushButton::released, this, &MainWindow::uploadHandleButton);
}

void MainWindow::uploadHandleButton(){
    // allow image selection in png, jpeg, jpg, and bmp format
    file_name_ = QFileDialog::getOpenFileName(this,
                                              tr("Open Image"), "/home/bp", tr("Image Files (*.png *.jpeg *.jpg *.bmp)"));
    // protect program from crashing if file select is closed without selecting image
    if(file_name_.toStdString().length() > 0){
        SetImageLabel();
        // run classifier to detect hot dogs


        cv_.RunClassifier(file_name_.toStdString());
        // set image classifier detected
        SetImage();
        // pass cv by reference
        // set custom label depending on what classifier found
        SetFoundLabel(cv_);
    }
}

void MainWindow::SetImage(){
    // read file that classifier made
    QPixmap pic("../output/processed_image.jpeg");
    // scale image to fit container in gui to not have the gui change sizes
    pic = pic.scaled(500, 500, Qt::KeepAspectRatio);
    // removes label info instructions and places image in place
    image_->setPixmap(pic);
}

void MainWindow::SetImageLabel() {
    // change QString to QFileInfo to parse filename
    QFileInfo fi = file_name_;
    image_label_->setText("File Name: " + fi.fileName());
}

void MainWindow::SetFoundLabel(OpenCV &cv){
    // if a hot dog is found create a label that shows how many and top confidence level if not found display error message
    if(cv.GetHotDogCount() > 0){
        std::string msg = "There were " + std::to_string(cv.GetHotDogCount()) + " hot dog(s) found. The highest confidence is: " +
                          std::to_string(static_cast<int>((cv.GetTopConfidence() * 100))) + "%.";
        found_label_->setText(QString::fromStdString(msg));
        found_label_->setStyleSheet("QLabel { background-color : green; color : white;}");
    }else{
        found_label_->setText("Unable to find any hot dogs in the picture, please try another image!");
        found_label_->setStyleSheet("QLabel { background-color : red; color : white;}");
    }
    found_label_->setWordWrap(true);
}
