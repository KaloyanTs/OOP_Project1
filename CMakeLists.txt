cmake_minimum_required(VERSION 3.0.0)
project(hotel VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(hotel main.cpp Hotel.cpp Date.cpp Room.cpp Reservation.cpp HotelBuilding.cpp RoomAnalyzer.cpp HotelInterface.cpp String.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
