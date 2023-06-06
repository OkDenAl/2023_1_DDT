#include "Task.h"

Task::Task(std::size_t id, std::string_view desc, std::string_view name, double threshold) :
        id(id), description(desc), name(name), threshold(threshold) {}
