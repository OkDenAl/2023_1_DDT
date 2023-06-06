#ifndef SOURCEDOUT_SOLUTION_HPP
#define SOURCEDOUT_SOLUTION_HPP

#include <iostream>
#include <string>
#include <utility>

class Solution {
 public:
    struct Codes {
        std::string original;
        std::string current;
        Codes(const std::string &original, const std::string &current);
        Codes() = default;
    };

    Solution(size_t id, std::string sendDate, size_t senderId, std::string source, size_t taskId, std::string result,
             std::string tokens, std::string astTree, size_t orig_solution, std::string language) noexcept;

    Solution(std::string sendDate, size_t senderId, std::string source, size_t taskId, std::string result,
             std::string tokens, std::string astTree, size_t orig_solution, std::string language) noexcept;

    Solution() noexcept;

    [[nodiscard]] size_t getId() const noexcept;

    [[nodiscard]] const std::string &getSendDate() const noexcept;

    void setSendDate(const std::string &sendDate) noexcept;

    [[nodiscard]] size_t getSenderId() const noexcept;

    void setSenderId(size_t senderId) noexcept;

    [[nodiscard]] const std::string &getSource() const noexcept;

    void setSource(const std::string &source) noexcept;

    [[nodiscard]] const std::string &getTokens() const noexcept;

    void setTokens(const std::string &tokens) noexcept;

    [[nodiscard]] const std::string &getAstTree() const noexcept;

    void setAstTree(const std::string &astTree) noexcept;

    [[nodiscard]] size_t getTaskId() const noexcept;

    void setTaskId(size_t taskId) noexcept;

    [[nodiscard]] const std::string &getResult() const noexcept;

    void setResult(const std::string &result) noexcept;

    [[nodiscard]] size_t getOrigSolution() const;

    void setOrigSolution(size_t origSolution);

    [[nodiscard]] const std::string &getLanguage() const;

    void setLanguage(const std::string &language);

    void setId(size_t id) noexcept;

    bool operator==(const Solution &rhs) const noexcept;

    bool operator!=(const Solution &rhs) const noexcept;

 private:
    size_t id;
    std::string send_date;
    size_t sender_id;
    std::string source;
    std::string tokens;
    std::string astTree;
    size_t task_id;
    std::string result;
    size_t orig_solution = 0;
    std::string language;
};

#endif  // SOURCEDOUT_SOLUTION_HPP
