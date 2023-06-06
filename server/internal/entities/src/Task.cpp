#include "Task.hpp"

#include <iostream>
#include <utility>

Task::Task(std::string description_, float treshold_, std::string name_) noexcept
    : id(0), description(std::move(description_)), treshhold(treshold_), name(std::move(name_)) {}

Task::Task(size_t id, std::string description_, float treshold_, std::string name_) noexcept
    : id(id), description(std::move(description_)), treshhold(treshold_), name(std::move(name_)) {}

Task::Task() noexcept : id(0), treshhold(0) {}

unsigned long Task::getId() const noexcept { return id; }

const std::string &Task::getDescription() const noexcept { return description; }

void Task::setId(size_t id_) noexcept { id = id_; }

void Task::setDescription(const std::string &description_) noexcept { Task::description = description_; }

bool Task::operator==(const Task &rhs) const noexcept { return id == rhs.id; }

bool Task::operator!=(const Task &rhs) const noexcept { return !(rhs == *this); }

float Task::getTreshhold() const noexcept { return treshhold; }

void Task::setTreshhold(float treshhold_) noexcept { Task::treshhold = treshhold_; }

const std::string &Task::getName() const { return name; }

void Task::setName(const std::string &name_) { Task::name = name_; }
