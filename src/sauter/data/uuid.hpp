/*
 * uuid.hpp
 *
 *  Created on: Sep 28, 2016
 *      Author: frieddan
 */

#ifndef SRC_SAUTER_UUID_HPP_
#define SRC_SAUTER_UUID_HPP_

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <pre/bytes/utils.hpp>


namespace sauter { namespace data {

using uuid       = boost::uuids::uuid;
using uuid_list  = std::vector<uuid>;



inline uuid generate_uuid() {
  return  boost::uuids::uuid(boost::uuids::random_generator()());
}

}}

/*
namespace pre { namespace json { namespace traits {

  template<> struct transform<sauter::data::uuid> {
    static void to_json(nlohmann::json& json, const sauter::data::uuid& value) {
      json = pre::bytes::to_hexstring(value.data, value.size());
    }
  };

  template<> struct has_transform<sauter::data::uuid> : std::true_type {};

}}}
*/

inline std::string to_string(const sauter::data::uuid& id) {
  return pre::bytes::to_hexstring(id.data, id.size());
}

template<typename OStream>
OStream& operator<<(OStream& os, const sauter::data::uuid& id) {
  os << to_string(id);
  return os;
}


#endif /* SRC_SAUTER_UUID_HPP_ */
