/*
 * item.hpp
 *
 *  Created on: Sep 30, 2016
 *      Author: frieddan
 */

#ifndef SRC_SAUTER_REAL_DEVICE_DDC_ITEM_HPP_
#define SRC_SAUTER_REAL_DEVICE_DDC_ITEM_HPP_

#include <cstdint>
#include <string>
#include <mapbox/variant.hpp>
#include <mapbox/variant_io.hpp>
#include <sauter/data/uuid.hpp>

namespace sauter { namespace real_device { namespace ddc {

using value_type = mapbox::util::variant<  bool,
                                      uint32_t,
                                      int32_t,
                                      float,
                                      double,
                                      std::string
                                      // date_time,
                                      //  duration
                                      >;

struct item {

  value_type          value;
  sauter::data::uuid  id;
  /*indicate if item is used as input on a block*/
  bool                is_input{false};
  /*indicate if item is used as output on a block*/
  bool                is_output{false};

};

typedef std::shared_ptr<item> item_ptr;

}}}


#endif /* SRC_SAUTER_REAL_DEVICE_DDC_ITEM_HPP_ */
