#ifndef SOURCEDOUT_METRICREPOSITORY_HPP
#define SOURCEDOUT_METRICREPOSITORY_HPP

#include <optional>
#include <pqxx/pqxx>

#include "IMetricRepository.hpp"
#include "dbManager.hpp"

using namespace pqxx;

class MetricRepository : public IMetricRepository {
 public:
    MetricRepository();

    std::optional<MetricStat> getById(size_t id) override;

    size_t storeMetric(MetricStat metric) override;

    void updateMetric(MetricStat metric) override;

    void deleteMetric(MetricStat metric) override;

    void deleteMetricById(size_t id) override;

 private:
    std::shared_ptr<dbManager> manager;

    static MetricStat makeMetric(const result::const_iterator &c);
};

#endif  // SOURCEDOUT_METRICREPOSITORY_HPP
