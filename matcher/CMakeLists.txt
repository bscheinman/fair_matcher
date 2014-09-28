add_executable(matcher match_server.cpp matcher_engine.cpp orderbook.cpp server_session.cpp market_data_host.cpp market_data_session.cpp)
add_library(orderbook.o orderbook.cpp)

include_directories(../shared/trade_data ../shared/network)
link_directories(../shared/network ../shared/trade_data)
target_link_libraries(matcher network.o messages.o ${Boost_LIBRARIES})
target_link_libraries(orderbook.o messages.o ${Boost_LIBRARIES})

add_subdirectory(test)