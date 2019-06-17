cmake_minimum_required(VERSION 3.6)
project(naive_bayes)

set(CMAKE_CXX_STANDARD 14)

configure_file(data/test_labels.txt test_labels.txt COPYONLY)
configure_file(data/test_states.txt test_states.txt COPYONLY)
configure_file(data/train_labels.txt train_labels.txt COPYONLY)
configure_file(data/train_states.txt train_states.txt COPYONLY)

add_executable(naive_bayes src/main.cpp src/classifier.cpp src/classifier.h src/helpers.h)