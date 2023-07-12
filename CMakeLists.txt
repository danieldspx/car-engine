FIND_PACKAGE(OpenGL)
cmake_minimum_required(VERSION 3.25)
project(canvas_clion)

set(CMAKE_CXX_STANDARD 11)

set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

add_executable(
        canvas_clion
        include/GL/freeglut.h
        include/GL/freeglut_ext.h
        include/GL/freeglut_std.h
        include/GL/glut.h
        src/main.cpp
        src/gl_canvas2d.cpp src/gl_canvas2d.h src/base/interfaces/IRender.h src/base/vectors/Vector2D.h src/base/interfaces/IMouse.h src/base/interfaces/IEntity.h src/SceneManager.h src/SceneManager.cpp src/base/interfaces/IKeyboard.h src/base/Utils.h src/entities/engine/2d/CarEngine2D.cpp src/entities/engine/2d/CarEngine2D.h src/entities/engine/3d/CarEngine3D.cpp src/entities/engine/3d/CarEngine3D.h src/entities/engine/3d/parts/Crank.cpp src/entities/engine/3d/parts/Crank.h src/entities/engine/3d/parts/Piston.h src/entities/engine/3d/parts/Piston.cpp src/base/vectors/Vector3D.h src/base/vectors/Matrix.h src/base/vectors/Vector4D.h)

target_link_libraries(canvas_clion ${OpenGlLinkers})