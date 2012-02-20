project(libqcpp)

set(CMAKE_CXX_FLAGS "--std=c++0x -Wall -fopenmp")

add_library(qcpp qgates.cpp 
	qram.cpp
	qram.inl
	qram.h
	qgates.h
)

add_subdirectory(examples)