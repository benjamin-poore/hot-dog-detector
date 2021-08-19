cmake_minimum_required(VERSION 3.13)
project(capstone)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package( OpenCV 4 REQUIRED )
if( OpenCV_FOUND )
    list( APPEND ThirdParty_LIBS ${OpenCV_LIBS} )
    include_directories( ${OpenCV_INCLUDE_DIRS} )
endif( OpenCV_FOUND )

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(capstone main.cpp mainwindow.cpp mainwindow.h opencv.cpp opencv.h)
target_link_libraries(${PROJECT_NAME}
        pthread
        ${OpenCV_LIBS}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

