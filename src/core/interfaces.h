#include <string>
#include <vector>

class Doc {
public:
    std::string title;
    long loc;
};
class ScoredDoc : public Doc {
public:
    int score;
};

class IStore {
public:
    virtual ~IStore() = default;
    virtual add(Doc);
    virtual Doc get(string title);
};
class IPreprocessor {
public:
    virtual ~IPreprocessor() = default;
    virtual void* preprocess(string filename, IStore*);
};

class IHash {
public:
    virtual ~IHash() = default;
    virtual uint64_t hash(const std::string &key);
};

class ISearcher {
public:
    virtual ~ISearcher() = default;
    virtual std::vector<Doc> search(string * q, IStore*) = 0;
};

class IRanker {
public:
    virtual ~IRanker() = default;
    virtual std::vector<ScoredDoc> rank(const std::vector<Doc>* candidates, string query) = 0;
};