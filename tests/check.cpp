#include <twitter/client.h>
#include "catch.h"

SCENARIO("if right parameters are given => return true")
{
    GIVEN("client with right consumer_key and right consumer_secret")
    {
        std::map<const std::string, const std::string> data;
        data.insert(std::pair<const std::string, const std::string>("consumer key", CONSUMER_KEY));
        data.insert(std::pair<const std::string, const std::string>("consumer secret", CONSUMER_SECRET));

        Twitter::Client client(data);
        WHEN("checking connection")
        {
            THEN("connection was set")
            {
                REQUIRE(client.check_connection());
            }
        }
    }
}
SCENARIO("if wrong consumer_key and wrong consumer_secret are given => return false")
{
    GIVEN("client with wrong consumer_key and wrong consumer_secret")
    {
        std::map<const std::string, const std::string> data;
        data.insert(std::pair<const std::string, const std::string>("consumer key", "something wrong"));
        data.insert(std::pair<const std::string, const std::string>("consumer secret", "another wrong string"));

        Twitter::Client client(data);
        WHEN("checking connection")
        {
            THEN("connection was set")
            {
                REQUIRE_FALSE(client.check_connection());
            }
        }
    }
}
SCENARIO("if wrong consumer_key and right consumer_secret are given => return false")
{
    GIVEN("client with wrong consumer_key and right consumer_secret")
    {
        std::map<const std::string, const std::string> data;
        data.insert(std::pair<const std::string, const std::string>("consumer key", "wrong string"));
        data.insert(std::pair<const std::string, const std::string>("consumer secret", CONSUMER_SECRET));

        Twitter::Client client(data);
        WHEN("checking connection")
        {
            THEN("connection was set")
            {
                REQUIRE_FALSE(client.check_connection());
            }
        }
    }
}
SCENARIO("if right consumer_key and wrong consumer_secret are given => return false")
{
    GIVEN("client with right consumer_key and wrong consumer_secret")
    {
        std::map<const std::string, const std::string> data;
        data.insert(std::pair<const std::string, const std::string>("consumer key", CONSUMER_KEY));
        data.insert(std::pair<const std::string, const std::string>("consumer secret", "wrong secret"));

        Twitter::Client client(data);
        WHEN("checking connection")
        {
            THEN("connection was set")
            {
                REQUIRE_FALSE(client.check_connection());
            }
        }
    }
}
SCENARIO("if wrong map is given => return false")
{
    GIVEN("client with wrong keys in map")
    {
        std::map<const std::string, const std::string> data;
        data.insert(std::pair<const std::string, const std::string>("cnsmr key", CONSUMER_KEY));
        data.insert(std::pair<const std::string, const std::string>("consumer scrt", "wrong secret"));

        Twitter::Client client(data);
        WHEN("checking connection")
        {
            THEN("connection was set")
            {
                REQUIRE_FALSE(client.check_connection());
            }
        }
    }
}