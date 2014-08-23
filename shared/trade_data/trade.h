#ifndef TRADE_H_
#define TRADE_H_

#include <string>
#include <boost/flyweight.hpp>

class Trade {
public:
	std::string& getSymbol(void) { return symbol_.get(); }
	std::string& getUserId(void) { return userId_.get(); }
	unsigned int getQuantity(void) { return quantity_; }
	float getPrice(void) { return price_; }
private:
	boost::flyweight<std::string> symbol_;
	boost::flyweight<std::string> userId_;
	unsigned int quantity_;
	float price_;
};



#endif /* TRADE_H_ */
