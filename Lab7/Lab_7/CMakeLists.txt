project(Lab7)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

#add_library(GUIMyFrame1.cpp GUI.cpp GUI.h GUIMyFrame1.h vecmat.h)



set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(${PROJECT_NAME} ${SRC_LIST} GUIMyFrame1.h GUIMyFrame1.cpp GUI.h GUI.cpp main.cpp)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})


