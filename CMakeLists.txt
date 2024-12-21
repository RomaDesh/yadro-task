cmake_minimum_required(VERSION 3.8)

project(task)

# Добавление исходников основного проекта
add_executable(task "events.h" "globals.h" "desk.h" "time.h" "utils.h" "main.cpp" "time.cpp" "desk.cpp" "utils.cpp" "events.cpp")

# Поиск и подключение Google Test
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Добавление исполняемого файла для тестов
add_executable(task_tests "tests_source/test_main.cpp" "tests_source/tests.cpp" "events.h" "globals.h" "desk.h" "time.h" "utils.h" "time.cpp" "desk.cpp" "utils.cpp" "events.cpp")

target_compile_definitions(task_tests PRIVATE TESTRUN)

# Линковка исполняемого файла тестов с библиотеками Google Test и pthread
if (WIN32) 
target_link_libraries(task_tests ${GTEST_LIBRARIES}) 
else () 
target_link_libraries(task_tests ${GTEST_LIBRARIES} pthread) 
endif()