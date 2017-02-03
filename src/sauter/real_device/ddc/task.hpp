/*
 * task.hpp
 *
 *  Created on: Sep 30, 2016
 *      Author: frieddan
 */

#ifndef SRC_SAUTER_REAL_DEVICE_DDC_TASK_HPP_
#define SRC_SAUTER_REAL_DEVICE_DDC_TASK_HPP_

#include <cstdint>
#include <sauter/data/uuid.hpp>
#include <sauter/real_device/ddc/block_interface.hpp>
#include <sauter/real_device/ddc/item.hpp>
#include <sauter/real_device/ddc/block/blocks.hpp>


namespace sauter { namespace real_device { namespace ddc {

struct task {

  using items_type          = std::map<sauter::data::uuid, item_ptr>;
  using blocks_type         = std::map<sauter::data::uuid, block_ptr>;
  using execute_order_type  = std::list<block_ptr>;

  items_type items;
  blocks_type blocks;
  execute_order_type execute_order;


  block_ptr insert_block(sauter::data::uuid id, block_ptr b) {
    blocks[id] = b;
    return b;
  }

  item_ptr insert_value(sauter::data::uuid id, item_ptr v) {
    items[id] = v;
    v->id = id;
    return v;
  }

  block_ptr get_block(sauter::data::uuid id) {
    return blocks[id];
  }

  item_ptr get_value(sauter::data::uuid id) {
    return items[id];
  }



  void connect_input(sauter::data::uuid block_id, uint32_t input_id, sauter::data::uuid value_id) {
    if(items.find(value_id) == items.end() || items[value_id] == nullptr) {
      throw std::runtime_error("connect_input() no such value_id: " + to_string(value_id));
    }
    blocks[block_id]->input(input_id, items[value_id]);
    items[value_id]->is_input = true;
  }

  void connect_output(sauter::data::uuid block_id, uint32_t input_id, sauter::data::uuid value_id) {
    if(items.find(value_id) == items.end() || items[value_id] == nullptr) {
      throw std::runtime_error("connect_output() no such value_id: " + to_string(value_id));
    }
    blocks[block_id]->output(input_id, items[value_id]);
    items[value_id]->is_output = true;
  }


  void optimize_execution_order() {
   //std::vector

    for(auto &i : items) {
          if(i.second)
            std::cout << "block["  << i.first << "] = " << i.second->value << std::endl;;
        }
  }


  void execute() {
    for(auto& block : blocks) {
      if(block.second != nullptr) {
        block.second->execute();
      }
    }
  }




  void print_blocks() {
    for(auto &pair_block : blocks) {
        auto block = pair_block.second;
        std::cout << "block["  << pair_block.first << "] " << std::endl;
    }
  }

  void print_items() {
    for(auto &i : items) {
      if(i.second) {
        std::cout << "block["  << i.first << "] = " << i.second->value << std::endl;
      }
    }
  }

};

}}}


#endif /* SRC_SAUTER_REAL_DEVICE_DDC_TASK_HPP_ */
