#pragma once

#include <iostream>

struct Task{
    std::size_t id;
    std::string name;
    std::string description;
    double threshold;

    Task(std::size_t id, std::string_view desc, std::string_view name, double threshold);
};
