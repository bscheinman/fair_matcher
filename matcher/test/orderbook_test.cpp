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
			orderbook.add_order(order);
		} else if (input.compare("M") == 0) {
			orderbook.match_orders([](shared_ptr<Trade> trade) {
				cout << "executed " << trade->quantity() << " shares at " << trade->price() << endl;
			});
		} else if (input.compare("E") == 0) {
			break;
		} else {
			cerr << "unrecognized command type " << input << endl;
		}
	}

	return 0;
}
