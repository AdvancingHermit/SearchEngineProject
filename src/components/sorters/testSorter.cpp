#include "MergeSort.cpp"
#include "../../core/interfaces.h"
#include <iostream>

int main() {
  std::vector<ScoredDoc> docs(5);
  docs[0].title = "abe";
  docs[0].score = 10;
  docs[1].title = "kat";
  docs[1].score = 2;
  docs[2].title = "lak";
  docs[2].score = 20;
  docs[3].title = "kak";
  docs[3].score = 5;
  docs[4].title = "sak";
  docs[4].score = 3;

  docs = MergeSort(docs);

  for (int i = 0; i < docs.size(); i++) {
    std::cout << docs[i].title << " " << docs[i].score << "\n";

  }
  return 0;
}