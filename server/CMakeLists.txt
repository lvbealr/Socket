# Define the server project
project(Server)

# Add the executable for the server
add_executable(mksock server.cpp ../colorPrint/colorPrint.cpp)

# Include directories
target_include_directories(mksock PRIVATE ${CMAKE_SOURCE_DIR}/customWarning ${CMAKE_SOURCE_DIR}/colorPrint)

# Set compile options
SET(FLAGS "-D NDEBUG")
target_compile_options(mksock PRIVATE ${FLAGS})

# Link libraries if needed
# target_link_libraries(server <library_name>)