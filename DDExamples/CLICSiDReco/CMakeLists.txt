cmake_minimum_required(VERSION 2.8.3 FATAL_ERROR)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include
                     ${CMAKE_SOURCE_DIR}/DDExamples/CLICSiD/include
                     ${CMAKE_SOURCE_DIR}/DDExamples/ILDExDet/include
                     ${CMAKE_SOURCE_DIR}/DDCore/include 
                     ${ROOT_INCLUDE_DIR})

file(GLOB sources src/*.cpp)
include(DD4hep_XML_setup)

add_executable(CLICSiDCalorimeterReco src/CLICSiDCalorimeterReco.cpp)
add_executable(TGeoTest src/TGeoTest.cpp)
#add_library(CLICSiDReco SHARED ${sources})
#target_link_libraries(CLICSiDReco DD4hepCore CLICSiD ${ROOT_LIBRARIES})
target_link_libraries(CLICSiDCalorimeterReco DD4hepCore CLICSiD ${ROOT_LIBRARIES})
target_link_libraries(TGeoTest DD4hepCore CLICSiD ${ROOT_LIBRARIES})
