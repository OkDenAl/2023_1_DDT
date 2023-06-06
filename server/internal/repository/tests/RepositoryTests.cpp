#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <optional>

#include "MetricRepository.hpp"
#include "SolutionRepository.hpp"
#include "TaskRepository.hpp"
#include "UserRepository.hpp"

TEST(UserRepository_CRUD_Test, CRUD) {
    UserRepository rep;

    EXPECT_NO_FATAL_FAILURE(rep.getUserById(1));

    User user("test@test.com", "test", "testuser");
    size_t id = rep.makeUser(user);
    user.setId(id);
    std::optional<User> new_user_opt = rep.getUserById(id);
    User new_user;
    if (new_user_opt) {
        new_user = new_user_opt.value();
    }

    EXPECT_EQ(user, new_user);

    new_user.setUsername("new_test_user");

    EXPECT_NO_FATAL_FAILURE(rep.update(new_user));
    EXPECT_NO_FATAL_FAILURE(rep.deleteUser(new_user));
}

TEST(TaskRepository_CRUD_Test, CRUD) {
    TaskRepository rep;

    Task task("test task", 0.5, "name");
    size_t id = rep.storeTask(task);

    EXPECT_NO_FATAL_FAILURE(rep.getTaskById(1));

    task.setId(id);
    std::optional<Task> new_task_opt = rep.getTaskById(id);
    Task new_task;
    if (new_task_opt) new_task = new_task_opt.value();

    EXPECT_EQ(task, new_task);

    new_task.setDescription("new_test_description");

    EXPECT_NO_FATAL_FAILURE(rep.updateTask(new_task));
    EXPECT_NO_FATAL_FAILURE(rep.deleteTask(new_task));
}

TEST(SolutionRepository_CRUD_Test, CRUD) {
    SolutionRepository rep;

    Solution solution("01.01.1970", 1, ":/C/Users", 1, "result", "tokens.txt", "tree.txt", 1, "py");
    size_t id = rep.storeSolution(solution);

    EXPECT_NO_FATAL_FAILURE(rep.getSolutionById(id));

    solution.setId(id);
    std::optional<Solution> new_solution_opt = rep.getSolutionById(id);
    Solution new_solution;
    if (new_solution_opt) new_solution = new_solution_opt.value();

    EXPECT_EQ(solution, new_solution);

    new_solution.setSource(":/D");

    EXPECT_NO_FATAL_FAILURE(rep.updateSolution(new_solution));
    EXPECT_NO_FATAL_FAILURE(rep.deleteSolution(new_solution));
}

TEST(MetricRepository_CRUD_Test, CRUD) {
    MetricRepository rep;
    MetricStat metricStat(1, 0.8f, 0.9f, 0.89f, true, 0.85f);
    size_t id = rep.storeMetric(metricStat);

    EXPECT_NO_FATAL_FAILURE(rep.getById(1));

    metricStat.setId(id);
    std::optional<MetricStat> new_stat_opt = rep.getById(id);
    MetricStat new_stat;
    if (new_stat_opt) new_stat = new_stat_opt.value();
    EXPECT_EQ(metricStat, new_stat);
    new_stat.setMeanRes(1);

    EXPECT_NO_FATAL_FAILURE(rep.updateMetric(new_stat));
    EXPECT_NO_FATAL_FAILURE(rep.deleteMetric(new_stat));
}

TEST(UserRepository_CRUD_Test, getAllUsers) {
    UserRepository rep;
    std::vector<User> v = {{"test@test.com", "test", "testuser"}, {"test2@test.com", "test2", "testuser2"}};
    EXPECT_NO_FATAL_FAILURE(rep.getAllUsers());
    std::vector<User> new_v = rep.getAllUsers();
    EXPECT_EQ(v, new_v);
}

TEST(UserRepository_CRUD_Test, loginLikeId) {
    UserRepository rep;
    User user("test@test.com", "test", "testuser");
    size_t id = rep.makeUser(user);
    user.setId(id);
    std::optional<User> new_user_id = rep.getUserById(id);
    std::optional<User> new_user_login = rep.getUserByLogin(user.getLogin());
    User new_user;
    EXPECT_EQ(new_user_id, new_user_login);
    EXPECT_NO_FATAL_FAILURE(rep.deleteUser(user));
}

TEST(SolutionRepository_CRUD_Test, CRUD_getSolutionsBySenderId) {
    SolutionRepository rep;

    Solution solution1("01.01.1970", 1, ":/C/Users", 1, "result", "tokens.txt", "tree.txt", 1, "py");
    Solution solution2("01.01.1970", 1, "home/usr", 1, "result", "tokens.txt", "tree.txt", 1, "cpp");

    size_t id1 = rep.storeSolution(solution1);
    solution1.setId(id1);

    EXPECT_EQ(solution1, rep.getSolutionById(id1));

    size_t id2 = rep.storeSolution(solution2);
    solution2.setId(id2);

    EXPECT_EQ(solution2, rep.getSolutionById(id2));

    std::vector<Solution> v = {{id1, "01.01.1970", 1, ":/C/Users", 1, "result", "tokens.txt", "tree.txt", 1, "py"},
                               {id2, "01.01.1970", 1, "home/usr", 1, "result", "tokens.txt", "tree.txt", 1, "cpp"}};
    std::vector<Solution> new_v = rep.getSolutionsBySenderId(solution1.getSenderId());

    EXPECT_EQ(v, new_v);
    EXPECT_NO_FATAL_FAILURE(rep.deleteSolution(solution1));
    EXPECT_NO_FATAL_FAILURE(rep.deleteSolution(solution2));
}

TEST(SolutionRepository_CRUD_Test, CRUD_getSolutionsByTaskId) {
    SolutionRepository rep;

    Solution solution1("01.01.1970", 1, ":/C/Users", 1, "result", "tokens.txt", "tree.txt", 1, "py");
    Solution solution2("01.01.1970", 1, "home/usr", 1, "result", "tokens.txt", "tree.txt", 1, "cpp");

    size_t id1 = rep.storeSolution(solution1);
    solution1.setId(id1);
    size_t id2 = rep.storeSolution(solution2);
    solution2.setId(id2);
    std::vector<Solution> v = {solution1, solution2};
    std::vector<Solution> new_v = rep.getSolutionsByTaskId(solution1.getTaskId());

    EXPECT_EQ(v, new_v);
    EXPECT_NO_FATAL_FAILURE(rep.deleteSolution(solution1));
    EXPECT_NO_FATAL_FAILURE(rep.deleteSolution(solution2));
}

TEST(SolutionRepository_CRUD_Test, CRUD_getSolutionsByTaskIdAndLanguage) {
    SolutionRepository rep;
    Solution solution1("01.01.1970", 1, ":/C/Users", 1, "result", "tokens.txt", "tree.txt", 1, "py");
    Solution solution2("01.01.1970", 1, "home/usr", 1, "result", "tokens.txt", "tree.txt", 1, "cpp");

    size_t id1 = rep.storeSolution(solution1);
    solution1.setId(id1);
    size_t id2 = rep.storeSolution(solution2);
    solution2.setId(id2);
    std::vector<Solution> new_v = rep.getSolutionsByTaskIdAndLanguage(1, "py");

    EXPECT_EQ(solution1, new_v[0]);
    EXPECT_NO_FATAL_FAILURE(rep.deleteSolution(solution1));
    EXPECT_NO_FATAL_FAILURE(rep.deleteSolution(solution2));
}

TEST(SolutionRepository_CRUD_Test, CRUD_getSolutionsByTaskIdAndSenderId) {
    SolutionRepository rep;
    Solution solution1("01.01.1970", 1, ":/C/Users", 1, "result", "tokens.txt", "tree.txt", 1, "py");
    Solution solution2("01.01.1970", 1, "home/usr", 1, "other result", "tokens1.txt", "tree3.txt", 1, "cpp");
    Solution solution3("01.01.1971", 2, ":/C/Easter_egg", 1, "another result", "tokens2.txt", "tree1.txt", 1, "py");
    size_t id1 = rep.storeSolution(solution1);
    solution1.setId(id1);
    size_t id2 = rep.storeSolution(solution2);
    solution2.setId(id2);
    size_t id3 = rep.storeSolution(solution3);
    solution2.setId(id3);
    std::vector<Solution> v = {solution1, solution2};
    std::vector<Solution> new_v = rep.getSolutionsByTaskIdAndSenderId(1, 1);

    EXPECT_EQ(v, new_v);
    EXPECT_NO_FATAL_FAILURE(rep.deleteSolution(solution1));
    EXPECT_NO_FATAL_FAILURE(rep.deleteSolution(solution2));
    EXPECT_NO_FATAL_FAILURE(rep.deleteSolution(solution3));
}

TEST(SolutionRepository_CRUD_Test, tryToAddWithNotExistingTask) {
    SolutionRepository rep;
    Solution solution("01.01.1970", 1, ":/C/Users", 100500, "result", "tokens.txt", "tree.txt", 1, "py");
    try {
        rep.storeSolution(solution);
    } catch (pqxx::foreign_key_violation &e) {
        std::cout << e.what();
    }
}

TEST(SolutionRepository_CRUD_Test, tryToStoreWithNotExistingSender) {
    SolutionRepository rep;

    Solution solution("01.01.1970", 100500, ":/C/Users", 100500, "result", "tokens.txt", "tree.txt", 1, "cpp");
    try {
        rep.storeSolution(solution);
    } catch (pqxx::foreign_key_violation &keyViolation) {
        std::cout << keyViolation.what();
    }
}

TEST(MetricRepository_CRUD_Test, tryToStoreWithNotExistingSolution) {
    MetricRepository rep;
    MetricStat metricStat(100500, 0.8f, 0.9f, 0.89f, true, 0.85f);
    try {
        rep.storeMetric(metricStat);
    } catch (pqxx::foreign_key_violation &keyViolation) {
        std::cout << keyViolation.what();
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
