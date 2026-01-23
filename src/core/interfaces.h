#include <cstdint>
#include <string>
#include <vector>

class Doc {
public:
    std::string title;
    long loc;
};
class ScoredDoc : public Doc {
public:
    int score{};
};

class IStore {
public:
    virtual ~IStore() = default;
    virtual void add(Doc);
    virtual Doc get(std::string title);
};
class IPreprocessor {
public:
    virtual ~IPreprocessor() = default;
    virtual void* preprocess(std::string filename, IStore*);
};

class IHash {
public:
    virtual ~IHash() = default;
    virtual std::uint64_t hash(const std::string &key);
};

class ISearcher {
public:
    virtual ~ISearcher() = default;
    virtual std::vector<Doc> search(std::string * q, IStore*);
};

class IRanker {
public:
    virtual ~IRanker() = default;
    virtual std::vector<ScoredDoc> rank(const std::vector<Doc>* candidates, std::string query);
};