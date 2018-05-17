cmake_minimum_required(VERSION 3.8)
project(connectorTest)
#LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/res)

set(CMAKE_CXX_STANDARD 11)
#include_directories(/usr/local/include)
#link_directories(/usr/local/include)

set(SOURCE_FILES PatientQuery.h PatientQuery.cpp SpecializationQuery.h SpecializationQuery.cpp PositionQuery.h PositionQuery.cpp SpecialistQuery.h SpecialistQuery.cpp TimetableQuery.h TimetableQuery.cpp SessionQuery.h SessionQuery.cpp HistoryQuery.h HistoryQuery.cpp  SurveyQuery.h SurveyQuery.cpp dbQuery.h dbQuery.cpp clinic.cpp)
add_executable(connectorTest ${SOURCE_FILES})

find_library(CPPCMS_LIBRARY cppcms)

target_link_libraries(connectorTest mysqlcppconn)
target_link_libraries(connectorTest cppcms)
