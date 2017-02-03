/*
 * task.hpp
 *
 *  Created on: Sep 28, 2016
 *      Author: frieddan
 */

#ifndef SRC_SAUTER_PROJECT_DDC_TASK_HPP_
#define SRC_SAUTER_PROJECT_DDC_TASK_HPP_

#include <boost/fusion/include/adapt_struct.hpp>

namespace sauter { namespace data { namespace project { namespace ddc {

struct task {
  sauter::data::uuid        id;
  std::string name;

  std::vector<sauter::data::uuid> blocks;
  std::vector<sauter::data::uuid> values;
  std::vector<sauter::data::uuid> parameters;
};

}}}}

BOOST_FUSION_ADAPT_STRUCT(
    sauter::data::project::ddc::task,
    id,
    name,
    blocks,
    values,
    parameters
);

#endif /* SRC_SAUTER_PROJECT_DDC_TASK_HPP_ */
