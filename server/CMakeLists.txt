project(Server)

add_executable(mksock server.cpp)

target_link_libraries(mksock PRIVATE customWarning)
target_compile_options(mksock PRIVATE ${FLAGS})