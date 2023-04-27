project(Lab8)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

add_compile_options(-lpthread -lX11)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})


add_executable(${PROJECT_NAME} ${SRC_LIST} GUIMyFrameMyFrame1.cpp FreeImage.h CImg.h GUIMyFrameMyFrame1.h MyVeryOwnClass.cpp MyVeryOwnClass.h Lab08.cpp Main.h)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} -lfreeimage /usr/lib/x86_64-linux-gnu/libwx_gtk2u_richtext-3.0.so -lX11)





