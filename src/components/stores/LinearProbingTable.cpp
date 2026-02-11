#include "../../core/interfaces.h"


struct entry {
    std::string word;
    std::vector<Doc> documents_in;
    int occupied = 0;
};


class LinearProbingTable : public IStore {
private:
    int numBuckets;
    std::vector<entry> buckets;
    IHash* hash_function;
    entry* get_entry(std::string word, entry* &lastEmpty);
public:
    LinearProbingTable(int n, IHash* hash_function);
    void add(std::string word, Doc document) override;
    std::vector<Doc>* get(std::string word) override;
};

entry* LinearProbingTable::get_entry(std::string word, entry* &lastEmpty) {
    std::uint64_t index = hash_function->hash(word, numBuckets) % numBuckets;

    for (int i = 0; i < numBuckets; i++) {
        std::uint64_t idx = (i + index) % numBuckets;

        if (buckets[idx].occupied == 0) {
            lastEmpty = &buckets[idx];
            return nullptr;
        }
        if (buckets[idx].word == word) {
            return &buckets[idx];
        }
    }
    return nullptr;
}

LinearProbingTable::LinearProbingTable(int n, IHash* hash_function) {
    numBuckets = n;
    buckets = std::vector<entry>(n);
    this->hash_function = hash_function;

}
void LinearProbingTable::add(std::string word, Doc document) {

    entry* lastEmpty;
    entry* lookUp = get_entry(word, lastEmpty);

    if (!lookUp) {
        lastEmpty->word = word;
        lastEmpty->documents_in.push_back(document);
        lastEmpty->occupied = 1;
    } else {
        //return if trying to add the same document again
        if (lookUp->documents_in[lookUp->documents_in.size() - 1].title == document.title) {
            return;
        }
        lookUp->documents_in.push_back(document);
    }

}


std::vector<Doc> *LinearProbingTable::get(std::string word) {
    entry* lastEmpty;
    entry* result = get_entry(word, lastEmpty);


    return  result ? &result->documents_in : nullptr;
}




