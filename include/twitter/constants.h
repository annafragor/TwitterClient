//
// Created by anna on 26.10.16.
//

/*
для авторизации Desktop-приложения необходимо зарегистрировать ваше будущее приложение
в Twitter, это можно сделать на этой странице: twitter.com/oauth_clients,
вам буду выданы два ключа: oauth_consumer_key и oauth_consumer_secret.
Эти ключи следует запомнить и в дальнейшем вставить в ваше приложение как константы,
так как они с ним неотрывно связаны.

Процесс авторизации по шагам:
    С помощью некоего GET-запроса на адрес api.twitter.com/oauth/request_token
    мы должны получить первоначальное значение ключей oauth_token и oauth_secret

    С помощью некоего GET запроса мы должны открыть в браузере пользователя
    следующую страницу: api.twitter.com/oauth/authorize

    На этой странице у пользователя спросят его логин и пароль, если он не авторизован
    на сайте и спросят, действительно ли он желает разрешить данному приложению
    доступ в Twitter от имени его аккаунта

    После согласия пользователя ему будет показан PIN-код

    Наше приложение тем временем должно предложить пользователю диалог для ввода PIN-кода

    После того как пользователь скопирует из браузера PIN и вставит его в наше приложение,
    оно должно выполнить некий POST-запрос на адрес: api.twitter.com/oauth/access_token,
    это необходимо для получения настоящих ключей oauth_token и oauth_secret,
    которые в дальнейшем будут использоваться для идентификации пользователя в системе.
*/

#ifndef TWITTERCLIENT_CONSTANTS_H
#define TWITTERCLIENT_CONSTANTS_H

#include <string>

const std::string URL_SEPARATOR = "&";

const std::string CONSUMER_KEY =      "xNDZ06PUh5puXTsP6u9NNCWAZ";
const std::string CONSUMER_SECRET =   "vw4SjgZ150H0HC6536lj2IO8ktzyWhP52mLOSTFUCitqQNxd9I";

const std::string AUTHORIZE_URL =     "https://api.twitter.com/oauth/authorize";
const std::string REQUEST_TOKEN_URL = "https://api.twitter.com/oauth/request_token";
const std::string ACCESS_TOKEN_URL =  "https://api.twitter.com/oauth/access_token";

const std::string ACCOUNT_DATA_URL =  "https://api.twitter.com/1.1/users/show.json"; /*адрес API получения информации о пользователе*/

const std::string CALLBACK_URL =      "https://github.com/moskanka/TwitterClient"; /*адрес, куда пользователь
                                                                            будет перенаправлен после аутентификации*/


#endif //TWITTERCLIENT_CONSTANTS_H
