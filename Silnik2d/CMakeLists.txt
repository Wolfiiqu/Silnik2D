cmake_minimum_required(VERSION 4.1)
project(Silnik2d)

set(CMAKE_CXX_STANDARD 20)

add_executable(Silnik2d demo/main.cpp
        src/Point2D.cpp
        include/Point2D.h
        src/Transform2D.cpp
        include/Transform2D.h
        src/MathUtils.cpp
        include/MathUtils.h
        src/Color.cpp
        include/Color.h
        src/Renderer.cpp
        include/Renderer.h
        src/Shape.cpp
        include/Shape.h
        src/Rectangle.cpp
        include/Rectangle.h
        src/Circle.cpp
        include/Circle.h
        src/Line.cpp
        include/Line.h
        src/Triangle.cpp
        include/Triangle.h
        src/Polygon.cpp
        include/Polygon.h
        src/Bitmap.cpp
        include/Bitmap.h
        src/Animation.cpp
        include/Animation.h
        src/Sprite.cpp
        include/Sprite.h
        src/AnimatedSprite.cpp
        include/AnimatedSprite.h
        src/InputManager.cpp
        include/InputManager.h
)
