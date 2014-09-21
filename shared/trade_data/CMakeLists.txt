find_package(Protobuf REQUIRED)

file(GLOB proto_files "proto/*.proto")
PROTOBUF_GENERATE_CPP(proto_src proto_hdr ${proto_files})

file(GLOB data_classes "*.cc" "*.cpp")
add_library(messages.o STATIC ${data_classes})
target_link_libraries(messages.o ${PROTOBUF_LIBRARIES})
