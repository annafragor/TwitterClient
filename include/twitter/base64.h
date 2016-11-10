//
// Created by anna on 10.11.16.
//

#ifndef TWITTERCLIENT_BASE64_H
#define TWITTERCLIENT_BASE64_H

/*#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);*/

#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/algorithm/string.hpp>

std::string decode64(const std::string&);

std::string encode64(const std::string&);


#endif //TWITTERCLIENT_BASE64_H
