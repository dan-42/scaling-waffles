/*
 * addition.hpp
 *
 *  Created on: Sep 30, 2016
 *      Author: frieddan
 */

#ifndef SRC_SAUTER_REAL_DEVICE_DDC_DETAIL_ADDITION_HPP_
#define SRC_SAUTER_REAL_DEVICE_DDC_DETAIL_ADDITION_HPP_

#include <cstdint>
#include <sauter/real_device/ddc/detail/traits.hpp>
#include <sauter/real_device/ddc/detail/block_crtp.hpp>
#include <sauter/real_device/ddc/item.hpp>

namespace sauter { namespace real_device { namespace ddc { namespace block {

struct addition;

namespace traits {
  template<>  constexpr size_t number_of_inputs<addition>()     { return 2; }
  template<>  constexpr size_t number_of_outputs<addition>()    { return 1; }
}

struct addition : detail::block_crtp<addition> {

  void execute_impl() {
    if(outputs[0]) {
      outputs[0]->value = mapbox::util::apply_visitor(addition_impl<value_type>(), inputs[0]->value, inputs[1]->value);
    }
  }


private:
  template<typename Result>
  struct addition_impl {

    template <typename T1, typename T2>
    Result operator()(const T1& lhs, const T2& rhs) const  {
      return Result{};
    }

    template <typename T>
    Result operator()(const T& lhs, const T& rhs) const  {
      return lhs + rhs;
    }


/*
    template <typename T1, typename T2, typename T = typename std::enable_if<   std::is_arithmetic<T1>::value
                                                                        && std::is_arithmetic<T2>::value>::type>
    Result operator()(T1 lhs, T2 rhs) const  {
       return Result(lhs + rhs);
    }
*/

  };

};

//template<> block_register<addition> detail::block_crtp<addition>::reg("addition");

DDC_REGISTER_BLOCK(addition)


}}}}


#endif /* SRC_SAUTER_REAL_DEVICE_DDC_DETAIL_ADDITION_HPP_ */
