//
// Created by bp on 8/13/21.
//
#ifndef CAPSTONE_MAINWINDOW_H
#define CAPSTONE_MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QGroupBox>
#include <memory>

#include "mainwindow.h"
#include "opencv.h"

namespace Ui {
    class MainWindow;
}

class Controller;

class MainWindow: public QMainWindow
        {
    Q_OBJECT
        public:
            explicit MainWindow(OpenCV& cv, QWidget *parent = 0);

    signals:
            public slots:
            void uploadHandleButton();
        private:
            shared_ptr<OpenCV> cvPtr_;
            void SetImage();
            void SetImageLabel();
            void SetFoundLabel(OpenCV &cv);
            QLabel *image_label_{new QLabel("No File Selected")};
            OpenCV cv_;
            QPushButton *image_button_{new QPushButton("Select Image")};
            QLabel *found_label_{new QLabel("")};
            QLabel *image_{new QLabel("Upload an image to check if image has a hot dog")};
            QString file_name_;
            Ui::MainWindow *ui;
};
#endif //CAPSTONE_MAINWINDOW_H
