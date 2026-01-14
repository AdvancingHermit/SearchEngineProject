#include "Index5.h"

int main(int argc, char* argv[]) {
    printf("main");
    Index5 index5 = Index5();
    printf("main2");
    index5.preprocess("data/WestburyLab.wikicorp.201004_100KB.txt");
    printf("main3");
    exit(0);
}