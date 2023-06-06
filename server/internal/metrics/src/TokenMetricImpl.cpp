//
// Created by march on 04.05.2023.
//

#include "TokenMetricLib.h"

double LevDistTokenMetric::getMetric() {
    unsigned long n = tokens1.size();
    unsigned long m = tokens2.size();
    int x, y, z;

    std::vector<std::vector<int>> lev(n, std::vector<int>(m, 0));

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            if (std::min(i, j) == 0) {
                lev[i][j] = static_cast<int>(std::max(i, j));
            } else {
                x = lev[i - 1][j];
                y = lev[i][j - 1];
                z = lev[i - 1][j - 1];
                lev[i][j] = std::min(x, std::min(y, z));
                if (tokens1[i] != tokens2[j]) {
                    lev[i][j]++;
                }
            }
        }
    }

    if (n == 0 || m == 0) return 0;
    double res = 1.0 - static_cast<double>(lev[n - 1][m - 1]) / static_cast<double>(std::max(n, m));
    return res;
}

double WShinglingTokenMetric::getMetric() {
    unsigned long n = tokens1.size();
    unsigned long m = tokens2.size();

    if (n < 3 || m < 3) return 0;

    std::vector<std::tuple<int, int, int>> sh1;
    std::vector<std::tuple<int, int, int>> sh2;

    for (size_t i = 0; i < n - 2; i++) {
        sh1.emplace_back(tokens1[i], tokens1[i + 1], tokens1[i + 2]);
    }
    for (size_t i = 0; i < m - 2; i++) {
        sh2.emplace_back(tokens2[i], tokens2[i + 1], tokens2[i + 2]);
    }

    std::set<std::tuple<int, int, int>> s1;
    std::set<std::tuple<int, int, int>> s2;

    for (auto &i : sh1) s1.insert(i);
    for (auto &i : sh2) s2.insert(i);

    std::set<std::tuple<int, int, int>> intersect_sets;
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(intersect_sets, intersect_sets.begin()));

    std::set<std::tuple<int, int, int>> union_sets;
    set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(union_sets, union_sets.begin()));

    if (union_sets.empty())
        return 0;
    else
        return static_cast<double>(intersect_sets.size()) / static_cast<double>(union_sets.size());
}

void PrepareDataTokenMetric::setData(std::vector<int> _tokens1, std::vector<int> _tokens2) {
    tokens1 = std::move(_tokens1);
    tokens2 = std::move(_tokens2);
}
