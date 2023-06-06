#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "HttpClient.h"

TEST(HttpClientSuite, WrongGetTest) {
    HttpClient client;
    Host h("1", "1.1.1.1", 80);
    ResponseStruct res = client.makeGetRequest(h, "/ser/login");
    EXPECT_EQ(res.status, 500);
}
