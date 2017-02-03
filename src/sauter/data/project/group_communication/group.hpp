/*
 * group.hpp
 *
 *  Created on: Sep 28, 2016
 *      Author: frieddan
 */

#ifndef SRC_SAUTER_PROJECT_GROUP_COMMUNICATION_GROUP_HPP_
#define SRC_SAUTER_PROJECT_GROUP_COMMUNICATION_GROUP_HPP_

#include <boost/fusion/include/adapt_struct.hpp>

namespace sauter { namespace data { namespace project { namespace group_communication {

struct group {
  /*
   {
     "id"     : "bd9b8dc7-49d7-4ea0-a9e5-17a28c7afde0",
     "master" : "",
     "values" : {
        "9d6b05eb-a96e-4274-a39b-8cca57d0f7da",
        "96fbe8c2-067a-4783-978d-cc98cb5abf73",
        "17a93821-84f0-40e1-9373-ac2f6de35602",
        "4fd9012c-9a77-49f8-aef9-26d9efed961b",
        "0ee22ed3-f029-447d-bdb7-ad51a0b30592",
        "cd4750ac-be46-49f5-b371-79e54727c1cc",
        "f3b8399a-bc64-4122-8d8f-d3892d082a14",
        "da26cf2d-1728-40d5-9a94-571803eba9de",
        "a6fce1fe-b96f-4b95-8770-a9098174683b"
     },
     "mode" : "average"
   }
   */

  enum class mode_t {
    master_slave,
    average,
    last_wins,
    minimum,
    maximum
  };

  uuid id;
  uuid master;
  std::vector<uuid> values;
  mode_t mode;
};

}}}}


#endif /* SRC_SAUTER_PROJECT_GROUP_COMMUNICATION_GROUP_HPP_ */
