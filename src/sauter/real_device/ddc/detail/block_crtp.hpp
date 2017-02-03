/*
 * block_crtp.hpp
 *
 *  Created on: Sep 30, 2016
 *      Author: frieddan
 */

#ifndef SRC_SAUTER_REAL_DEVICE_DDC_DETAIL_BLOCK_CRTP_HPP_
#define SRC_SAUTER_REAL_DEVICE_DDC_DETAIL_BLOCK_CRTP_HPP_

#include <cstdint>
#include <sauter/real_device/ddc/item.hpp>
#include <sauter/real_device/ddc/block_interface.hpp>
#include <sauter/real_device/ddc/detail/factory.hpp>
#include <sauter/real_device/ddc/detail/traits.hpp>


namespace sauter { namespace real_device { namespace ddc {  namespace detail {


namespace traits = sauter::real_device::ddc::block::traits;
namespace block  = sauter::real_device::ddc::block;

template<typename Derived,  size_t NumberInputs     = traits::number_of_inputs<Derived>(),
                            size_t NumberOutputs    = traits::number_of_outputs<Derived>(),
                            size_t NumberParameter  = traits::number_of_parameters<Derived>(),
                            size_t NumberMarkers    = traits::number_of_markers<Derived>()>
struct block_crtp : block_interface {

  Derived* self()  {
    return static_cast<Derived*>(this);
  }

  void execute()  final {
    self()->execute_impl();
  }



  void input(uint32_t position, item_ptr v) final {
    assert(position <  NumberInputs);
    inputs[position] = v;
    //outputs[position]->is_input = true;
  }

  void output(uint32_t position, item_ptr v) final {
    assert(position <  NumberOutputs);
    outputs[position]  = v;
    //outputs[position]->is_output = true;
  }


  item_ptr input(uint32_t position) const final {
    assert(position <  NumberInputs);
    return inputs[position];
  }

  item_ptr output(uint32_t position) const final {
    assert(position <  NumberOutputs);
    return outputs[position];
  }

  inline size_t number_of_inputs()      const final { return  NumberInputs; }
  inline size_t number_of_outputs()     const final { return  NumberOutputs; }
  inline size_t number_of_parameters()  const final { return  NumberParameter; }
  inline size_t number_of_markers()     const final { return  NumberMarkers; }


  bool only_inputs() {
    return false;
  }


//private:
  static block::block_register<Derived>  reg;
  std::array<item_ptr, NumberInputs>     inputs;
  std::array<item_ptr, NumberOutputs>    outputs;
  std::array<item_ptr, NumberParameter>  parameters;
  std::array<item_ptr, NumberMarkers>    markes;
};


}}}}

#define DDC_REGISTER_BLOCK(name)        \
    template<> block_register<name> detail::block_crtp<name>::reg(#name);


#endif /* SRC_SAUTER_REAL_DEVICE_DDC_DETAIL_BLOCK_CRTP_HPP_ */
