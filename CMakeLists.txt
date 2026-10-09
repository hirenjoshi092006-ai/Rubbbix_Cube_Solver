cmake_minimum_required(VERSION 3.20)
project(rubbix_cube_solver VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories for headers across modules
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Model
    ${CMAKE_CURRENT_SOURCE_DIR}/Solver
    ${CMAKE_CURRENT_SOURCE_DIR}/PatternDatabases
    ${CMAKE_CURRENT_SOURCE_DIR}/Scanner
)

set(SOURCE_FILES
    main.cpp

    # Model
    Model/RubbixCube.h
    Model/RubbixCube.cpp
    Model/RubbixCube3D.cpp
    Model/RubbixCube1D.cpp
    Model/RubbixCubeBitBoard.cpp
    Model/PatternData/PatternData.h

    # Solvers
    Solver/DfsSolver.h
    Solver/BfsSolver.h
    Solver/IdDfsSolver.h
    Solver/IdAstarSolver.h

    # Pattern Databases
    PatternDatabases/NibbleArray.h
    PatternDatabases/NibbleArray.cpp
    PatternDatabases/PatternDatabase.h
    PatternDatabases/PatternDatabase.cpp
    PatternDatabases/Permutation_Indexer.h
    PatternDatabases/CornerPatternDatabase.h
    PatternDatabases/CornerPatternDatabase.cpp
    PatternDatabases/CornerDbMaker.h
    PatternDatabases/CornerDbMaker.cpp
    PatternDatabases/math.h
    PatternDatabases/math.cpp
)

# Check for OpenCV
find_package(OpenCV QUIET)

if(OpenCV_FOUND)
    message(STATUS "OpenCV found (${OpenCV_VERSION}): Enabling camera scanner module.")
    list(APPEND SOURCE_FILES
        Scanner/CubeScanner.h
        Scanner/CubeScanner.cpp
    )
    include_directories(${OpenCV_INCLUDE_DIRS})
    add_executable(rubbix_cube_solver ${SOURCE_FILES})
    target_link_libraries(rubbix_cube_solver ${OpenCV_LIBS})
    target_compile_definitions(rubbix_cube_solver PRIVATE USE_SCANNER HAVE_OPENCV)
else()
    message(STATUS "OpenCV not found: Building solver without camera scanner.")
    add_executable(rubbix_cube_solver ${SOURCE_FILES})
endif()