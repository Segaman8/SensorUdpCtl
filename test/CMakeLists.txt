#Set BINARY to the project name IndexProject
set(BINARY ${CMAKE_PROJECT_NAME}_test)

# scan project files
file(GLOB_RECURSE TEST_SOURCES TEST_SOURCES false *.h *.cpp)
set(SOURCES ${TEST_SOURCES})
message(STATUS "${TEST_SOURCES}")

# include google test directory
include_directories(${GTestIncludes})

# In order to allow the code under src to be used as a static link library during unit testing

# shared lib & static lib
add_executable(${BINARY} ${TEST_SOURCES} ${GTestFiles})
add_test(NAME ${BINARY} COMMAND ${BINARY})

# important flags
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_static -lpthread)

if (WIN32)
set_target_properties(${BINARY} PROPERTIES LINK_FLAGS "-static")
target_link_libraries(${BINARY} -lwsock32)
endif (WIN32)
