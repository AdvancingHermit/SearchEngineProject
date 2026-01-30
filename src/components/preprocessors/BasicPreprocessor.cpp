#include "../../core/interfaces.h"

#include <fstream>

class BasicPreprocessor : public IPreprocessor {
public:
    ~BasicPreprocessor() override = default;
    void* preprocess(std::string filename, IStore* store) override;
};

void* BasicPreprocessor::preprocess(std::string filename, IStore *store) {
    std::ifstream file;
    file.open (filename);
    if (!file.good()) {
        printf("Error reading file");
        return nullptr;
    }
    if (!file.is_open()) {
        printf("No file is open");
        return nullptr;
    }

    Doc document{};
    std::string word;
    short take_next = 1;

    while (file >> word)
    {
        if (take_next) {
            document.title = word;
            document.start_loc = file.tellg();
        }

        store->add(word, document);

        take_next = word == END;
    }
    file.close();
    return nullptr;
}
