cmake_minimum_required(VERSION 2.8.7)

project(TwitterClient)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_system")
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)

option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)
option(BUILD_TESTS "Build tests for webdavclient" ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ tests/)
add_library(TwitterClient STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/client.cpp sources/base64.cpp tests/main.cpp)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
include_directories(${BOOST_INCLUDE_DIRS} /usr/local/libs/process)

if(UNIX)
    set(DEPENDS_LIBRARIES ${OPENSSL_LIBRARIES} ${CURL_LIBRARY})
elseif(MSVC)
    set(DEPENDS_LIBRARIES ${OPENSSL_LIBRARIES} ${CURL_LIBRARY} ws2_32)
endif()

add_executable(Examples ${CMAKE_CURRENT_SOURCE_DIR} examples/main.cpp)
target_link_libraries(Examples ${PROJECT_NAME} ${DEPENDS_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
add_executable(wc ${CMAKE_CURRENT_SOURCE_DIR} examples/wc.cpp)
target_link_libraries(wc ${PROJECT_NAME} ${DEPENDS_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})

if(BUILD_TESTS)
    enable_testing()
    file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
    add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
    target_link_libraries(check ${PROJECT_NAME} ${DEPENDS_LIBRARIES} ${Boost_LIBRARIES})
    add_test(NAME check COMMAND check "-s" "-r" "compact" "--use-colour" "yes")
endif()