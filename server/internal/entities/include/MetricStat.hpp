#ifndef SOURCEDOUT_METRICSTAT_HPP
#define SOURCEDOUT_METRICSTAT_HPP

#include <iostream>

class MetricStat {
 public:
    MetricStat() noexcept;

    MetricStat(size_t solutionId, float textBasedRes, float tokenBasedRes, float treeBasedRes, bool verdict,
               float meanRes) noexcept;

    MetricStat(size_t id, size_t solutionId, float textBasedRes, float tokenBasedRes, float treeBasedRes, bool verdict,
               float meanRes) noexcept;

    [[nodiscard]] size_t getId() const noexcept;

    void setId(size_t id);

    [[nodiscard]] size_t getSolutionId() const noexcept;

    void setSolutionId(size_t solutionId) noexcept;

    [[nodiscard]] float getTextBasedRes() const noexcept;

    void setTextBasedRes(float textBasedRes) noexcept;

    [[nodiscard]] float getTokenBasedRes() const noexcept;

    void setTokenBasedRes(float tokenBasedRes) noexcept;

    [[nodiscard]] float getTreeBasedRes() const noexcept;

    void setTreeBasedRes(float treeBasedRes) noexcept;

    [[nodiscard]] bool isVerdict() const noexcept;

    void setVerdict(bool verdict) noexcept;

    [[nodiscard]] float getMeanRes() const noexcept;

    void setMeanRes(float meanRes) noexcept;

    bool operator==(const MetricStat &rhs) const noexcept;

    bool operator!=(const MetricStat &rhs) const noexcept;

 private:
    size_t id;
    size_t solution_id;
    float text_based_res;
    float token_based_res;
    float tree_based_res;
    bool verdict;
    float mean_res;
};

#endif  // SOURCEDOUT_METRICSTAT_HPP
