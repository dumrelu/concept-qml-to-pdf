cmake_minimum_required(VERSION 3.16)

project(concept-qml-to-pdf VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick PrintSupport REQUIRED)

qt_add_executable(appconcept-qml-to-pdf
    qmltopdfexporter.h qmltopdfexporter.cpp
    main.cpp
)

qt_add_qml_module(appconcept-qml-to-pdf
    URI concept_qml_to_pdf
    VERSION 1.0
    QML_FILES main.qml 
)

set_target_properties(appconcept-qml-to-pdf PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appconcept-qml-to-pdf
    PRIVATE Qt6::Quick Qt6::PrintSupport)

# NOT A GOOD IDEA, just using for proof of concept
target_link_libraries(appconcept-qml-to-pdf PRIVATE Qt6::QuickPrivate)

install(TARGETS appconcept-qml-to-pdf
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
