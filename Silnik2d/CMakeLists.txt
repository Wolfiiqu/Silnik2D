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
            include/TransformableObject.h
            include/GameObject.h
            include/DrawableObject.h
            include/UpdatableObject.h
            src/Elipsa.cpp
            include/Elipsa.h
            src/Engine.cpp
            include/Engine.h
            src/BitmapHandler.cpp
            include/BitmapHandler.h
            include/AnimatedObject.h
            include/BitmapObject.h
            src/BItMapObject.cpp
            include/AnimatedObject.h
            demo/src/Player.cpp
            demo/include/Player.h
            demo/src/Bullet.cpp
            demo/include/Bullet.h
            demo/src/HomingBullet.cpp
            demo/include/HomingBullet.h
            demo/src/TrackerBullet.cpp
            demo/include/TrackerBullet.h
            demo/src/Bomb.cpp
            demo/include/Bomb.h
            demo/src/Spawner.cpp
            demo/include/Spawner.h
            demo/src/Game.cpp
            demo/include/Game.h
            demo/include/GameConfig.h
            demo/include/Board.h
            demo/src/Board.cpp
            demo/main.cpp
            demo/src/BoardObject.cpp
            demo/include/BoardObject.h
            demo/src/HudObject.cpp
            demo/include/HudObject.h
    )

    target_include_directories(Silnik2d PRIVATE include)

    target_link_libraries(Silnik2d PRIVATE sfml-graphics sfml-main)

    add_custom_command(TARGET Silnik2d POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/demo/assets
            $<TARGET_FILE_DIR:Silnik2d>/assets
    )

    if(WIN32)
        target_link_libraries(Silnik2d PRIVATE sfml-main)
        add_custom_command(TARGET Silnik2d POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                $<TARGET_FILE_DIR:sfml-graphics>
                $<TARGET_FILE_DIR:Silnik2d>
        )
    endif()