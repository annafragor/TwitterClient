#include <twitter/client.h>
#include "catch.h"

SCENARIO("if right parameters are given => return true")
{
    GIVEN("client with right consumer_key and right consumer_secret")
    {
        Twitter::Client client;
        WHEN("checking connection")
        {
            THEN("connection was set")
            {
                REQUIRE(client.check_connection(CONSUMER_KEY, CONSUMER_SECRET));
            }
        }
    }
}
SCENARIO("if wrong consumer_key and wrong consumer_secret are given => return false")
{
    GIVEN("client with wrong consumer_key and wrong consumer_secret")
    {
        Twitter::Client client;
        WHEN("checking connection")
        {
            THEN("connection was set")
            {
                REQUIRE_FALSE(client.check_connection("smthing wrong", "another wrong string"));
            }
        }
    }
}
SCENARIO("if wrong consumer_key and right consumer_secret are given => return false")
{
    GIVEN("client with wrong consumer_key and right consumer_secret")
    {
        Twitter::Client client;
        WHEN("checking connection")
        {
            THEN("connection was set")
            {
                REQUIRE_FALSE(client.check_connection("smthing wrong", CONSUMER_SECRET));
            }
        }
    }
}
SCENARIO("if right consumer_key and wrong consumer_secret are given => return false")
{
    GIVEN("client with right consumer_key and wrong consumer_secret")
    {
        Twitter::Client client;
        WHEN("checking connection")
        {
            THEN("connection was set")
            {
                REQUIRE_FALSE(client.check_connection(CONSUMER_KEY, "another wrong string"));
            }
        }
    }
}