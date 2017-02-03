/*
 * device.hpp
 *
 *  Created on: Sep 28, 2016
 *      Author: frieddan
 */

#ifndef SRC_SAUTER_PROJECT_LIBRARY_DEVICE_HPP_
#define SRC_SAUTER_PROJECT_LIBRARY_DEVICE_HPP_

#include <boost/fusion/include/adapt_struct.hpp>

#include <sauter/data/uuid.hpp>
#include <sauter/data/serial_number.hpp>

namespace sauter { namespace data { namespace library { namespace hardware {

/**
 * a Hardware DEVICE  is the most comment part of different hardware
 * it can be a AS/IO/F-Module
 */

struct device {
  uuid          id;
  std::string   model;
  std::string   hardware_index;
  std::string   description;
};


struct device_firmware {
  uuid          id;
  uuid_list     supported_devices;
  std::string   version;
  uuid          signature_id;
  uuid          file_id;
};


struct device_configuration {
  uuid          id;
  uuid_list     supported_frmwares;
  std::string   description;
};







}}}}


#endif /* SRC_SAUTER_PROJECT_LIBRARY_DEVICE_HPP_ */
