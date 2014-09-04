#include "orderbook.h"
#include <iostream>

using namespace trading::data;
using namespace trading::matcher;
using namespace std;


int main(int argc, char **argv) {
	Orderbook orderbook;
	string input;
	price_t price;
	quantity_t quantity;
	string side;
	unsigned int order_count = 0;
	unsigned int window_count = 0;

	while (true) {
		cin >> input;

		if (input.compare("O") == 0) {
			order_ptr order(new Order);
			cin >> side;
			cin >> quantity;
			cin >> price;
			order->set_buy_or_sell(side.compare("B") == 0);
			order->set_quantity(quantity);
			order->set_quantity_remaining(quantity);
			order->set_price(price);
			ostringstream oss;
			oss << "order_" << order_count++;
			order->set_order_id(oss.str());
			oss.clear();
			orderbook.add_order(order);
		} else if (input.compare("M") == 0) {
			cout << "window " << window_count++ << ":" << endl;
			orderbook.match_orders([](shared_ptr<Trade> trade) {
				cout << trade->order_id() << " executed " << trade->quantity() << " shares at " << trade->price() << endl;
			});
		} else if (input.compare("E") == 0) {
			break;
		} else {
			cerr << "unrecognized command type " << input << endl;
		}
	}

	return 0;
}
