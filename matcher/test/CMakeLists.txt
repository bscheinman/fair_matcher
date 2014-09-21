add_executable(orderbook_test orderbook_test.cpp)

target_include_directories(orderbook_test PUBLIC .. PUBLIC ../../shared/trade_data)
link_directories(.. ../../shared/trade_data)
target_link_libraries(orderbook_test messages.o orderbook.o ${Boost_LIBRARIES})