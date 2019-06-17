cmake_minimum_required(VERSION 3.6)
project(naive_bayes)

set(CMAKE_CXX_STANDARD 14)

configure_file(data/test_labels.txt test_labels.txt COPYONLY)
configure_file(data/test_states.txt test_states.txt COPYONLY)
configure_file(data/train_labels.txt train_labels.txt COPYONLY)
configure_file(data/train_states.txt train_states.txt COPYONLY)

if((NOT ${EIGEN_INCLUDE_DIR}) OR (NOT EXISTS ${EIGEN_INCLUDE_DIR}))
    message("Installing Eigen library...")

    execute_process(COMMAND git submodule update --init -- third_party/eigen
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

    set(EIGEN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/eigen)  # CACHE PATH "Eigen library include directory"

else()
    message("Eigen library already present")
endif()

add_executable(naive_bayes src/main.cpp src/classifier.cpp src/classifier.h)
target_include_directories(naive_bayes PRIVATE ${EIGEN_INCLUDE_DIR})