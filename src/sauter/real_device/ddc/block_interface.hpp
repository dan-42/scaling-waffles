/*
 * block.hpp
 *
 *  Created on: Sep 30, 2016
 *      Author: frieddan
 */

#ifndef SRC_SAUTER_REAL_DEVICE_DDC_BLOCK_HPP_
#define SRC_SAUTER_REAL_DEVICE_DDC_BLOCK_HPP_

#include <cstdint>
#include <sauter/real_device/ddc/item.hpp>

namespace sauter { namespace real_device { namespace ddc {

struct block_interface {

  virtual ~block_interface() { }
  virtual void     execute()                              = 0;
  virtual void     input (uint32_t position, item_ptr v)  = 0;
  virtual void     output(uint32_t position, item_ptr v)  = 0;
  virtual item_ptr input (uint32_t position)      const   = 0;
  virtual item_ptr output(uint32_t position)      const   = 0;
  virtual size_t number_of_inputs()               const   = 0;
  virtual size_t number_of_outputs()              const   = 0;
  virtual size_t number_of_parameters()           const   = 0;
  virtual size_t number_of_markers()              const   = 0;

};

typedef std::shared_ptr<block_interface> block_ptr;

inline block_ptr make(const std::string& name);

}}}


#endif /* SRC_SAUTER_REAL_DEVICE_DDC_BLOCK_HPP_ */
