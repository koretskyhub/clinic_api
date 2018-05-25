cmake_minimum_required(VERSION 3.8)
project(clinicAPI)
set(CMAKE_CXX_STANDARD 11)
set(
        SOURCE_FILES
        PatientQuery.h PatientQuery.cpp SpecializationQuery.h SpecializationQuery.cpp
        PositionQuery.h PositionQuery.cpp SpecialistQuery.h SpecialistQuery.cpp
        TimetableQuery.h TimetableQuery.cpp SessionQuery.h SessionQuery.cpp
        HistoryQuery.h HistoryQuery.cpp SurveyQuery.h SurveyQuery.cpp
        dbQuery.h dbQuery.cpp clinic.h clinic.cpp
        main.cpp
)
add_executable(clinicAPI ${SOURCE_FILES})
find_library(CPPCMS_LIBRARY cppcms)
target_link_libraries(clinicAPI mysqlcppconn)
target_link_libraries(clinicAPI cppcms)
