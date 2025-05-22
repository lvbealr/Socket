project(Client)

add_executable(client client.cpp)

target_link_libraries(client PRIVATE customWarning)
target_compile_options(client PRIVATE ${FLAGS})