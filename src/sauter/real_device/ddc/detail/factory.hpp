/*
 * block_factory.hpp
 *
 *  Created on: Sep 30, 2016
 *      Author: frieddan
 */

#ifndef SRC_SAUTER_REAL_DEVICE_DDC_DETAIL_BLOCK_FACTORY_HPP_
#define SRC_SAUTER_REAL_DEVICE_DDC_DETAIL_BLOCK_FACTORY_HPP_


#include <cstdint>
#include <sauter/real_device/ddc/block_interface.hpp>

namespace sauter { namespace real_device { namespace ddc { namespace detail {


template<typename T> block_ptr make_block() { return std::make_shared<T>(); }


struct factory {

  using map_type = std::map<std::string, block_ptr(*)()>;
  using map_type_ptr = std::shared_ptr<map_type>;

  static block_ptr make(std::string const& s) {
      map_type::iterator it = get_map()->find(s);
      if(it == get_map()->end())
          return 0;
      return it->second();
  }

protected:
  static map_type_ptr get_map() {
      static map_type_ptr map;
      if(map == nullptr) {
        map = std::make_shared<map_type>();
      }
      return map;
  }

};

}}}}

namespace sauter { namespace real_device { namespace ddc { namespace block {

template<typename T>
struct block_register :  sauter::real_device::ddc::detail::factory {
    block_register(std::string const& s) {
        get_map()->insert(std::make_pair(s, &sauter::real_device::ddc::detail::make_block<T>));
    }
};

}}}}

//must be included after the factory
#include <sauter/real_device/ddc/block/blocks.hpp>

namespace sauter { namespace real_device { namespace ddc {

block_ptr make(const std::string& name) {
  return detail::factory::make(name);
}

}}}

#endif /* SRC_SAUTER_REAL_DEVICE_DDC_DETAIL_BLOCK_FACTORY_HPP_ */
