CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(yoloXArmor)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE RELEASE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPATH=\"\\\"${PROJECT_SOURCE_DIR}\\\"\"")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D${CMAKE_SYSTEM_NAME}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
SET(CMAKE_PREFIX_PATH /opt/intel/openvino_2021/deployment_tools/inference_engine/share) # 设置 OpenVino路径(以实际安装路径为准)
SET(BIN_NAME "run")

add_definitions(-D _GLIBCXX_USE_CXX11_ABI=1)
add_compile_definitions(PROJECT_DIR="${PROJECT_SOURCE_DIR}")

FIND_PACKAGE(InferenceEngine REQUIRED)
FIND_PACKAGE(Eigen3 REQUIRED)
FIND_PACKAGE(OpenCV 4 REQUIRED)
FIND_PACKAGE(Threads)

INCLUDE_DIRECTORIES(${InferenceEngine_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${FFTW3_INCLUDE_DIR})

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/detector)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/general)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/detector/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/general/include)

FILE(GLOB_RECURSE sourcefiles "detector/src/*.cpp" "general/src/*.cpp")
ADD_EXECUTABLE(${BIN_NAME} main.cpp ${sourcefiles} )

TARGET_LINK_LIBRARIES(${BIN_NAME} ${CMAKE_THREAD_LIBS_INIT}
                                  ${OpenCV_LIBS}
                                  ${Eigen3_LIBRARIES}
                                  ${InferenceEngine_LIBRARIES}
                                  )