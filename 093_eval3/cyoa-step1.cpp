#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "Page.hpp"

//using namespace std;

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage: direction path\n";
    return EXIT_FAILURE;
  }

  // get the direction path
  std::string dirName = argv[1];
  std::string path = dirName + "/";
  std::string storyPath = path + "story.txt";

  std::ifstream ifStory(storyPath.c_str());
  if (!ifStory.is_open()) {
    std::cerr << "File could not be opened\n";
    return EXIT_FAILURE;
  }
  std::vector<page *> pages;
  readStoryFile(pages, ifStory, path);

  ifStory.close();

  // read all pages in the vector
  typename std::vector<page *>::iterator itPages = pages.begin();
  for (; itPages != pages.end(); ++itPages) {
    try {
      std::cout << "Page " << (*itPages)->getPageNum() << std::endl;
      std::cout << "==========" << std::endl;
      printPages(path, **itPages);
    }
    catch (const InvalidInput & e) {
      std::cerr << e.what() << std::endl;
    }
  }

  freePages(pages);

  return EXIT_SUCCESS;
}
