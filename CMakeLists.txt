# stop if cmake version below 3.3
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

# project name
project(IndieStudio)


# project version
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
string(STRIP ${PROJECT_SOURCE_DIR} SOURCES_PATH)


# location of additional cmake modules
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/CMake
)


# guard against in-source builds and bad build-type strings
include(safeguards)


# detect operating system
message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_definitions(-DSYSTEM_LINUX)
endif()
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_definitions(-DSYSTEM_DARWIN)
endif()
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-DSYSTEM_WINDOWS)
endif()


# detect host processor
message(STATUS "The host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")


# example how to set c++ compiler flags for GNU
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
    set(CMAKE_CXX_FLAGS         "-std=c++11 -pthread")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3 -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
elseif(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
    set(CMAKE_CXX_FLAGS         "-std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3 -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

IF (DEFINED AIDEBUG)
    add_definitions(-DAIDEBUG)
ENDIF()

# settings library dependencies
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    link_directories(${PROJECT_SOURCE_DIR}/lib/irrlicht-1.8.4/lib/Linux/)
    link_directories(${PROJECT_SOURCE_DIR}/lib/bullet3-2.83.7/lib/Linux/)
    link_directories(${PROJECT_SOURCE_DIR}/lib/socket.io-client-cpp/lib/LINUX/)
    link_directories(${PROJECT_SOURCE_DIR}/lib/irrKlang-64bit-1.5.0/lib/LINUX/)
endif()
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    link_directories(/usr/local/lib/)
    link_directories(${PROJECT_SOURCE_DIR}/lib/irrlicht-1.8.4/lib/OSX/)
    link_directories(${PROJECT_SOURCE_DIR}/lib/bullet3-2.83.7/lib/OSX/)
    link_directories(${PROJECT_SOURCE_DIR}/lib/irrKlang-64bit-1.5.0/lib/OSX/)
    link_directories(${PROJECT_SOURCE_DIR}/lib/socket.io-client-cpp/lib/OSX/)
endif()
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    link_directories(${PROJECT_SOURCE_DIR}/lib/irrlicht-1.8.4/lib/Win64-visualStudio/)
endif()


set(SRC_FILES
    ${PROJECT_SOURCE_DIR}/sources/main.cpp

    ${PROJECT_SOURCE_DIR}/sources/AGame.cpp
    ${PROJECT_SOURCE_DIR}/sources/IndieGame.cpp
    ${PROJECT_SOURCE_DIR}/sources/EventReceiver.cpp
    ${PROJECT_SOURCE_DIR}/sources/NetworkEventBridge.cpp

    ${PROJECT_SOURCE_DIR}/sources/Vector2.cpp
    ${PROJECT_SOURCE_DIR}/sources/Vector3.cpp

    ${PROJECT_SOURCE_DIR}/sources/AGameObject.cpp
    ${PROJECT_SOURCE_DIR}/sources/AModelObject.cpp
    ${PROJECT_SOURCE_DIR}/sources/APhysicObject.cpp

    ${PROJECT_SOURCE_DIR}/sources/AGameCamera.cpp
    ${PROJECT_SOURCE_DIR}/sources/BasicCamera.cpp
    ${PROJECT_SOURCE_DIR}/sources/GameCameraFPS.cpp

    ${PROJECT_SOURCE_DIR}/sources/Minimap.cpp
    ${PROJECT_SOURCE_DIR}/sources/GameCheckpoint.cpp
    ${PROJECT_SOURCE_DIR}/sources/RandomEvent.cpp

    ${PROJECT_SOURCE_DIR}/sources/Race.cpp
    ${PROJECT_SOURCE_DIR}/sources/Circuit.cpp

    ${PROJECT_SOURCE_DIR}/sources/SoundManager.cpp
    ${PROJECT_SOURCE_DIR}/sources/SizeS.cpp
    ${PROJECT_SOURCE_DIR}/sources/KeyboardManager.cpp

    ${PROJECT_SOURCE_DIR}/sources/BulletAnimator/CBulletPhysics.cpp
    ${PROJECT_SOURCE_DIR}/sources/BulletAnimator/CBulletPhysicsAnimator.cpp
    ${PROJECT_SOURCE_DIR}/sources/BulletAnimator/CBulletPhysicsUtils.cpp
    ${PROJECT_SOURCE_DIR}/sources/BulletAnimator/CDebugNode.cpp
    ${PROJECT_SOURCE_DIR}/sources/BulletAnimator/PhysicsCar.cpp
    ${PROJECT_SOURCE_DIR}/sources/BulletAnimator/PhysicsObject.cpp

    ${PROJECT_SOURCE_DIR}/sources/CarSystem/GroundMaterial.cpp
    ${PROJECT_SOURCE_DIR}/sources/CarSystem/Car.cpp
    ${PROJECT_SOURCE_DIR}/sources/CarSystem/AICar.cpp
    ${PROJECT_SOURCE_DIR}/sources/CarSystem/NetworkCar.cpp
    ${PROJECT_SOURCE_DIR}/sources/CarSystem/LearningCar.cpp
    ${PROJECT_SOURCE_DIR}/sources/CarSystem/loadCar.cpp
    ${PROJECT_SOURCE_DIR}/sources/CarSystem/carWatcher.cpp

    ${PROJECT_SOURCE_DIR}/sources/GUI/Settings.cpp
    ${PROJECT_SOURCE_DIR}/sources/GUI/Garage.cpp
    ${PROJECT_SOURCE_DIR}/sources/GUI/Menu.cpp
    ${PROJECT_SOURCE_DIR}/sources/GUI/Course.cpp
    ${PROJECT_SOURCE_DIR}/sources/GUI/Audio.cpp
    ${PROJECT_SOURCE_DIR}/sources/GUI/Keyboard.cpp
    ${PROJECT_SOURCE_DIR}/sources/GUI/Concessionnaire.cpp
    ${PROJECT_SOURCE_DIR}/sources/GUI/Graphic.cpp
    ${PROJECT_SOURCE_DIR}/sources/GUI/JoinServer.cpp
    ${PROJECT_SOURCE_DIR}/sources/GUI/Classement.cpp
    ${PROJECT_SOURCE_DIR}/sources/GUI/MainMenu.cpp

    ${PROJECT_SOURCE_DIR}/sources/NeuralNetwork/ANetworkData.cpp
    ${PROJECT_SOURCE_DIR}/sources/NeuralNetwork/Network.cpp
    ${PROJECT_SOURCE_DIR}/sources/NeuralNetwork/NetworkTrainer.cpp
    ${PROJECT_SOURCE_DIR}/sources/NeuralNetwork/Neuron.cpp
    ${PROJECT_SOURCE_DIR}/sources/NeuralNetwork/Genome.cpp
    ${PROJECT_SOURCE_DIR}/sources/NeuralNetwork/GeneticPool.cpp
    ${PROJECT_SOURCE_DIR}/sources/NeuralNetwork/GeneticTrainer.cpp

    ${PROJECT_SOURCE_DIR}/sources/Client/Client.cpp


)

# build executable
add_executable(IndieStudio ${SRC_FILES})


# settings library dependencies
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(${PROJECT_NAME}
        Irrlicht
        BulletSoftBody_gmake_x64_release
        BulletDynamics_gmake_x64_release
        BulletCollision_gmake_x64_release
        LinearMath_gmake_x64_release
        "-lm"
        GL
        GLU
        Xrandr
        Xext
        Xxf86vm
        X11
        sioclient
        boost_system
        IrrKlang
    )
endif()
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    target_link_libraries(${PROJECT_NAME}
        Irrlicht
        BulletSoftBody
        BulletDynamics
        BulletCollision
        LinearMath
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework IOKit"
        "-framework Carbon"
        sioclient
        boost_system
        irrklang
    )
endif()
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(${PROJECT_NAME}
        Irrlicht
    )
endif()


# location of header files
include_directories(
    /usr/local/include/
    ${PROJECT_BINARY_DIR}/includes
    ${PROJECT_SOURCE_DIR}/includes
    ${PROJECT_SOURCE_DIR}/includes/CarSystem
    ${PROJECT_SOURCE_DIR}/includes/BulletAnimator
    ${PROJECT_SOURCE_DIR}/includes/NeuralNetwork
    ${PROJECT_SOURCE_DIR}/includes/GUI/
    ${PROJECT_SOURCE_DIR}/includes/Client/
    ${PROJECT_SOURCE_DIR}/lib/irrlicht-1.8.4/include/
    ${PROJECT_SOURCE_DIR}/lib/bullet3-2.83.7/include/bullet/
    ${PROJECT_SOURCE_DIR}/lib/socket.io-client-cpp/include/
    ${PROJECT_SOURCE_DIR}/lib/irrKlang-64bit-1.5.0/include/
    ${PROJECT_SOURCE_DIR}/lib/socket.io-client-cpp/lib/rapidjson/include/rapidjson/
)


# configure header file
configure_file(
    ${PROJECT_SOURCE_DIR}/CMake/config.h.in
    ${PROJECT_BINARY_DIR}/includes/IndieStudioConfig.h
)

# install binary
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        SET(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})
    ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    install(
        TARGETS IndieStudio DESTINATION IndieStudio.app/Contents/MacOS
    )
    install(
        CODE "execute_process(COMMAND install_name_tool -change /usr/local/lib/libirrklang.dylib ${PROJECT_SOURCE_DIR}/lib/irrKlang-64bit-1.5.0/lib/OSX/libirrklang.dylib IndieStudio)"
    )
    install(
        CODE "execute_process(COMMAND install_name_tool -change /usr/local/lib/libirrklang.dylib ${PROJECT_SOURCE_DIR}/lib/irrKlang-64bit-1.5.0/lib/OSX/libirrklang.dylib IndieStudio.app/Contents/MacOS/IndieStudio)"
    )
    file(COPY ${PROJECT_SOURCE_DIR}/Assets DESTINATION IndieStudio.app/Contents/Assets)
    string(STRIP IndieStudio.app/Contents/ SOURCES_PATH)
endif()
