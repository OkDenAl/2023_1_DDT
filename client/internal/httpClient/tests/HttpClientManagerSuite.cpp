#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "HttpClientManager.h"
#include "IHttpClient.h"

class HttpClientMock : public IHttpClient {
 public:
    HttpClientMock() = default;
    MOCK_METHOD(ResponseStruct, makeGetRequest,
                (const Host& host, const std::string& target, const std::shared_ptr<Params>& params,
                 const std::shared_ptr<Params>& headers),
                (override));
    MOCK_METHOD(ResponseStruct, makePostRequest,
                (const Host& host, const std::string& target, const std::shared_ptr<Params>& body,
                 const std::shared_ptr<Params>& headers),
                (override));
    MOCK_METHOD(ResponseStruct, parseResponse, (Response response), (override));
    MOCK_METHOD(std::string, createURL, (const std::string& target, const std::shared_ptr<Params>& params), (override));
    MOCK_METHOD(bool, connect, (unsigned short port), (override));
    MOCK_METHOD(ResponseStruct, makeRequest,
                (const Host& host, const std::string& target, boost::beast::http::verb method,
                 const std::shared_ptr<Params>& params, const std::shared_ptr<Params>& body,
                 const std::shared_ptr<Params>& headers),
                (override));
};

class HttpClientManagerSuite : public ::testing::Test {
 protected:
    void SetUp() override { manager.setHttpClient(client); }

    std::shared_ptr<HttpClientMock> client = std::make_shared<HttpClientMock>();
    HttpClientManager manager = HttpClientManager("1", "1.1.1.1", 1, ".");
};

TEST_F(HttpClientManagerSuite, LoginUserTest) {
    EXPECT_CALL(*client, makeGetRequest);
    manager.loginUser("1", "2");
}

TEST_F(HttpClientManagerSuite, RegisterUserTest) {
    EXPECT_CALL(*client, makePostRequest);
    manager.registerUser("1", "2", "3");
}

TEST_F(HttpClientManagerSuite, SubmitSolutionTest) {
    EXPECT_CALL(*client, makePostRequest);
    manager.submitSolution(1, "2234");
}

TEST_F(HttpClientManagerSuite, GetAllSolutionsForTaskTest) {
    EXPECT_CALL(*client, makeGetRequest);
    manager.getAllSolutionsForTask(1, 2);
}

TEST_F(HttpClientManagerSuite, GetAllTasksTest) {
    EXPECT_CALL(*client, makeGetRequest);
    manager.getAllTasks();
}

TEST_F(HttpClientManagerSuite, GetMetricsTest) {
    EXPECT_CALL(*client, makeGetRequest);
    manager.getMetrics(1);
}
