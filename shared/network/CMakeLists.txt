include_directories(../trade_data)

add_library(network.o STATIC network_session.cpp network_utils.cpp network_host.h)
