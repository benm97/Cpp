cmake_minimum_required(VERSION 3.8)
project(ex2)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES Ikea.cpp Product.cpp Product.h Unit.cpp Unit.h Continuous.cpp Continuous.h Cloth.cpp Cloth.h Candy.cpp Candy.h Furniture.cpp Furniture.h Table.cpp Table.h Chair.cpp Chair.h Utensil.cpp Utensil.h Book.cpp Book.h)
add_executable(ex2 ${SOURCE_FILES})