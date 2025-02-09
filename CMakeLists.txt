cmake_minimum_required(VERSION 3.16)

project(qtdatabase VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set(CMAKE_CXX_FLAGS "-O0")
#set(CMAKE_C_FLAGS "-O0")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets Network Sql)


qt_add_executable(qtdatabase
    MANUAL_FINALIZATION
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    raiiguard.h
    settings.h
    settings.cpp
    datatable.h
    datatable.cpp
)

target_link_libraries(qtdatabase PRIVATE Qt6::Widgets Qt6::Network Qt6::Sql)

qt_finalize_executable(qtdatabase)
