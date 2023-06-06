#include "SolutionRepository.hpp"

#include <boost/format.hpp>
#include <iostream>
#include <pqxx/pqxx>

#include "Solution.hpp"

using namespace pqxx;

SolutionRepository::SolutionRepository() { manager = std::make_shared<dbManager>(); }

std::optional<Solution> SolutionRepository::getSolutionById(size_t id) {
    try {
        auto c = manager->connection();

        std::string sql = "SELECT * FROM solutions WHERE id=" + std::to_string(id);
        nontransaction n(*c);
        result r(n.exec(sql));

        manager->freeConnection(c);
        if (r.empty()) return std::nullopt;
        return makeSolution(r.begin());
    } catch (...) {
        throw;
    }
}

std::vector<Solution> SolutionRepository::getSolutionsBySenderId(size_t sender_id) {
    try {
        auto c = manager->connection();

        std::string sql = "SELECT * FROM solutions WHERE sender_id=" + std::to_string(sender_id);
        nontransaction n(*c);
        auto stream = stream_from::query(n, sql);
        std::vector<Solution> solutions;
        std::tuple<size_t, std::string, size_t, std::string, size_t, std::string, std::string, std::string, size_t,
                   std::string>
            row;
        while (stream >> row) {
            solutions.emplace_back(get<0>(row), get<1>(row), get<2>(row), get<3>(row), get<4>(row), get<5>(row),
                                   get<6>(row), get<7>(row), get<8>(row), get<9>(row));
        }
        stream.complete();

        manager->freeConnection(c);
        return solutions;
    } catch (...) {
        throw;
    }
}

std::vector<Solution> SolutionRepository::getSolutionsByTaskId(size_t task_id) {
    try {
        auto c = manager->connection();

        std::string sql = "SELECT * FROM solutions WHERE task_id=" + std::to_string(task_id);
        nontransaction n(*c);
        auto stream = stream_from::query(n, sql);
        std::vector<Solution> solutions;
        std::tuple<size_t, std::string, size_t, std::string, size_t, std::string, std::string, std::string, size_t,
                   std::string>
            row;
        while (stream >> row) {
            solutions.emplace_back(get<0>(row), get<1>(row), get<2>(row), get<3>(row), get<4>(row), get<5>(row),
                                   get<6>(row), get<7>(row), get<8>(row), get<9>(row));
        }
        stream.complete();

        manager->freeConnection(c);
        return solutions;
    } catch (...) {
        throw;
    }
}

std::vector<Solution> SolutionRepository::getSolutionsByTaskIdAndSenderId(size_t task_id, size_t sender_id) {
    try {
        auto c = manager->connection();

        std::string sql = (boost::format("SELECT * FROM solutions WHERE"
                                         " task_id='%s' AND sender_id='%s'") %
                           task_id % sender_id)
                              .str();
        nontransaction n(*c);
        auto stream = stream_from::query(n, sql);
        std::vector<Solution> solutions;
        std::tuple<size_t, std::string, size_t, std::string, size_t, std::string, std::string, std::string, size_t,
                   std::string>
            row;
        while (stream >> row) {
            solutions.emplace_back(get<0>(row), get<1>(row), get<2>(row), get<3>(row), get<4>(row), get<5>(row),
                                   get<6>(row), get<7>(row), get<8>(row), get<9>(row));
        }
        stream.complete();

        manager->freeConnection(c);
        return solutions;
    } catch (...) {
        throw;
    }
}

std::vector<Solution> SolutionRepository::getSolutionsByTaskIdAndLanguage(size_t task_id, std::string lang) {
    try {
        auto c = manager->connection();
        std::string sql = (boost::format("SELECT * FROM solutions WHERE"
                                         " task_id='%s' AND language='%s'") %
                           task_id % lang)
                              .str();
        nontransaction n(*c);
        auto stream = stream_from::query(n, sql);
        std::vector<Solution> solutions;
        std::tuple<size_t, std::string, size_t, std::string, size_t, std::string, std::string, std::string, size_t,
                   std::string>
            row;
        while (stream >> row) {
            solutions.emplace_back(get<0>(row), get<1>(row), get<2>(row), get<3>(row), get<4>(row), get<5>(row),
                                   get<6>(row), get<7>(row), get<8>(row), get<9>(row));
        }
        stream.complete();

        manager->freeConnection(c);
        return solutions;
    } catch (...) {
        throw;
    }
}

std::optional<Solution> SolutionRepository::getOriginalSolution(size_t id) {
    try {
        auto c = manager->connection();

        std::string sql =
            "SELECT * FROM solutions WHERE"
            " original_solution_id=" +
            std::to_string(id);
        nontransaction n(*c);
        result r(n.exec(sql));

        manager->freeConnection(c);
        if (r.empty()) return std::nullopt;
        return makeSolution(r.begin());
    } catch (...) {
        throw;
    }
}

size_t SolutionRepository::storeSolution(Solution solution) {
    try {
        auto c = manager->connection();

        std::string sql =
            (boost::format("INSERT INTO solutions (send_date,sender_id, source, task_id, result, tokens, "
                           "astTree, original_solution_id, language) "
                           "VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s') RETURNING id; ") %
             solution.getSendDate() % solution.getSenderId() % solution.getSource() % solution.getTaskId() %
             solution.getResult() % solution.getTokens() % solution.getAstTree() % solution.getOrigSolution() %
             solution.getLanguage())
                .str();
        work w(*c);
        row r = (w.exec1(sql));
        w.commit();

        manager->freeConnection(c);
        return r["id"].as<size_t>();
    } catch (...) {
        throw;
    }
}

void SolutionRepository::updateSolution(Solution solution) {
    try {
        auto c = manager->connection();

        std::string sql = (boost::format("UPDATE solutions SET send_date = '%s', sender_id = '%s', source = '%s',"
                                         " task_id = '%s', result = '%s', tokens = '%s', astTree = '%s', "
                                         "original_solution_id = '%s', language = '%s';") %
                           solution.getSendDate() % solution.getSenderId() % solution.getSource() %
                           solution.getTaskId() % solution.getResult() % solution.getTokens() % solution.getAstTree() %
                           solution.getOrigSolution() % solution.getLanguage())
                              .str();
        work w(*c);
        w.exec(sql);

        manager->freeConnection(c);
    } catch (...) {
        throw;
    }
}

void SolutionRepository::deleteSolutionById(size_t id) {
    try {
        auto c = manager->connection();

        std::string sql = "DELETE FROM solutions WHERE id=" + std::to_string(id);
        work w(*c);
        w.exec(sql);
        w.commit();

        manager->freeConnection(c);
    } catch (...) {
        throw;
    }
}

void SolutionRepository::deleteSolution(Solution solution) { deleteSolutionById(solution.getId()); }

Solution SolutionRepository::makeSolution(const result::const_iterator &c) {
    return {c.at(c.column_number("id")).as<size_t>(),
            c.at(c.column_number("send_date")).as<std::string>(),
            c.at(c.column_number("sender_id")).as<size_t>(),
            c.at(c.column_number("source")).as<std::string>(),
            c.at(c.column_number("task_id")).as<size_t>(),
            c.at(c.column_number("result")).as<std::string>(),
            c.at(c.column_number("tokens")).as<std::string>(),
            c.at(c.column_number("astTree")).as<std::string>(),
            c.at(c.column_number("original_solution_id")).as<size_t>(),
            c.at(c.column_number("language")).as<std::string>()};
}
