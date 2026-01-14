#include "Index5.h"

int main(int argc, char* argv[]) {
    printf("main \n");
    Index5 index5 = Index5();
    printf("Started preprocessing \n");
    index5.preprocess("data/WestburyLab.wikicorp.201004_100MB.txt");
    printf("Finished preprocessing \n");
    printf("Start searching \n");
    WikiItem* res = index5.search("albedo");
    while (res) {
        cout << res->str << endl;
        res = res->next;
    }

    printf("Finished Searching \n");


    return 0;
}