//
// Created by march on 22.05.2023.
//
#include <utility>

#include "DiffLib.h"

void FoundSame::setData(std::vector<std::pair<std::string, std::pair<int, int> > > _tokens1,
                        std::vector<std::pair<std::string, std::pair<int, int> > > _tokens2) {
    str_int_tokens1 = std::move(_tokens2);
    str_int_tokens2 = std::move(_tokens1);
}

std::pair<std::string, std::string> FoundSame::getTexts() {
    unsigned long n = str_int_tokens1.size();
    unsigned long m = str_int_tokens2.size();

    std::vector<std::vector<int> > dist(n + 1, std::vector<int>(m + 1, 0));

    for (size_t i = 0; i < n + 1; i++) {
        dist[i][0] = static_cast<int>(i);
    }

    for (size_t i = 0; i < m + 1; i++) {
        dist[0][i] = static_cast<int>(i);
    }

    std::vector<std::vector<Elem2> > cache(n + 1, std::vector<Elem2>(m + 1));

    for (size_t i = 1; i <= n; i++) {
        cache[i][0] = {"I", {"%", str_int_tokens1[i - 1].second}, str_int_tokens1[i - 1]};
    }
    for (size_t i = 1; i <= m; i++) {
        cache[0][i] = {"D", str_int_tokens2[i - 1], {"#", str_int_tokens2[i - 1].second}};
    }

    std::pair<std::string, std::pair<int, int> > r, h;
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= m; j++) {
            h = str_int_tokens1[i - 1], r = str_int_tokens2[j - 1];
            std::vector<std::pair<int, Elem2> > cases;

            if (r.first == h.first)
                cases.push_back({dist[i - 1][j - 1], {"C", r, h}});
            else
                cases.push_back({dist[i - 1][j - 1] + 1, {"R", r, h}});
            cases.push_back({dist[i][j - 1] + 1, {"D", r, {"#", r.second}}});
            cases.push_back({dist[i - 1][j] + 1, {"I", {"%", h.second}, h}});

            dist[i][j] = cases[0].first;
            cache[i][j] = cases[0].second;

            for (size_t k = 1; k < cases.size(); k++) {
                if (dist[i][j] > cases[k].first) {
                    dist[i][j] = cases[k].first;
                    cache[i][j] = cases[k].second;
                }
            }
        }
    }

    std::vector<Elem2> alignment;
    size_t i = n, j = m;
    while (i != 0 || j != 0) {
        std::string op = cache[i][j].op;
        auto temp = cache[i][j];
        cache[i][j] = temp;
        alignment.push_back(cache[i][j]);
        if (op == "C" || op == "R") {
            i--, j--;
        } else if (op == "I") {
            i--;
        } else {
            j--;
        }
    }
    std::reverse(alignment.begin(), alignment.end());

    res_alignment = alignment;

    return tokens2html();
}

std::pair<std::string, std::string> FoundSame::tokens2text() {
    std::string res1, res2;
    std::vector<std::string> ops;

    int line = res_alignment[0].token1.second.first;

    for (auto& i : res_alignment) {
        if (i.token1.second.first > line) {
            while (line != i.token1.second.first) {
                res1 += '\n';
                line++;
            }
        }
        res1 += i.token1.first, res1 += " ";
    }

    line = res_alignment[0].token2.second.first;
    for (auto& i : res_alignment) {
        if (i.token2.second.first > line) {
            res2 += '\t';
            // outOps(ops, res2);
            ops.clear();
            while (line < i.token2.second.first) {
                res2 += '\n';
                line++;
            }
        }
        ops.push_back(i.op);
        res2 += i.token2.first, res2 += " ";
    }

    res1.pop_back(), res2.pop_back();

    return {res1, res2};
}

void FoundSame::outOps(std::vector<std::string> ops, std::string& str) {
    if (ops.empty()) return;
    std::string o = ops[0];
    int f = 0;
    for (auto& op : ops) {
        if (op != o) {
            f = 1;
            break;
        }
    }
    if (f == 0) {
        str += "[" + o + "]";
    } else {
        for (auto& op : ops) {
            str += op, str += " ";
        }
    }
}

std::pair<std::string, std::string> FoundSame::tokens2html() {
    std::string teg_I = "<span style=\"background-color: #00FF00\">";
    std::string teg_D = "<span style=\"background-color: #CD5C5C\">";
    std::string teg_C = "<span style=\"background-color: #96CC9F\">";
    std::string teg_R = "<span style=\"background-color: #FFD700\">";
    std::string close_teg = "</span>";

    for (auto& i : res_alignment) {
        size_t pos;
        while ((pos = i.token1.first.find("<")) != std::string::npos) {
            i.token1.first.replace(pos, 1, "&lt;");
        }
        while ((pos = i.token1.first.find(">")) != std::string::npos) {
            i.token1.first.replace(pos, 1, "&gt;");
        }

        while ((pos = i.token2.first.find("<")) != std::string::npos) {
            i.token2.first.replace(pos, 1, "&lt;");
        }
        while ((pos = i.token2.first.find(">")) != std::string::npos) {
            i.token2.first.replace(pos, 1, "&gt;");
        }

        if (i.token1.first == "%") {
            i.token1.first = "";
            i.token1.second.first = -1;
        }

        if (i.token2.first == "#") {
            i.token2.first = "";
            i.token2.second.first = -1;
        }
    }

    std::string res1 =
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<div>";
    std::string res2 = res1;
    std::vector<std::string> ops;

    int line = res_alignment[0].token1.second.first;

    int f = 0;

    for (auto& i : res_alignment) {
        if (i.token1.second.first > line) {
            while (line < i.token1.second.first) {
                res1 += "<br>";
                res1 += '\n';
                line++;
            }
            f = 1;
        }
        if (f == 1) {
            res1 += "<span>";
            for (int k = 0; k < i.token1.second.second; k++) {
                res1 += "&nbsp;";
            }
            res1 += "</span>";
            f = 0;
        }
        if (i.op == "I") res1 += teg_I;
        if (i.op == "D") res1 += teg_D;
        if (i.op == "C") res1 += teg_C;
        if (i.op == "R") res1 += teg_R;

        res1 += i.token1.first;
        if (!i.token1.first.empty()) res1 += " ";
        res1 += close_teg;
    }

    line = res_alignment[0].token2.second.first;
    for (auto& i : res_alignment) {
        if (i.token2.second.first > line) {
            while (line < i.token2.second.first) {
                res2 += "<br>";
                res2 += '\n';
                line++;
            }
            f = 1;
        }
        if (f == 1) {
            res2 += "<span>";
            for (int k = 0; k < i.token2.second.second; k++) {
                res2 += "&nbsp;";
            }
            res2 += "</span>";
            f = 0;
        }
        if (i.op == "I") res2 += teg_I;
        if (i.op == "D") res2 += teg_D;
        if (i.op == "C") res2 += teg_C;
        if (i.op == "R") res2 += teg_R;

        res2 += i.token2.first;
        if (!i.token2.first.empty()) res2 += " ";
        res2 += close_teg;
    }

    res1 +=
        "</div>\n"
        "</html>";
    res2 +=
        "</div>\n"
        "</html>";

    return {res1, res2};
}
