cmake_minimum_required(VERSION 3.16)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(SnakeGame
    main.cpp
    snakewidget.cpp
    snakewidget.h
)

target_link_libraries(SnakeGame Qt5::Widgets)
qt_add_resources(RESOURCES resources.qrc)
target_sources(SnakeGame PRIVATE ${RESOURCES})
