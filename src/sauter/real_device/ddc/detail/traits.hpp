/*
 * traits.hpp
 *
 *  Created on: Oct 9, 2016
 *      Author: dan
 */

#ifndef SRC_SAUTER_REAL_DEVICE_DDC_TRAITS_HPP_
#define SRC_SAUTER_REAL_DEVICE_DDC_TRAITS_HPP_

namespace sauter { namespace real_device { namespace ddc { namespace block { namespace traits {
  template<typename T>  constexpr size_t number_of_inputs()     { return 0; }
  template<typename T>  constexpr size_t number_of_outputs()    { return 0; }
  template<typename T>  constexpr size_t number_of_parameters() { return 0; }
  template<typename T>  constexpr size_t number_of_markers()    { return 0; }
}}}}}



#endif /* SRC_SAUTER_REAL_DEVICE_DDC_TRAITS_HPP_ */
