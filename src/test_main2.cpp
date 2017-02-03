/*
    Copyright 2013 Adobe Systems Incorporated
    Distributed under the MIT License (see license at
    http://stlab.adobe.com/licenses.html)

    This file is intended as example code and is not production quality.
*/

#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <mutex>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sodium/crypto_box.h>
#include <sodium/randombytes.h>
#include <sodium/utils.h>


using binary_t      = std::vector<uint8_t>;
using secret_key_t  = std::array<uint8_t, crypto_box_SECRETKEYBYTES>;
using public_key_t  = std::array<uint8_t, crypto_box_PUBLICKEYBYTES>;
using nonce_t       = std::array<uint8_t, crypto_box_NONCEBYTES>;

template<typename OStream, typename Buffer>
inline void print(OStream& os, const Buffer &data) {
    for(auto &c : data) {
      os << "" << std::setfill('0') << std::setw(2) << std::hex << (int)c;
    }
    os << std::dec;
}


struct node {

  node() {
    crypto_box_keypair(_public.data(),_secret.data());
    randombytes_buf(_nonce.data(), _nonce.size());
  }


  binary_t encrypt(const binary_t& msg, const public_key_t& pub) {

    static constexpr binary_t::size_type offset = crypto_box_ZEROBYTES;
    static constexpr binary_t::value_type empty = 0x00;

    binary_t msg_buf(offset, empty);


    for(const auto& b : msg) {
      msg_buf.push_back(b);
    }

    binary_t enc_msg(msg_buf.size(), 0x00);

    auto nonce  = next_nonce();

    auto success = crypto_box(enc_msg.data(), msg_buf.data(), msg_buf.size(), nonce.data(), pub.data(), _secret.data());
    if(success != 0) {
      std::cerr << "ERROR encrypt() " << success << "\n";
      throw;
    }
    return enc_msg;
  }


  binary_t decrypt(const binary_t& enc_msg, const public_key_t& pub, const nonce_t& n) {
    binary_t msg(enc_msg.size(), 0x00);

    for(auto idx = 0; idx < crypto_box_BOXZEROBYTES; ++idx) {
      assert(enc_msg[idx] == 0x00);
    }

    auto success = crypto_box(msg.data(), enc_msg.data(), enc_msg.size() ,n.data(), pub.data(),_secret.data());
    if(success != 0) {
      std::cerr << "ERROR decrypt() " << success << "\n";
      throw;
    }

    binary_t clear_msg(msg.begin() + crypto_box_ZEROBYTES , msg.end());

    return clear_msg;
  }


  const nonce_t& next_nonce() {
    sodium_increment(_nonce.data(), _nonce.size());
    return _nonce;
  }

  secret_key_t _secret{};
  public_key_t _public{};
  nonce_t      _nonce{};

};

void print(const node& n) {
  print(std::cout, n._public);
  std::cout << std::endl;
  print(std::cout, n._secret);
  std::cout << std::endl;
}


int main() {

  node bob{};
  node alice{};

  std::cout << "bob: " << std::endl ;
  print(bob);
  std::cout <<  std::endl ;


  std::cout << "alice: " << std::endl ;
  print(alice);
  std::cout <<  std::endl ;


  std::string message{"Hello World"};
  binary_t binary_msg{};

  for(const auto& c:message) {
    binary_msg.push_back(c);
  }
  std::cout << "msg: " ; print(std::cout, binary_msg); std::cout << std::endl;


  auto encrypted = bob.encrypt(binary_msg, alice._public);
  std::cout << "encrypted " ; print(std::cout, encrypted); std::cout << std::endl;


  auto clear = alice.decrypt(encrypted, bob._public, bob._nonce);
  std::cout << "msg: " ; print(std::cout, clear); std::cout << std::endl;


  return 0;


}
