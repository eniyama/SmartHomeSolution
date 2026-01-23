cmake_minimum_required(VERSION 3.16)

project(SmartHomeDashboard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 🔴 IMPORTANT: allow system Qt modules (Qt6Mqtt from qt6-connectivity-dev)
list(APPEND CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake")

find_package(Qt6 REQUIRED COMPONENTS
    Quick
    Qml
    Mqtt
    QuickControls2
)

qt_standard_project_setup()

qt_add_executable(SmartHomeDashboard
    cpp/main.cpp
    cpp/MqttManager.cpp
)

qt_add_qml_module(SmartHomeDashboard
    URI SmartHome
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/components/LeftPane.qml
        qml/components/MiddlePane.qml
        qml/components/RightPane.qml
        qml/components/RightPaneLightSwitchComponent.qml
        qml/components/Switch.qml
        qml/components/IconLabel.qml
        qml/components/CircularProgressBar.qml
        qml/components/Progressbar.qml
        qml/components/MiddlePaneWidget.qml
        SOURCES
        SOURCES cpp/MqttManager.h
        QML_FILES
        QML_FILES
        QML_FILES qml/components/KitchenPage.qml
        QML_FILES
        QML_FILES qml/components/Bedroom.qml
        QML_FILES qml/components/Laundry.qml

)

target_link_libraries(SmartHomeDashboard
    PRIVATE
        Qt6::Quick
        Qt6::Qml
        Qt6::Mqtt
        Qt6::QuickControls2
)
