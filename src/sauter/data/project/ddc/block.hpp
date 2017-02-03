/*
 * block.hpp
 *
 *  Created on: Sep 28, 2016
 *      Author: frieddan
 */

#ifndef SRC_SAUTER_PROJECT_DDC_BLOCK_HPP_
#define SRC_SAUTER_PROJECT_DDC_BLOCK_HPP_

#include <boost/fusion/include/adapt_struct.hpp>

#include <sauter/data/uuid.hpp>

namespace sauter { namespace data { namespace project { namespace ddc {


using values_t   = std::map<uint32_t, sauter::data::uuid>;
using coridnates = std::array<int32_t, 3>;
using dimentions = std::array<uint32_t, 2>;


struct block {
  /*

   {
     "id"         : "2843u40",
     "inputs"     : {
       "0" : "1239842",
       "1" : "1239821"
     },
     "outputs"    : {
       "0" : "123984ff",
     },
     "parameter"  : {},
     "marker"     : {},
     "function"   : "addition",
     "version"    :  1,
     "position"   : {1, 2, 3},
     "size"       : {10, 100}
   }
 */
  sauter::data::uuid  id;
  values_t      inputs;
  values_t      outputs;
  values_t      parameters;
  values_t      markers;
  std::string   function;
  uint32_t      version;
  coridnates    position;
  dimentions    size;
};


}}}}


BOOST_FUSION_ADAPT_STRUCT(
    sauter::data::project::ddc::block,
    id,
    inputs,
    outputs,
    parameters,
    markers,
    function,
    version,
    position,
    size
);


#endif /* SRC_SAUTER_PROJECT_DDC_BLOCK_HPP_ */
