#include <fstream>
#include <iostream>
#include <algorithm>

#include "../../core/interfaces.h"
#include <map>
#include <sstream>
#include <regex>


std::map<std::string, std::vector<std::string>> load_test() {

    std::map<std::string, std::vector<std::string>> results = std::map<std::string, std::vector<std::string>>{};

    std::string filename = "src/components/test/test_100MB.txt";
    std::ifstream file;
    file.open (filename);
    if (!file.good()) {
        printf("Error reading file");
        return results;
    }
    if (!file.is_open()) {
        printf("No file is open");
        return results;
    }
    std::string word;
    std::string line;
    std::string end = "---END.OF.WORD---";

    std::vector<std::string> curr_vector;

    short take_next = 1;
    printf("ayoo");

    while (std::getline(file, line))
    {
        if (line == end) {
            take_next = 1;
            continue;
        }
        if (take_next) {
            results.insert({word, curr_vector});
            word = line;
            curr_vector = std::vector<std::string>{};
            take_next = 0;
            continue;
        }

        curr_vector.push_back(line);

    }
    results.insert({word, curr_vector});
    printf("finished while loop");
    file.close();

    return results;
}

void CompareResult(std::string query, std::vector<Doc> index_res, std::vector<std::string> benchmark_res) {

    std::vector<std::string> index_res_as_strings = std::vector<std::string>{};
    for (const Doc& doc : index_res) {
        index_res_as_strings.push_back(doc.title);
    }
    std::sort(index_res_as_strings.begin(), index_res_as_strings.end());
    std::sort(benchmark_res.begin(), benchmark_res.end());


    for (int i = 0; i < benchmark_res.size(); i++) {
        if (index_res_as_strings.size() == i) {
            printf("Seems to be missing %s on %s", benchmark_res[i].c_str(), query.c_str());
            break;
        }

        if (benchmark_res[i] != index_res_as_strings[i]) {
            if (std::find(index_res_as_strings.begin(), index_res_as_strings.end(), benchmark_res[i]) == index_res_as_strings.end()) {
                printf("On Query %s\nWas supposed to have %s\n", query.c_str(), benchmark_res[i].c_str());
            }
        }
    }
}

void test(Index* index) {

    std::map<std::string, std::vector<std::string>> results = load_test();
    std::vector<std::string> some_200 = std::vector<std::string>{};
    int count = 0;
    std::regex re(R"([0-9A-Z\"\(\)\$'\,#\;:\-\.\/!\*\?\<┬\+&\%=\>\@╬\[\]\\\^\_\`├])");
    for (std::map<std::string, std::vector<std::string>>::iterator it = results.begin(); it != results.end(); ++it) {
        if (it->first.empty()) continue;
        if (std::regex_search(it->first, re)) continue;
        if (it->first.length() < 2) continue;
        count++;
        if (count > 1000) break;
        some_200.push_back(it->first);
    }
    std::cout << some_200[0] << std::endl;
    for (const std::string& s : some_200) {
        auto res = index->search(s);
        CompareResult(s, res, results.at(s));
    }
}