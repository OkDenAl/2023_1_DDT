
#include "Solution.hpp"

#include <string>
#include <utility>

Solution::Codes::Codes(const std::string &original, const std::string &current)
    : original(original), current(current) {}

Solution::Solution(size_t id, std::string sendDate, size_t senderId, std::string source, size_t taskId,
                   std::string result, std::string tokens, std::string astTree, size_t orig_solution,
                   std::string language_) noexcept
    : id(id),
      send_date(std::move(sendDate)),
      sender_id(senderId),
      source(std::move(source)),
      tokens(std::move(tokens)),
      astTree(std::move(astTree)),
      task_id(taskId),
      result(std::move(result)),
      orig_solution(orig_solution),
      language(std::move(language_)) {}

Solution::Solution(std::string sendDate, size_t senderId, std::string source, size_t taskId, std::string result,
                   std::string tokens, std::string astTree, size_t orig_solution, std::string language_) noexcept
    : id(0),
      send_date(std::move(sendDate)),
      sender_id(senderId),
      source(std::move(source)),
      tokens(std::move(tokens)),
      astTree(std::move(astTree)),
      task_id(taskId),
      result(std::move(result)),
      orig_solution(orig_solution),
      language(std::move(language_)) {}

size_t Solution::getId() const noexcept { return id; }

void Solution::setId(size_t id_) noexcept { id = id_; }

const std::string &Solution::getSendDate() const noexcept { return send_date; }

void Solution::setSendDate(const std::string &sendDate) noexcept { send_date = sendDate; }

size_t Solution::getSenderId() const noexcept { return sender_id; }

void Solution::setSenderId(size_t senderId) noexcept { sender_id = senderId; }

const std::string &Solution::getSource() const noexcept { return source; }

void Solution::setSource(const std::string &source_) noexcept { Solution::source = source_; }

const std::string &Solution::getTokens() const noexcept { return tokens; }

void Solution::setTokens(const std::string &tokens_) noexcept { Solution::tokens = tokens_; }

const std::string &Solution::getAstTree() const noexcept { return astTree; }

void Solution::setAstTree(const std::string &astTree_) noexcept { Solution::astTree = astTree_; }

size_t Solution::getTaskId() const noexcept { return task_id; }

void Solution::setTaskId(size_t taskId) noexcept { task_id = taskId; }

const std::string &Solution::getResult() const noexcept { return result; }

void Solution::setResult(const std::string &result_) noexcept { Solution::result = result_; }

bool Solution::operator==(const Solution &rhs) const noexcept { return id == rhs.id; }

bool Solution::operator!=(const Solution &rhs) const noexcept { return !(rhs == *this); }

size_t Solution::getOrigSolution() const { return orig_solution; }

void Solution::setOrigSolution(size_t origSolution) { orig_solution = origSolution; }

Solution::Solution() noexcept : id(0), sender_id(0), task_id(0) {}

const std::string &Solution::getLanguage() const { return language; }

void Solution::setLanguage(const std::string &language_) { Solution::language = language_; }
