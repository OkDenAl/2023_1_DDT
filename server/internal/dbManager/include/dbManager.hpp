#ifndef SOURCEDOUT_DBMANAGER_HPP
#define SOURCEDOUT_DBMANAGER_HPP

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <pqxx/pqxx>
#include <queue>
#include <stack>
#include <thread>
#include <vector>

class dbManager {
 public:
    dbManager();

    std::shared_ptr<pqxx::connection> connection();

    void freeConnection(const std::shared_ptr<pqxx::connection> &);

 private:
    const size_t POOL_SIZE = std::getenv("POOL_SIZE") ? std::stoul(std::getenv("POOL_SIZE")) : 10;
    std::condition_variable m_condition;

    void createPool();

    std::queue<std::shared_ptr<pqxx::connection>> connection_pool;
    std::mutex m_mutex;
};

#endif  // SOURCEDOUT_DBMANAGER_HPP
