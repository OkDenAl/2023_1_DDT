#include "MetricRepository.hpp"

#include <boost/format.hpp>

#include "MetricStat.hpp"

MetricRepository::MetricRepository() { manager = std::make_shared<dbManager>(); }

std::optional<MetricStat> MetricRepository::getById(size_t id) {
    try {
        auto c = manager->connection();

        std::string sql = "SELECT * FROM metricStat WHERE id=" + std::to_string(id);
        nontransaction n(*c);
        result r(n.exec(sql));

        manager->freeConnection(c);
        if (r.empty()) return std::nullopt;
        return makeMetric(r.begin());
    } catch (...) {
        throw;
    }
}

size_t MetricRepository::storeMetric(MetricStat metric) {
    try {
        auto c = manager->connection();

        std::string sql = (boost::format("INSERT INTO metricStat (solution_id, text_based_res, token_based_res, "
                                         "tree_based_res, verdict, mean_res) "
                                         "VALUES ('%s', '%s', '%s', '%s', '%s', '%s') RETURNING id; ") %
                           metric.getSolutionId() % metric.getTextBasedRes() % metric.getTokenBasedRes() %
                           metric.getTreeBasedRes() % metric.isVerdict() % metric.getMeanRes())
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

void MetricRepository::updateMetric(MetricStat metric) {
    try {
        auto c = manager->connection();

        std::string sql = (boost::format("UPDATE metricStat SET solution_id = '%s',"
                                         " text_based_res = '%s', token_based_res = '%s',"
                                         " tree_based_res = '%s', verdict = '%s', mean_res = '%s';") %
                           metric.getSolutionId() % metric.getTextBasedRes() % metric.getTokenBasedRes() %
                           metric.getTreeBasedRes() % metric.isVerdict() % metric.getMeanRes())
                              .str();
        work w(*c);
        w.exec(sql);

        manager->freeConnection(c);
    } catch (...) {
        throw;
    }
}

void MetricRepository::deleteMetric(MetricStat metric) { deleteMetricById(metric.getId()); }

void MetricRepository::deleteMetricById(size_t id) {
    try {
        auto c = manager->connection();

        std::string sql = "DELETE FROM metricStat WHERE id=" + std::to_string(id);
        work w(*c);
        w.exec(sql);
        w.commit();

        manager->freeConnection(c);
    } catch (...) {
        throw;
    }
}

MetricStat MetricRepository::makeMetric(const result::const_iterator &c) {
    return {c.at(c.column_number("id")).as<size_t>(),
            c.at(c.column_number("solution_id")).as<size_t>(),
            c.at(c.column_number("text_based_res")).as<float>(),
            c.at(c.column_number("token_based_res")).as<float>(),
            c.at(c.column_number("tree_based_res")).as<float>(),
            c.at(c.column_number("verdict")).as<bool>(),
            c.at(c.column_number("mean_res")).as<float>()};
}
