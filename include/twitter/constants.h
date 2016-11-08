//
// Created by anna on 26.10.16.
//

#ifndef TWITTERCLIENT_CONSTANTS_H
#define TWITTERCLIENT_CONSTANTS_H

#include <string>

const std::string URL_SEPARATOR = "&";

const std::string CONSUMER_KEY =      "xNDZ06PUh5puXTsP6u9NNCWAZ";
const std::string CONSUMER_SECRET =   "vw4SjgZ150H0HC6536lj2IO8ktzyWhP52mLOSTFUCitqQNxd9I";

const std::string AUTHORIZE_URL =     "https://api.twitter.com/oauth/authorize";
const std::string REQUEST_TOKEN_URL = "https://api.twitter.com/oauth/request_token";
const std::string ACCESS_TOKEN_URL =  "https://api.twitter.com/oauth/access_token";

const std::string FRIEND_LIST_URL =   "https://api.twitter.com/1.1/friends/list.json";

const std::string MY_ID =             "904268618";


const std::string ACCOUNT_DATA_URL =  "https://api.twitter.com/1.1/users/show.json"; /*адрес API получения информации о пользователе*/

#endif //TWITTERCLIENT_CONSTANTS_H
