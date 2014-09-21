add_executable(client trade_client.cpp client_session.cpp)

target_include_directories(client PUBLIC ../shared/trade_data PUBLIC ../shared/network)
link_directories(../shared/network ../shared/trade_data)
target_link_libraries(client network_session.o network_utils.o messages.o ${Boost_LIBRARIES})
