
#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <functional>
#include <thread>
#include <cassert>

namespace core {

struct value {

  value() : v(0.0) {

  }

  value(double d) : v(d) {

   }

  void set_id(size_t i) { id = i;}
  double v{0.0};
  size_t id{0};

};

typedef std::shared_ptr<value> value_ptr;

struct block {

  virtual ~block() { }
  virtual void set_input(uint32_t position, value_ptr v)  = 0;
  virtual void set_output(uint32_t position, value_ptr v) = 0;
  virtual void execute() = 0;

};

typedef std::shared_ptr<block> block_ptr;


template<typename Derived>
struct block_crtp : block {

  Derived* self()  {
    return static_cast<Derived*>(this);
  }

  void execute()  final {
    self()->execute_impl();
  }

  void set_input(uint32_t position, value_ptr v) final {
    self()->set_input_impl(position, v);
  }

  void set_output(uint32_t position, value_ptr v) final {
    self()->set_output_impl(position, v);
  }

};



struct addition : block_crtp<addition> {
  void execute_impl() {
    output->v = 0.0;
    for(auto &input : inputs) {
      output->v += input->v;
    }
  }


  void set_input_impl(uint32_t position, value_ptr v) {
    inputs.push_back(v);
  }

  void set_output_impl(uint32_t position, value_ptr v) {
    assert(position == 0);
    output  = v;
  }


  value_ptr output;
  std::vector<value_ptr> inputs;
  //std::vector<value_ptr> outputs;
  //std::vector<value_ptr> inputs;
};






struct plan {

  std::array<core::value_ptr, 300000> values;
  std::array<core::block_ptr, 100005> blocks;


  block_ptr insert_block(size_t id, block_ptr b) {
    blocks[id] = b;
    return b;
  }

  value_ptr insert_value(size_t id, value_ptr v) {
    values[id] = v;
    v->set_id(id);
    return v;
  }

  block_ptr get_block(size_t id) {
    return blocks[id];
  }

  value_ptr get_value(size_t id) {
    return values[id];
  }



  void connect_input(size_t block_id, size_t input_id, size_t value_id) {
    blocks[block_id]->set_input(input_id, values[value_id]);
  }

  void connect_output(size_t block_id, size_t input_id, size_t value_id) {
    blocks[block_id]->set_output(input_id, values[value_id]);
  }


  void execute() {
    for(size_t i = 0; i < blocks.size(); ++i) {
      if(blocks[i] != nullptr) {
        blocks[i]->execute();
      }
    }
  }


  void print_blocks() {
    for(size_t i = 0; i < blocks.size(); ++i) {
         if(blocks[i] != nullptr) {
           std::cout << "block["     << std::setw(7) << i << "] "
                   //  << " in[0, " << std::setw(6) << blocks[i]->inputs[0]->id  << "]="    << std::setw(7) << blocks[i]->inputs[0]->v
                   //  << " in[1, " << std::setw(6) << blocks[i]->inputs[0]->id  << "]="    << std::setw(7) << blocks[i]->inputs[0]->v
                   //  << " out[0," << std::setw(6) << blocks[i]->outputs[0]->id << "]="    << std::setw(7) << blocks[i]->outputs[0]->v

                     << std::endl;

         }
       }
  }
};




}// core





int main() {



  core::plan plan;


  //parsing and instantiating

  //first //create types

  core::block_ptr current_block;
  core::value_ptr current_value;

  plan.insert_block(0, std::make_shared<core::addition>());


  //  inputs
  plan.insert_value(0, std::make_shared<core::value>(1));
  plan.insert_value(1, std::make_shared<core::value>(1));

  plan.insert_value(2, std::make_shared<core::value>());


  plan.connect_input(0, 0, 0);
  plan.connect_input(0, 1, 1);
  plan.connect_output(0, 0, 2);


  uint32_t value_id = 2;
  uint32_t block_id = 1;
  std::cout << " start 2 " << std::endl;


  for(; block_id < 100000; ++block_id)  {

    plan.insert_block(block_id, std::make_shared<core::addition>());

    plan.connect_input(block_id, 0, value_id);


    //  inputs
    value_id++;
    plan.insert_value(value_id, std::make_shared<core::value>(1));
    plan.connect_input(block_id, 1, value_id);


    value_id++;
    plan.insert_value(value_id, std::make_shared<core::value>());

    plan.connect_output(block_id, 0, value_id);

  }
  std::cout << " start 3 " << std::endl;


  plan.insert_block(block_id, std::make_shared<core::addition>());

  plan.connect_input(block_id, 0, value_id);


  //  inputs
  value_id++;
  plan.insert_value(value_id, std::make_shared<core::value>(1));
  plan.connect_input(block_id, 1, value_id);



  // make loop
  plan.connect_output(block_id, 0, 0);





  std::cout << " start 4 " << std::endl;

  auto now = std::chrono::high_resolution_clock::now();


  for(uint i=0; i<1; i++) {
    plan.execute();
  }

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - now).count();
    std::cout << "took qs: " << diff << std::endl;


    //std::this_thread::sleep_for(std::chrono::seconds(2));

/*

    //changing the plan on the flight
    blocks[0] = std::make_shared<core::subtraction>();
    blocks[0]->set_input(0, values[0]);
    blocks[0]->set_input(1, values[1]);
    blocks[0]->set_output(0, values[2]);
    blocks[1] = std::make_shared<core::subtraction>();
    blocks[1]->set_input(0, values[2]);
    blocks[1]->set_input(1, values[3]);
    blocks[1]->set_output(0, values[5]);



    for(uint i=0; i<100000000; i++) {

          for(auto &block : blocks) {
            block.second->execute();
          }

        }
*/
  //plan.print_blocks();



  return 0;
}
