using namespace std;
#include <string>
#include <fstream>
#include <iostream>

class WikiItem {
    public:
        WikiItem();
        ~WikiItem();
        WikiItem(string s, WikiItem* n);
        void addDoc(WikiItem* article);

    private:
        string str;
        WikiItem* articles;
        WikiItem* next;
};

class WikiItemMap {
    public:
        WikiItemMap(int n);
        ~WikiItemMap();
        WikiItem get(string s);
        void add(WikiItem* new_item);
        int hash(string s);

    private:
        int numBuckets;
        WikiItem* buckets;
};


class Index5 {
public:
    Index5();
    void preprocess(string filename);
    void* search(string query);
private:
    WikiItemMap map;
};