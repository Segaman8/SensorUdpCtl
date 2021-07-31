#Set BINARY to the project name IndexProject
set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcmodel=large")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcmodel=large")

# scan project files
# exclude "export.cpp" from shared lib
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
#list(REMOVE_ITEM SOURCES "src/export.cpp")
list(FILTER SOURCES EXCLUDE REGEX ".*export.cpp")
set(SOURCES ${SOURCES})
#message(STATUS "${SOURCES}")

# In order to allow the code under src to be used as a static link library during unit testing

# shared lib & static lib
add_library(${BINARY}_static STATIC ${SOURCES})
add_library(${BINARY}_lib SHARED export.cpp)

# important flags
target_link_libraries(${BINARY}_static -fPIC -lpthread)
target_link_libraries(${BINARY}_lib PUBLIC ${CMAKE_PROJECT_NAME}_static -lpthread)

if (WIN32)
set_target_properties(${BINARY}_lib PROPERTIES LINK_FLAGS "-static")
target_link_libraries(${BINARY}_lib -lwsock32)
endif (WIN32)
