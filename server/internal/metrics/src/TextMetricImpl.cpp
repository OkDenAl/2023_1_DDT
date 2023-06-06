//
// Created by march on 02.05.2023.
//

#include "TextMetricsLib.h"

void PrepareDataTextMetric::setData(std::string text1, std::string text2) {
    std::string non_comm_text1 = deleteComments(text1);
    std::string non_comm_text2 = deleteComments(text2);

    tokens1 = tbmTokenizer(non_comm_text1);
    tokens2 = tbmTokenizer(non_comm_text2);
}

std::string PrepareDataTextMetric::deleteComments(const std::string &text) {
    std::string modif;
    std::string res;

    std::stringstream ss;
    std::string line;

    ss << text;

    while (getline(ss, line)) {
        line.push_back('\0');
        modif += line;
    }

    bool s_comm = false;
    bool m_comm = false;

    for (size_t i = 0; i < modif.size(); i++) {
        if (s_comm && modif[i] == '\0')
            s_comm = false;
        else if (m_comm && modif[i] == '*' && modif[i + 1] == '/')
            m_comm = false, i++;
        else if (s_comm || m_comm)
            continue;
        else if (modif[i] == '/' && modif[i + 1] == '/')
            s_comm = true, i++;
        else if (modif[i] == '/' && modif[i + 1] == '*')
            m_comm = true, i++;

        else if (modif[i] != '\0')
            res += modif[i];
        else if (!res.empty() && res[res.size() - 1] != '\n')
            res += '\n';
    }
    return res;
}

std::vector<std::string> PrepareDataTextMetric::tbmTokenizer(const std::string &text) {
    boost::char_separator<char> sep(" {}();,\"\0\'");
    std::vector<std::string> res;
    boost::tokenizer<boost::char_separator<char> > tokens(text, sep);

    for (const std::string &s : tokens) {
        if (!s.empty() && s[0] != '\n' && s[0] != '\0') {
            res.push_back(s);
        }
    }
    return res;
}

double LevDistTextMetric::getMetric() {
    unsigned long n = tokens1.size();
    unsigned long m = tokens2.size();
    int x, y, z;

    std::vector<std::vector<int> > lev(n, std::vector<int>(m, 0));

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

double JaccardTextMetric::getMetric() {
    std::set<std::string> s1;
    std::set<std::string> s2;

    for (auto &i : tokens1) s1.insert(i);
    for (auto &i : tokens2) s2.insert(i);

    std::set<std::string> intersect_sets;
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(intersect_sets, intersect_sets.begin()));

    std::set<std::string> union_sets;
    set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(union_sets, union_sets.begin()));

    if (union_sets.empty())
        return 0;
    else
        return static_cast<double>(intersect_sets.size()) / static_cast<double>(union_sets.size());
}
