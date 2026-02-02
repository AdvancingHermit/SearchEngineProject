#include "../../core/interfaces.h"
#include <unordered_set>

class BooleanSearcher : public ISearcher {
private:
    void Intersection(std::vector<Doc>* main, std::vector<Doc>* v, std::unordered_set<std::string>* mainSet);
    void Union(std::vector<Doc>* main, std::vector<Doc>* v, std::unordered_set<std::string>* mainSet);
    std::unordered_set<std::string> createDocSet(std::vector<Doc>* v);

public:
    ~BooleanSearcher() override = default;
    std::vector<Doc> search(SearchQuery q, IStore* store) override;
};

std::unordered_set<std::string> BooleanSearcher::createDocSet(std::vector<Doc>* v) {
    std::unordered_set<std::string> set;
    for (Doc& doc : *v) {
        set.insert(doc.title);
    }
    return set;
}


void BooleanSearcher::Intersection(std::vector<Doc>* main, std::vector<Doc>* v, std::unordered_set<std::string>* mainSet) {
    std::unordered_set<std::string> vSet = createDocSet(v);
    std::unordered_set<std::string> resultSet;
    for (auto& docName : *mainSet) {
        if (vSet.find(docName) != vSet.end()) { // element found (contained in both)
            resultSet.insert(docName);
        }
    }
    *mainSet = resultSet;
    std::vector<Doc> resultsDoc;
    for (Doc& doc : *main) {
        if (resultSet.find(doc.title) != resultSet.end()) { // element found (contained in both)
            resultsDoc.push_back(doc);
        }
    *main = resultsDoc;
    }


}
void BooleanSearcher::Union(std::vector<Doc>* main, std::vector<Doc>* v, std::unordered_set<std::string>* mainSet) {
    for (Doc& doc : *v) {
        if (mainSet->find(doc.title) == mainSet->end()) { //element not found
            main->push_back(doc);
            mainSet->insert(doc.title);
        }
    }


}



std::vector<Doc> BooleanSearcher::search(SearchQuery q, IStore* store) {
    if (!store) return {};
    printf("%lu",q.queries.size());
    std::vector<std::vector<Doc>> allDocs;
    for (auto& qu : q.queries) {
        std::vector<Doc>* tmp = store->get(qu);
        if (tmp) {
            allDocs.push_back(*tmp);
        }
    }

    std::vector<Doc> res = allDocs.back();
    allDocs.pop_back();
    std::unordered_set<std::string> resSet = createDocSet(&res);

    for (auto doc : allDocs) {
        q.mode == boolOperator::a ? Intersection(&res, &doc, &resSet) : Union(&res,&doc, &resSet);
    }

    return res;
}
