    cmake_minimum_required(VERSION 4.1)
    project(Silnik2d)

    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.1
            GIT_SHALLOW ON
            EXCLUDE_FROM_ALL
    )
    FetchContent_MakeAvailable(SFML)

    file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
    file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.h")

    add_executable(Silnik2d ${SOURCES} ${HEADERS}
            src/main.cpp
            include/main.h
            src/TransformObject.cpp
            include/TransformObject.h
            src/GameObject.cpp
            include/GameObject.h
            src/DrawableObject.cpp
            include/DrawableObject.h
            include/UpdateObject.h
            src/Elipsa.cpp
            include/Elipsa.h
            src/Engine.cpp
            include/Engine.h
            src/BitmapHandler.cpp
            include/BitmapHandler.h
            include/AnimatedObject.cpp
            include/AnimatedObject.h
            include/BitmapObject.h
            include/BItMapObject.cpp
            src/Player.cpp
            include/Player.h)

    target_include_directories(Silnik2d PRIVATE include)

    target_link_libraries(Silnik2d PRIVATE sfml-graphics sfml-main)

    if(WIN32)
        target_link_libraries(Silnik2d PRIVATE sfml-main)
        add_custom_command(TARGET Silnik2d POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                $<TARGET_FILE_DIR:sfml-graphics>
                $<TARGET_FILE_DIR:Silnik2d>
        )
    endif()