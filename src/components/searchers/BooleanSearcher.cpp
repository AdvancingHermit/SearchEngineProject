#include "../../core/interfaces.h"

class BooleanSearcher : public ISearcher {
private:
    std::vector<Doc> Intersection(std::vector<Doc> v1, std::vector<Doc> v2);
    std::vector<Doc> Union(std::vector<Doc> v1, std::vector<Doc> v2);

public:
    ~BooleanSearcher() override = default;
    std::vector<Doc> search(SearchQuery q, IStore* store) override;
};

std::vector<Doc> Intersection(std::vector<Doc> v1, std::vector<Doc> v2) {

}

std::vector<Doc> BooleanSearcher::search(SearchQuery q, IStore* store) {
    if (!store) return {};
    std::vector<std::vector<Doc>*> allDocs;
    for (std::string qu : q.queries) {
       allDocs.push_back(store->get(qu));
    }
    std::vector<Doc>* res = allDocs.back();

    return docs == nullptr ? std::vector<Doc>{} : *docs;
}
