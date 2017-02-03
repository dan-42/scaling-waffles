/*
 * serial_number.hpp
 *
 *  Created on: Sep 28, 2016
 *      Author: frieddan
 */

#ifndef SRC_SAUTER_SERIAL_NUMBER_HPP_
#define SRC_SAUTER_SERIAL_NUMBER_HPP_

#include <array>
#include <cstdint>

namespace sauter { namespace data {

using serial_number = std::array<uint8_t, 12>;

}}

#endif /* SRC_SAUTER_SERIAL_NUMBER_HPP_ */
