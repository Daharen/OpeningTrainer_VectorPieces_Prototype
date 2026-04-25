cmake_minimum_required(VERSION 3.16)

project(OpeningTrainerVectorPiecesPrototype
    VERSION 0.1.0
    DESCRIPTION "Qt prototype for procedural vector chess piece previews"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 QUIET COMPONENTS Widgets)
if (NOT Qt6_FOUND)
    message(FATAL_ERROR
        "Qt6 Widgets was not found. Install Qt 6 with the Widgets module and set CMAKE_PREFIX_PATH to your Qt installation."
    )
endif()

add_executable(OpeningTrainerVectorPiecesPrototype
    src/main.cpp
    src/PieceTypes.h
    src/PieceRenderer.h
    src/PieceRenderer.cpp
    src/PiecePixmapCache.h
    src/PiecePixmapCache.cpp
    src/PreviewWindow.h
    src/PreviewWindow.cpp
)

target_link_libraries(OpeningTrainerVectorPiecesPrototype PRIVATE Qt6::Widgets)

target_compile_definitions(OpeningTrainerVectorPiecesPrototype PRIVATE
    QT_NO_KEYWORDS
)
