/*
 * value.hpp
 *
 *  Created on: Sep 28, 2016
 *      Author: frieddan
 */

#ifndef SRC_SAUTER_PROJECT_DDC_VALUE_HPP_
#define SRC_SAUTER_PROJECT_DDC_VALUE_HPP_

#include <boost/fusion/include/adapt_struct.hpp>

namespace sauter { namespace data { namespace project { namespace ddc {

struct value {
 /*
  {
    "id"   : "42893792",
    "type" : "real"
    "value": "3.14"
  }
 */
  enum class type_t {
    null,
    bool_,
    real,
    integer,
    unsigned_integer,
    string,
    date_time,
    duration
  };

  uuid        id;
  type_t      type;
  std::string value;
};

}}}}

BOOST_FUSION_ADAPT_STRUCT(
    sauter::data::project::ddc::value,

    id,
    type,
    value
);

#endif /* SRC_SAUTER_PROJECT_DDC_VALUE_HPP_ */
