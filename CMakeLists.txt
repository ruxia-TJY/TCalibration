cmake_minimum_required(VERSION 3.5)

project(TCalibration VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


# 定义开发模式选项
option(DEV_MODE "Enable development mode" ON)

# 创建全局接口库
add_library(project_options INTERFACE)

# 如果开启开发模式，添加宏定义
if(DEV_MODE)
    target_compile_definitions(project_options INTERFACE DEV_MODE)
endif()



# Qt自动处理
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)

# 添加子项目
add_subdirectory(app)


# 源文件
set(PROJECT_SOURCES
        main.cpp
        include/debug_log.h
)

include_directories(${PROJECT_SOURCE_DIR})


# 创建可执行文件
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TCalibration
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TCalibration APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TCalibration SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TCalibration
            ${PROJECT_SOURCES}
        )
    endif()
endif()

qt_add_resources(TCalibration app_res
        PREFIX "/config"
        FILES
            resources/config.yaml)

target_include_directories(TCalibration
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)

# 链接库
target_link_libraries(TCalibration PUBLIC ${OpenCV_LIBS})
target_link_libraries(TCalibration PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(TCalibration PRIVATE app_core)
target_link_libraries(TCalibration PRIVATE project_options)


set_target_properties(TCalibration PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TCalibration)
endif()
