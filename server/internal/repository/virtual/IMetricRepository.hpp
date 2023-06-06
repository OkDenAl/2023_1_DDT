#ifndef SOURCEDOUT_IMETRICREPOSITORY_HPP
#define SOURCEDOUT_IMETRICREPOSITORY_HPP

#include <iostream>
#include <optional>

#include "MetricStat.hpp"

class IMetricRepository {
 public:
    virtual std::optional<MetricStat> getById(size_t id) = 0;

    virtual size_t storeMetric(MetricStat metric) = 0;

    virtual void updateMetric(MetricStat metric) = 0;

    virtual void deleteMetric(MetricStat metric) = 0;

    virtual void deleteMetricById(size_t id) = 0;
};

#endif  // SOURCEDOUT_IMETRICREPOSITORY_HPP
