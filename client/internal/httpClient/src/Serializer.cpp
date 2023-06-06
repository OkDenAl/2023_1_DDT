#include "Serializer.h"

#include <sstream>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

std::string Serializer::serialLoginData(std::string_view login, std::string_view password) {
    boost::property_tree::ptree json;
    json.put("login", login);
    json.put("password", password);
    std::stringstream out;
    boost::property_tree::write_json(out, json);
    return out.str();
}

User Serializer::deserialUserData(std::string_view body) {
    std::stringstream ss;
    ss << body;
    boost::property_tree::ptree json;
    boost::property_tree::read_json(ss, json);
    User res = {
            json.get<std::size_t>("user_id"),
            json.get<std::string>("login"),
            "",
            json.get<std::string>("username")
    };
    return res;
}

std::string
Serializer::serialRegisterData(std::string_view login, std::string_view username, std::string_view password) {
    boost::property_tree::ptree json;
    json.put("login", login);
    json.put("username", username);
    json.put("password", password);
    std::stringstream out;
    boost::property_tree::write_json(out, json);
    return out.str();
}

std::vector<Task> Serializer::deserialAllTasks(std::string_view body) {
    std::stringstream ss;
    ss << body;
    boost::property_tree::ptree json;
    boost::property_tree::read_json(ss, json);
    std::vector<Task> tasks;
    for (auto &task : json.get_child("tasks")) {
        Task new_task(task.second.get<std::size_t>("task_id"), task.second.get<std::string>("description"),
                      task.second.get<std::string>("name"), task.second.get<double>("threshold"));
        tasks.push_back(new_task);
    }
    return tasks;
}

std::string Serializer::serialSolutionData(const int &user_id, const int &task_id, const std::string& filename,
                                           const std::string& path_to_file) {
    boost::property_tree::ptree json;
    json.put("user_id", user_id);
    json.put("task_id", task_id);
    json.put("filename", filename);
    std::ifstream file(path_to_file);
    std::ostringstream sstr;
    sstr << file.rdbuf();
    std::string source = sstr.str();
    json.put("filedata", source);
    std::stringstream out;
    boost::property_tree::write_json(out, json);
    return out.str();
}

Solution Serializer::deserialSolutionData(std::string_view body) {
    std::stringstream ss;
    ss << body;
    boost::property_tree::ptree json;
    boost::property_tree::read_json(ss, json);
    Solution res = {
            json.get<std::size_t>("sol_id"),
            json.get<std::string>("source"),
            json.get<std::string>("result"),
    };
    return res;
}

std::pair<Solution, Solution::Codes> Serializer::deserialNewSolutionData(std::string_view body) {
    std::stringstream ss;
    ss << body;
    boost::property_tree::ptree json;
    boost::property_tree::read_json(ss, json);
    Solution sol = {
            json.get<std::size_t>("sol_id"),
            json.get<std::string>("source"),
            json.get<std::string>("result"),
    };
    Solution::Codes codes = {
            json.get<std::string>("original"),
            json.get<std::string>("your_code"),
    };
    return {sol, codes};
}

std::string Serializer::serialNewTaskData(std::string_view name, std::string_view desc, double threshold) {
    boost::property_tree::ptree json;
    json.put("name", name);
    json.put("description", desc);
    json.put("threshold", threshold);
    std::stringstream out;
    boost::property_tree::write_json(out, json);
    return out.str();
}
