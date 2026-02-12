
set(APP_FILES
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        formsetting.cpp
        formsetting.h
        formsetting.ui
        configmanager.cpp
        configmanager.h
)

add_library(app_core STATIC ${APP_FILES})

target_link_libraries(app_core
        PRIVATE
        project_options
)


target_link_libraries(app_core
        PUBLIC
        Qt6::Core
        Qt6::Widgets
        ${OpenCV_LIBS}
        yaml-cpp
)

target_include_directories(app_core PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include
        ${OpenCV_INCLUDE_DIRS}
)

find_package(yaml-cpp REQUIRED)


