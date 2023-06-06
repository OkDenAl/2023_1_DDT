//
// Created by Николай Степанов on 03.05.2023.
//
#include "SolutionManager.h"

#include <memory>
#include <utility>

#include "SolutionService.h"
#include "Utils.h"

SolutionManager::SolutionManager()
    : serializer(std::make_shared<Serializer>()), solutionService(std::make_shared<SolutionService>()) {}

void SolutionManager::setService(std::shared_ptr<ISolutionService> service) { solutionService = std::move(service); }

http::message_generator SolutionManager::createSolution(http::request<http::string_body>&& req) {
    size_t user_id, task_id;
    std::string filename, filedata;
    try {
        std::tie(user_id, task_id, filename, filedata) = serializer->deserialNewSolutionData(req.body());
    } catch (...) {
        return getBadRequest(req, "Bad parameters");
    }

    try {
        Solution sol;
        Solution::Codes codes;
        std::tie(sol, codes) = solutionService->createSolution(user_id, task_id, filename, filedata);
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = serializer->serialNewSolution(sol, codes);
        return res;
    } catch (const std::exception& e) {
        return getInternalServerError(req, e.what());
    }
}

http::message_generator SolutionManager::getAllSolutions(http::request<http::string_body>&& req) {
    size_t user_id, task_id;

    try {
        std::tie(user_id, task_id) = serializer->deserialTaskData(req.body());
    } catch (...) {
        return getBadRequest(req, "Bad parameters");
    }

    try {
        std::vector<Solution> solutions;
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = serializer->serialSolutions(solutions);
        res.prepare_payload();
        return res;
    } catch (const std::exception& e) {
        return getBadRequest(req, e.what());
    }
}
