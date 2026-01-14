#include "Index5.h"


WikiItem::WikiItem() {
    str = "";
    articles = nullptr;
    next = nullptr;
}
WikiItem::~WikiItem() {
    str = nullptr;
    delete articles;
    delete next;
}

WikiItem::WikiItem(string s, WikiItem* n) {
    str = s;
    articles = nullptr;
    next = n;
}
void WikiItem::addDoc(WikiItem* article) {
    article->next = articles;
    articles = article;
}

WikiItemMap::WikiItemMap(int n) {
    numBuckets = n;
    printf("wikitem1");
    buckets = new WikiItem[numBuckets];
    printf("wikitem2");


}
WikiItemMap::~WikiItemMap() {
    for (int i = 0; i < numBuckets; ++i) {
        WikiItem curr = buckets[i];
    }
    delete[] buckets;
}

Index5::Index5(): map(300'000) {};

void Index5::preprocess(string filename) {

    ifstream file;
    printf("hi");
    file.open (filename);
    printf("hi2");
    if (!file.good()) return;
    printf("hi2.5");
    if (!file.is_open()) return;
    printf("hi3");
    string word;
    while (file >> word)
    {
        cout<< word << '\n';
    }

}
