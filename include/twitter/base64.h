//
// Created by anna on 10.11.16.
//

#ifndef TWITTERCLIENT_BASE64_H
#define TWITTERCLIENT_BASE64_H

#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);

#endif //TWITTERCLIENT_BASE64_H
