#include "core/Index5.h"

#include "components/preprocessors/BasicPreprocessor.cpp"
#include "components/hashers/BasicHasher.cpp"
#include "components/searchers/BasicSearcher.cpp"
#include "components/stores/BasicHashTable.cpp"
#include "components/rankers/MostMatchesRanker.cpp"
/*
*/

int main(int argc, char* argv[]) {
    printf("main \n");

    BasicPreprocessor preprocessor;
    BasicHasher hasher;
    BasicSearcher searcher;
    BasicHashTable store = BasicHashTable(300'000, &hasher);
    MostMatchesRanker MMRanker;
    Index index = Index(&store, &preprocessor, &hasher, &searcher, &MMRanker);

    printf("Started preprocessing \n");
    std::string filename = "data/WestburyLab.wikicorp.201004_5MB.txt";
    index.preprocess(filename);


    printf("Finished preprocessing \n");

    std:string qy = "the";
    printf("Start searching \n");
    std::vector<Doc> res = index.search(qy);
    printf("Finished searching \n");
    for (std::vector<Doc>::iterator it = res.begin(); it != res.end(); ++it) {
        std::cout << it->title << " "  << endl;
    }

    printf("Started Ranking \n");
    std::vector<ScoredDoc> res_scored = index.rank(res, qy, filename);
    printf("Finished Ranking \n");
    for (std::vector<ScoredDoc>::iterator it = res_scored.begin(); it != res_scored.end(); it++) {
        std::cout << it->title << " " << it->score << endl;
    }



    return 0;
}
