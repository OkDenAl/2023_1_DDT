
#include "MetricStat.hpp"

MetricStat::MetricStat(unsigned long solutionId, float textBasedRes, float tokenBasedRes, float treeBasedRes,
                       bool verdict, float meanRes) noexcept
    : id(0),
      solution_id(solutionId),
      text_based_res(textBasedRes),
      token_based_res(tokenBasedRes),
      tree_based_res(treeBasedRes),
      verdict(verdict),
      mean_res(meanRes) {}

MetricStat::MetricStat(size_t id, size_t solutionId, float textBasedRes, float tokenBasedRes, float treeBasedRes,
                       bool verdict, float meanRes) noexcept
    : id(id),
      solution_id(solutionId),
      text_based_res(textBasedRes),
      token_based_res(tokenBasedRes),
      tree_based_res(treeBasedRes),
      verdict(verdict),
      mean_res(meanRes) {}

MetricStat::MetricStat() noexcept
    : id(0), solution_id(0), text_based_res(0), token_based_res(0), tree_based_res(), verdict(true), mean_res(0) {}

size_t MetricStat::getId() const noexcept { return id; }

void MetricStat::setId(size_t id_) { id = id_; }

size_t MetricStat::getSolutionId() const noexcept { return solution_id; }

void MetricStat::setSolutionId(size_t solutionId) noexcept { solution_id = solutionId; }

float MetricStat::getTextBasedRes() const noexcept { return text_based_res; }

void MetricStat::setTextBasedRes(float textBasedRes) noexcept { text_based_res = textBasedRes; }

float MetricStat::getTokenBasedRes() const noexcept { return token_based_res; }

void MetricStat::setTokenBasedRes(float tokenBasedRes) noexcept { token_based_res = tokenBasedRes; }

float MetricStat::getTreeBasedRes() const noexcept { return tree_based_res; }

void MetricStat::setTreeBasedRes(float treeBasedRes) noexcept { tree_based_res = treeBasedRes; }

bool MetricStat::isVerdict() const noexcept { return verdict; }

void MetricStat::setVerdict(bool verdict_) noexcept { verdict = verdict_; }

float MetricStat::getMeanRes() const noexcept { return mean_res; }

void MetricStat::setMeanRes(float meanRes) noexcept { mean_res = meanRes; }

bool MetricStat::operator==(const MetricStat &rhs) const noexcept { return id == rhs.id; }

bool MetricStat::operator!=(const MetricStat &rhs) const noexcept { return !(rhs == *this); }
