
#include "dbManager.hpp"

dbManager::dbManager() { createPool(); }

void dbManager::createPool() {
    std::lock_guard<std::mutex> locker_(m_mutex);

    for (size_t i = 0; i < POOL_SIZE; i++) {
        connection_pool.emplace(std::make_shared<pqxx::connection>());
    }
}

std::shared_ptr<pqxx::connection> dbManager::connection() {
    std::unique_lock<std::mutex> lock_(m_mutex);

    while (connection_pool.empty()) {
        m_condition.wait(lock_);
    }

    auto conn_ = connection_pool.front();
    connection_pool.pop();

    return conn_;
}

void dbManager::freeConnection(const std::shared_ptr<pqxx::connection> &conn_) {
    std::unique_lock<std::mutex> lock_(m_mutex);

    connection_pool.push(conn_);

    lock_.unlock();

    m_condition.notify_one();
}
