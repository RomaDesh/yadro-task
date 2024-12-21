п»їcmake_minimum_required(VERSION 3.8)

project(task)

# Р”РѕР±Р°РІР»РµРЅРёРµ РёСЃС…РѕРґРЅРёРєРѕРІ РѕСЃРЅРѕРІРЅРѕРіРѕ РїСЂРѕРµРєС‚Р°
add_executable(task "events.h" "globals.h" "desk.h" "time.h" "utils.h" "main.cpp" "time.cpp" "desk.cpp" "utils.cpp" "events.cpp")

# РџРѕРёСЃРє Рё РїРѕРґРєР»СЋС‡РµРЅРёРµ Google Test
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Р”РѕР±Р°РІР»РµРЅРёРµ РёСЃРїРѕР»РЅСЏРµРјРѕРіРѕ С„Р°Р№Р»Р° РґР»СЏ С‚РµСЃС‚РѕРІ
add_executable(task_tests "tests_source/test_main.cpp" "tests_source/tests.cpp" "events.h" "globals.h" "desk.h" "time.h" "utils.h" "time.cpp" "desk.cpp" "utils.cpp" "events.cpp")

target_compile_definitions(task_tests PRIVATE TESTRUN)

# Р›РёРЅРєРѕРІРєР° РёСЃРїРѕР»РЅСЏРµРјРѕРіРѕ С„Р°Р№Р»Р° С‚РµСЃС‚РѕРІ СЃ Р±РёР±Р»РёРѕС‚РµРєР°РјРё Google Test Рё pthread
if (WIN32) 
target_link_libraries(task_tests ${GTEST_LIBRARIES}) 
else () 
target_link_libraries(task_tests ${GTEST_LIBRARIES} pthread) 
endif()