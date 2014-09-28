#ifndef DATA_TYPES_H_
#define DATA_TYPES_H_

#include <string>
#include <boost/flyweight.hpp>

namespace trading {
namespace data {

typedef boost::flyweight<std::string> user_id_t;
typedef boost::flyweight<std::string> symbol_t;
typedef float price_t;
typedef unsigned long quantity_t;

}
}

#endif /* DATA_TYPES_H_ */
