#include "core/Index5.h"

#include "components/preprocessors/BasicPreprocessor.cpp"
#include "components/hashers/BasicHasher.cpp"
#include "components/searchers/BasicSearcher.cpp"
#include "components/stores/BasicHashTable.cpp"
/*
*/

int main(int argc, char* argv[]) {
    printf("main \n");

    BasicPreprocessor preprocessor;
    BasicHasher hasher;
    BasicSearcher searcher = {};
    BasicHashTable store = BasicHashTable(300'000, &hasher);
    Index index = Index(&store, &preprocessor, &hasher, &searcher, nullptr);

    printf("Started preprocessing \n");
    index.preprocess("data/WestburyLab.wikicorp.201004_100MB.txt");


    printf("Finished preprocessing \n");
    printf("Start searching \n");
    std::vector<Doc> res = index.search("albedo");

    for (std::vector<Doc>::iterator it = res.begin(); it != res.end(); it++) {
        std::cout << it->title << " " << it->loc << endl;
    }


    printf("Finished Searching \n");


    return 0;
}
