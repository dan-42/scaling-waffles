/*
 * device.hpp
 *
 *  Created on: Sep 28, 2016
 *      Author: frieddan
 */

#ifndef SRC_SAUTER_PROJECT_HARDWARE_DEVICE_HPP_
#define SRC_SAUTER_PROJECT_HARDWARE_DEVICE_HPP_

#include <boost/fusion/include/adapt_struct.hpp>

#include <sauter/data/uuid.hpp>
#include <sauter/data/serial_number.hpp>

namespace sauter { namespace data { namespace project { namespace hardware {

/**
 * a DEVICE  is any kind of hardware that can have zero or many, fixed or dynamic number of IO
 * E.g. - IO-Module has a fixed number of IO but different config of thoses
 *      - KNX/DALI/SMI can have a dynamic number of connected devices
 */

struct device {
  uuid          id;
  uuid          device_id;
  uuid          firmware_id;
  //uuid          device_id;

  serial_number serial;
};




/*
 * a gate maps exactly to one...
 * this represents the generic configuration, a type specific is stored somewhere else
 *  ... push button
 *  ... Relay
 *  ... one sensor input
 *  ... one 0..10V output
 *  ... one KNX-group-address
 *  ... one DALI-address
 *  ... etc
 */
struct gate {
  enum class direction_e { input, output };

  uuid      id;
  uuid      device;
  uuid      type;
  uuid      gate_config;

  direction_e direction;

};


}}}}


#endif /* SRC_SAUTER_PROJECT_HARDWARE_DEVICE_HPP_ */
