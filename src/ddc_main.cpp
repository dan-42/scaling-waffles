
#include <memory>
#include <vector>
#include <iostream>
#include <iomanip>
#include <functional>

//#include <pre/json/from_json.hpp>
//#include <pre/json/to_json.hpp>

#include <chrono>
#include <sauter/data/library/library.hpp>

#include <sauter/data/project/project.hpp>

#include <sauter/real_device/ddc/task.hpp>



// helper

inline sauter::real_device::ddc::value_type to_item_value_type(const std::string &value_string, sauter::data::project::ddc::value::type_t type) {
  using types = sauter::data::project::ddc::value::type_t;

  sauter::real_device::ddc::value_type value{};

  switch(type) {
  case types::real :
    value = std::stod(value_string);
    break;
  default:
    std::cout << "can not parse value_string " << value_string << std::endl;
    value = 0;
  }
  return value;
}





int main(int args, char **argc) {

  namespace hw_config = sauter::data::project::hardware;

  namespace ddc_config = sauter::data::project::ddc;
  namespace ddc_core   = sauter::real_device::ddc;













  ddc_core::item i;
  std::cout << "size of item " << sizeof(i) << std::endl;
  std::cout << "size of item value " << sizeof(i.value) << std::endl;
  std::cout << "size of item " << sizeof(ddc_core::item) << std::endl;
  std::cout << "size of string " << sizeof(std::string) << std::endl;
  std::cout << "size of bool " << sizeof(bool) << std::endl;
  std::cout << "size of uuid " << sizeof(sauter::data::uuid) << std::endl;
  std::cout << "size of item value_type " << sizeof(ddc_core::value_type) << std::endl << std::endl << std::endl;


  i.value = std::string{"HelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorld"};

  std::cout << "size of item " << sizeof(i) << std::endl;
  std::cout << "size of item value " << sizeof(i.value) << std::endl;
  std::cout << "size of item " << sizeof(ddc_core::item) << std::endl;
  std::cout << "size of string " << sizeof(std::string) << std::endl;
  std::cout << "size of bool " << sizeof(bool) << std::endl;
  std::cout << "size of uuid " << sizeof(sauter::data::uuid) << std::endl;
  std::cout << "size of item value_type " << sizeof(ddc_core::value_type) << std::endl;


  std::vector<ddc_config::block> database_blocks;
  std::vector<ddc_config::value> databse_values;

  /* CREATED WITH CASE OR WHATEVER */
  {
    ddc_config::value input_value_1;
    input_value_1.id    = sauter::data::generate_uuid();
    input_value_1.type  = ddc_config::value::type_t::real ;
    input_value_1.value = "2.0";

    ddc_config::value input_value_2;
    input_value_2.id    = sauter::data::generate_uuid();
    input_value_2.type  = ddc_config::value::type_t::real ;
    input_value_2.value = "2.0";

    ddc_config::value output_value_1;
    output_value_1.id    = sauter::data::generate_uuid();
    output_value_1.type  = ddc_config::value::type_t::real ;
    output_value_1.value = "1.0";

    ddc_config::block block_1;
    block_1.function    = "addition";
    block_1.id          = sauter::data::generate_uuid();
    block_1.position    = {3, 2, 1};
    block_1.size        = {50, 150};
    block_1.version     = 1;
    //current_block.inputs[0]   = input_value_1.id;
    block_1.inputs[0]   = output_value_1.id; //loop
    block_1.inputs[1]   = input_value_2.id;
    block_1.outputs[0]  = output_value_1.id;


    database_blocks.push_back(block_1);
    databse_values.push_back(input_value_1);
    databse_values.push_back(input_value_2);
    databse_values.push_back(output_value_1);

 //   std::cout << "blocks " << pre::json::to_json(database_blocks).dump(2) << std::endl;


  //  hw_config::gate temperature_gate;
  //  temperature_gate.direction = hw_config::gate::direction_e::input;


  }

  /* stored/ retrived from a DB */


  /* loading and executing the plan */

  ddc_core::task t;

  for(auto& config_value : databse_values) {
    auto item = std::make_shared<ddc_core::item>();
    item->id    = config_value.id;
    item->value = to_item_value_type(config_value.value, config_value.type);
    t.insert_value(config_value.id, item);
  }



  for(auto& config_block : database_blocks) {
    auto ddc_block = ddc_core::make(config_block.function);
    if(!ddc_block) {
      throw;
    }
    t.insert_block(config_block.id, ddc_block);


    for(auto& v : config_block.inputs) {
      t.connect_input(config_block.id, v.first, v.second);
    }

    for(auto& v : config_block.outputs) {
      t.connect_output(config_block.id, v.first, v.second);
    }
  }


  std::cout  << std::endl << "-----------BLOCKS----------------" << std::endl;
  t.print_blocks();
  std::cout << std::endl  << "-----------ITEMS-----------------" << std::endl;
  t.print_items();
  std::cout <<               "---------------------------------" << std::endl;


  std::chrono::high_resolution_clock::time_point start;
  std::chrono::high_resolution_clock::time_point end;

  for( int i = 0; i < 10; ++i) {
    start = std::chrono::high_resolution_clock::now();
    t.execute();
    end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "diff " << diff << std::endl;
  }



  std::cout  << std::endl << "-----------BLOCKS----------------" << std::endl;
  t.print_blocks();
  std::cout << std::endl  << "-----------ITEMS-----------------" << std::endl;
  t.print_items();
  std::cout <<               "---------------------------------" << std::endl;



  return 0;

}
