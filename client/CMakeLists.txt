# Define the client project
project(Client)

# Add the executable for the client
add_executable(client client.cpp ../colorPrint/colorPrint.cpp)

# Include directories
target_include_directories(client PRIVATE ${CMAKE_SOURCE_DIR}/customWarning ${CMAKE_SOURCE_DIR}/colorPrint)

# Set compile options
SET(FLAGS "-D NDEBUG")
target_compile_options(client PRIVATE ${FLAGS})

# Link libraries if needed