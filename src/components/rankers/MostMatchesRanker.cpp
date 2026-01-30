#include "../../core/interfaces.h"
#include "../sorters/MergeSort.cpp"
#include <fstream>
#include <istream>

class MostMatchesRanker : public IRanker {
public:
    ~MostMatchesRanker() = default;
    std::vector<ScoredDoc> rank(const std::vector<Doc>& candidates, std::string& query, IStore* store, std::string& filename) override;
};

std::vector<ScoredDoc> MostMatchesRanker::rank(const std::vector<Doc>& candidates,
                                        std::string& query, IStore* store,
                                        std::string& filename) {
    std::vector<ScoredDoc> scoredDocs(candidates.size());
    std::ifstream file;
    file.open (filename);
    if (!file.good()) {
        printf("Error reading file");
        return scoredDocs;
    }
    if (!file.is_open()) {
        printf("No file is open");
        return scoredDocs;
    }
    for (int i = 0; i < candidates.size(); ++i) {
        file.seekg(candidates[i].start_loc, std::ios::beg);
        std::string word;
        int counter = 0;
        while (file >> word && word != END) {
          if (word == query) counter++;
        }
        scoredDocs[i].title = candidates[i].title;
        scoredDocs[i].start_loc = candidates[i].start_loc;
        scoredDocs[i].score = counter;
    }
    file.close();
    return MergeSort(scoredDocs);
}

