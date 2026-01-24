#include "../../core/interfaces.h"


class BasicSearcher : public ISearcher {
public:
    ~BasicSearcher() override = default;
    std::vector<Doc> search(std::string q, IStore* store) override;
};

std::vector<Doc> BasicSearcher::search(std::string q, IStore *store) {
    return *store->get(q);
}
