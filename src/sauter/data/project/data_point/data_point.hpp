/*
 * data_point.hpp
 *
 *  Created on: Sep 28, 2016
 *      Author: frieddan
 */

#ifndef SRC_SAUTER_PROJECT_DATA_POINT_DATA_POINT_HPP_
#define SRC_SAUTER_PROJECT_DATA_POINT_DATA_POINT_HPP_

#include <boost/fusion/include/adapt_struct.hpp>

namespace sauter { namespace data { namespace project { namespace data_point {


struct data_point {

  sauter::data::uuid id;
  sauter::data::uuid type; //static info from sauter::library::data::type

};


}}}}



#endif /* SRC_SAUTER_PROJECT_DATA_POINT_DATA_POINT_HPP_ */
