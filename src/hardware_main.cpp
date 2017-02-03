
#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <functional>
#include <thread>
#include <cassert>


#include <sauter/data/uuid.hpp>


namespace sauter { namespace data { namespace library { namespace hardware {

  struct module {
    sauter::data::uuid  id;
    std::string         model_name;
    std::string         hardware_index;
    std::string         software_version;

  };






}}}}




namespace sauter { namespace data { namespace project { namespace hardware {

  struct type_t {
    uuid id;
    std::string name;
  };

  struct input_t {
    sauter::data::uuid  id;
    sauter::data::uuid  source_id;
    type_t              type;
    std::string         default_value;
  };

  struct output_t {
    sauter::data::uuid  id;
    std::vector<sauter::data::uuid>  target_ids;
    type_t              type;
    std::string         default_value;
  };

  struct module {
    sauter::data::uuid    id;
    sauter::data::uuid    library_id;
    sauter::data::uuid    configuration_id;
    std::vector<input_t>  inputs;
    std::vector<output_t> outputs;

  };


  struct configuration {
    sauter::data::uuid  id;
    sauter::data::uuid  module_id;
    std::string         data; //xxx serialized data for specific devices e.g. KNX etc...

  };

}}}}

namespace data {

  using values_t   = std::map<uint32_t, saiuuid>;
  using coridnates = std::array<int32_t, 3>;
  using dimentions = std::array<uint32_t, 2>;

  namespace bacnet {

    struct property {
      uint32_t property_id;
      uint32_t value;
    };

    struct object {
      uuid id;
      std::vector<property> propertys;
    };

  } //bacnet


  namespace hardware {

  struct part_t {
    uuid id;

  };




  struct terminal {
    uuid id;
    type_t type;
    direction_t direction;
    values_t value;
    uuid part;
  };

  }
}


int main(int args, char **argc) {




  return 0;

}
