add_executable(matcher match_server.cpp matcher_engine.cpp orderbook.cpp server_session.cpp)
add_library(orderbook.o orderbook.cpp)

include_directories(../shared/trade_data)
link_directories(../shared/network ../shared/trade_data)
target_link_libraries(matcher network_session.o network_utils.o messages.o ${Boost_LIBRARIES})
target_link_libraries(orderbook.o network_session.o network_utils.o messages.o ${Boost_LIBRARIES})

add_subdirectory(test)