#include "Page.hpp"

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

//using namespace std;

// free all page in the pages vector
void freePages(std::vector<page *> pages) {
  typename std::vector<page *>::iterator itPages = pages.begin();
  for (; itPages != pages.end(); ++itPages) {
    delete (*itPages);
  }
}

// print out each pages selections or story ending
size_t printByPageType(page & pages) {
  size_t index = 0;
  if (pages.getType() == 'N') {
    std::cout << "\nWhat would you like to do?\n" << std::endl;

    // print out all selections
    std::vector<std::pair<size_t, std::string> > nextPages = pages.getNextPages();
    typename std::vector<std::pair<size_t, std::string> >::const_iterator itNPage =
        nextPages.begin();
    for (; itNPage != nextPages.end(); ++itNPage) {
      ++index;
      std::cout << " " << index << ". " << (*itNPage).second << std::endl;
    }
  }
  else if (pages.getType() == 'W' || pages.getType() == 'L') {
    std::cout << "\n" << pages.getEnding() << std::endl;
  }
  return index;
}

// print out all in the page file
size_t printPages(const std::string & path, page & pages) {
  // read file
  size_t index = 0;  // get the selections amount
  std::string pagePath = path + "/" + pages.getPageFileName();
  std::ifstream fPage(pagePath.c_str());
  if (!fPage.is_open()) {
    //throw InvalidInput("Cannot open the page file\n");
    std::cerr << "Cannot open the page file: " << pagePath << "\n" << std::endl;
    exit(EXIT_FAILURE);
  }

  // output by format
  //cout << "Page " << pages.getPageNum() << endl;
  //cout << "==========" << endl;

  // output each line
  std::string line;
  while (getline(fPage, line)) {
    std::cout << line << std::endl;
  }

  // print selections or story ending
  index = printByPageType(pages);

  fPage.close();

  return index;
}

// help check the string if it is a positive integer
bool checkInputPosInt(std::string inputSele) {
  if (inputSele.length() <= 0)
    return false;
  bool startSpace = true;
  for (size_t i = 0; i < inputSele.length(); i++) {
    // if nagetive return false
    if (startSpace == true && inputSele.at(i) == ' ') {
      if (i == (inputSele.length() - 1)) {
        return false;
      }
      continue;
    }
    startSpace = false;
    if (!isdigit(inputSele.at(i)) || inputSele.at(i) == ' ')
      return false;
  }
  return true;
}

// help check the string if it is a long integer
bool checkInputLongInt(std::string valStr) {
  if (valStr.length() <= 0)
    return false;
  bool startSpaNag = true;
  for (size_t i = 0; i < valStr.length(); i++) {
    // if first char is - countinue
    if (startSpaNag == true && valStr.at(i) == ' ') {
      if (i == (valStr.length() - 1)) {
        return false;
      }
      continue;
    }
    if (startSpaNag == true && valStr.at(i) == '-') {
      if (i == (valStr.length() - 1))
        return false;
      startSpaNag = false;
      continue;
    }
    startSpaNag = false;
    if (!isdigit(valStr.at(i)) || valStr.at(i) == ' ')
      return false;
  }
  return true;
}

// to get page number
long int getBuffVal(const std::string & buffValStr) {
  std::stringstream sstream(buffValStr);
  long int buffVal;
  sstream >> buffVal;
  return buffVal;
}

// to get page number
size_t getPageNum(const std::string & pageNumStr) {
  std::stringstream sstream(pageNumStr);
  size_t pageNum;
  sstream >> pageNum;
  return pageNum;
}

// get next pages information
std::pair<size_t, std::string> nextPages(const std::string & nextPageNumStr,
                                         const std::string & nextPageStr) {
  //get next page number (str to size_t)
  size_t nextPageNum = getPageNum(nextPageNumStr);
  std::pair<size_t, std::string> result(nextPageNum, nextPageStr);
  return result;
}

// get the new page's type from string to char
char getNewPageType(const std::string & pageTypeStr) {
  std::stringstream sstream(pageTypeStr);
  char pageType;
  sstream >> pageType;
  return pageType;
}

// add new page into pages vector
// and add the ending into the page if it is w/l type page
void addIntoVec(std::vector<page *> & pages,
                size_t & pageNum,
                std::string & pageFileName,
                char & pageType) {
  if (pageType == 'N') {
    nPage * newPage = new nPage(pageNum, pageFileName, pageType);
    pages.push_back(newPage);
  }
  else if (pageType == 'W') {
    wPage * newPage = new wPage(pageNum, pageFileName, pageType);
    pages.push_back(newPage);
  }
  else if (pageType == 'L') {
    lPage * newPage = new lPage(pageNum, pageFileName, pageType);
    pages.push_back(newPage);
  }
  else {
    page * newPage = new page(pageNum, pageFileName, pageType);
    pages.push_back(newPage);
  }
}

// parseLine help functions
// get the page index
size_t getPageIndex(size_t pageNum, const std::vector<page *> & pages) {
  typename std::vector<page *>::const_iterator itPages = pages.begin();
  size_t index = 0;
  for (; itPages != pages.end(); ++itPages, ++index) {
    if ((*itPages)->getPageNum() == pageNum)
      return index;
  }
  return index;
}

// check page file whether it is existed
void checkPageFile(const std::string & path, const std::string & nextPageName) {
  std::string filePath = path + nextPageName;
  std::ifstream ifNextPage(filePath.c_str());
  if (!ifNextPage.is_open()) {
    std::cerr << "Cannot find page file: " << filePath << ".\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  ifNextPage.close();
}

// parse colon line, parse the :: type line in the story.txt
void colonLineHelp(std::string pageNumStr,
                   std::string nextPageInfo,
                   std::vector<page *> & pages,
                   const std::string & path) {
  // try to find second :
  size_t delimColon2 = nextPageInfo.find(":");
  // if there is no second colon
  if (delimColon2 == std::string::npos) {
    //throw an exception
    //throw InvalidInput("Story file line format error(:).\n");
    std::cerr << "Story file line format error(:).\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  // get the next page introduce information
  if (!checkInputPosInt(pageNumStr)) {
    //throw an exception
    //throw InvalidInput("Story file line format error(:).\n");
    std::cerr << "Story file line format error(:).\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  size_t pageNum = getPageNum(pageNumStr);
  size_t pageInd = getPageIndex(pageNum, pages);
  if (pageInd >= pages.size()) {
    //throw InvalidInput("Do not have the page for the next page.\n");
    std::cerr << "Do not have the page for the next page.\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  // check if the page type is not N, it cannot have a next page
  else if ((*pages[pageInd]).getType() != 'N') {
    //throw InvalidInput("The page type is not N, it cannot have a next page.\n");
    std::cerr << "The page type is not N, it cannot have a next page.\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string nextPageNumStr = nextPageInfo.substr(0, delimColon2);
  if (!checkInputPosInt(nextPageNumStr)) {
    //throw InvalidInput("Story file line format error(:).\n");
    std::cerr << "Story file line format error(:).\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string nextPageStr = nextPageInfo.substr(delimColon2 + 1);
  std::pair<size_t, std::string> nextPage = nextPages(nextPageNumStr, nextPageStr);
  (*pages[pageInd]).addNextPages(nextPage);
  // add no require seletion require into require list
  (*pages[pageInd]).addSeleReq("NoRequire", 0);
}

// parse at line, parse the @ type line in the story.txt
void atLineHelp(size_t pageNum,
                std::string newPageInfo,
                std::vector<page *> & pages,
                const std::string & path) {
  char pageType = getNewPageType(newPageInfo.substr(0, 1));
  std::string pageFileName = newPageInfo.substr(2);
  checkPageFile(path, pageFileName);
  addIntoVec(pages, pageNum, pageFileName, pageType);
}

// parse dollar line, parse the $ type line in the story.txt
void dollarLineHelp(std::string line,
                    size_t delimDollar,
                    size_t delimEqual,
                    std::vector<page *> & pages) {
  std::string pageNumStr = line.substr(0, delimDollar);
  if (!checkInputPosInt(pageNumStr)) {
    std::cerr << "Story file line format error($).\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  size_t pageNum = getPageNum(pageNumStr);
  size_t pageInd = getPageIndex(pageNum, pages);
  if (pageInd >= pages.size()) {
    std::cerr << "Do not have the page for the next page($).\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string buffName = line.substr((delimDollar + 1), (delimEqual - delimDollar - 1));
  std::string buffValStr = line.substr(delimEqual + 1);
  if (!checkInputLongInt(buffValStr)) {
    std::cerr << "Buff value is not a valid long integer($).\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  long int buffVal = getBuffVal(buffValStr);
  pages[pageInd]->addBuff(buffName, buffVal);
  // print out test
  //std::cout << pageNum << "$" << buffName << "=" << buffVal << std::endl;
}

// parse bracket line, parse the [] type line in the story.txt
void bracketLineHelp(std::string line,
                     size_t delimBracketl,
                     size_t delimBracketr,
                     size_t delimEqual,
                     size_t delimColon1,
                     std::vector<page *> & pages) {
  std::string bLineInfo = line.substr(delimColon1 + 1);
  // check second colon
  size_t delimColon2 = bLineInfo.find(":");
  if (delimColon2 == std::string::npos) {
    std::cerr << "Story file line format error([]).\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  // check valid page number
  std::string pageNumStr = line.substr(0, delimBracketl);
  if (!checkInputPosInt(pageNumStr)) {
    std::cerr << "Story file line format error([]).\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  // get valid page number and index
  size_t pageNum = getPageNum(pageNumStr);
  size_t pageInd = getPageIndex(pageNum, pages);
  if (pageInd >= pages.size()) {
    std::cerr << "Do not have the page for the next page([]).\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  // check if the page type is not N, it cannot have a next page
  else if ((*pages[pageInd]).getType() != 'N') {
    std::cerr << "The page type is not N, it cannot have a next page.\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  // get next page number and buff value to check valid
  std::string nextPageNumStr = bLineInfo.substr(0, delimColon2);
  std::string buffValStr =
      line.substr((delimEqual + 1), (delimBracketr - delimEqual - 1));
  if ((!checkInputPosInt(nextPageNumStr)) || (!checkInputLongInt(buffValStr))) {
    std::cerr << "Story file line format error([]).\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  // get buff Name and Value
  std::string buffName =
      line.substr((delimBracketl + 1), (delimEqual - delimBracketl - 1));
  long int buffVal = getBuffVal(buffValStr);
  // get next page info
  std::string nextPageStr = bLineInfo.substr(delimColon2 + 1);
  std::pair<size_t, std::string> nextPage = nextPages(nextPageNumStr, nextPageStr);
  (*pages[pageInd]).addNextPages(nextPage);
  // add require seletion require into require list
  (*pages[pageInd]).addSeleReq(buffName, buffVal);
  // print out test
  //std::cout << pageNum << "[" << buffName << "=" << buffVal << "]:" << nextPageNumStr
  //<< ":" << nextPageStr << std::endl;
}

// help function to check line type
int lineTypeCheckHelp(size_t delimAt,
                      size_t delimColon1,
                      size_t delimBracketl,
                      size_t delimBracketr,
                      size_t delimDollar,
                      size_t delimEqual) {
  // check : type
  if (delimColon1 != std::string::npos && delimAt > delimColon1 &&
      delimDollar > delimColon1 && delimBracketl > delimColon1 &&
      delimBracketr > delimColon1 && delimEqual > delimColon1) {
    return 1;
  }
  // check @ type
  else if (delimAt != std::string::npos && delimColon1 != std::string::npos &&
           delimAt < delimColon1 && delimAt < delimDollar && delimAt < delimBracketl &&
           delimAt < delimBracketr && delimAt < delimEqual) {
    return 2;
  }
  // check $ type
  else if (delimDollar != std::string::npos && delimEqual != std::string::npos &&
           delimDollar < delimAt && delimDollar < delimColon1 &&
           delimDollar < delimBracketl && delimDollar < delimBracketr &&
           delimDollar < delimEqual) {
    return 3;
  }
  // check [] type
  else if ((delimBracketl != std::string::npos && delimBracketr != std::string::npos &&
            delimEqual != std::string::npos && delimColon1 != std::string::npos) &&
           (delimAt > delimBracketl && delimColon1 == (delimBracketr + 1) &&
            (delimEqual > delimBracketl && delimEqual < delimBracketr))) {
    return 4;
  }
  else {
    throw InvalidInput("Story file line format error.\n");
  }
  return 0;
}

// for each line in file, parse to key and assoc values
void parseLine(std::vector<page *> & pages,
               const std::string & line,
               const std::string & path) {
  if (line != "") {
    // check first at and collon sign
    size_t delimAt = line.find("@");
    size_t delimColon1 = line.find(":");
    size_t delimBracketl = line.find("[");
    size_t delimBracketr = line.find("]");
    size_t delimDollar = line.find("$");
    size_t delimEqual = line.find("=");

    int lineType = lineTypeCheckHelp(
        delimAt, delimColon1, delimBracketl, delimBracketr, delimDollar, delimEqual);
    // check : type line
    if (lineType == 1) {
      // if there is no colon
      if (delimColon1 == std::string::npos) {
        //throw an exception
        throw InvalidInput("Story file line format error(:).\n");
      }
      else {
        // get the substr after the first colon
        std::string pageNumStr = line.substr(0, delimColon1);
        if (!checkInputPosInt(pageNumStr)) {
          throw InvalidInput("Story file line format error(:).\n");
        }
        std::string nextPageInfo = line.substr(delimColon1 + 1);
        colonLineHelp(pageNumStr, nextPageInfo, pages, path);
        return;
      }
    }
    // check @ type line
    else if (lineType == 2) {
      // check if the only have @ without :
      if (delimColon1 == std::string::npos) {
        //throw an exception
        throw InvalidInput("Story file line format error(@).\n");
      }
      // check if the page type only have one letter and only n/w/l tpyes
      char pageType = line[delimAt + 1];
      if ((delimColon1 - delimAt) != 2 ||
          (pageType != 'N' && pageType != 'W' && pageType != 'L')) {
        //throw an exception
        throw InvalidInput("Story file line format error(page type).\n");
      }
      else {
        std::string pageNumStr = line.substr(0, delimAt);
        if (!checkInputPosInt(pageNumStr)) {
          throw InvalidInput("Story file line format error(@).\n");
        }

        size_t pageNum = getPageNum(pageNumStr);

        // check first page is page0
        if (pages.size() == 0 && pageNum != 0) {
          throw InvalidInput("Story file line format error(@)(no page 0).\n");
        }
        // check all pages are continuous
        if (getPageIndex(pageNum, pages) < pages.size() ||
            (pageNum != 0 && pageNum != (pages.back()->getPageNum() + 1))) {
          throw InvalidInput("Page number error(@).(pages number is not continuous)\n");
        }
        std::string newPageInfo = line.substr(delimAt + 1);
        atLineHelp(pageNum, newPageInfo, pages, path);
      }
    }
    // check $ tpye line
    else if (lineType == 3) {
      dollarLineHelp(line, delimDollar, delimEqual, pages);
    }
    // check [] type line
    else if (lineType == 4) {
      bracketLineHelp(line, delimBracketl, delimBracketr, delimEqual, delimColon1, pages);
    }
    else {
      throw InvalidInput("Story file line format error.\n");
    }
  }
}

// help check and set all page for linked
void linkedCheckSet(std::vector<page *> & pages) {
  typename std::vector<page *>::const_iterator itPages = pages.begin();
  for (; itPages != pages.end(); ++itPages) {
    // set 0 page to linked
    if ((*itPages)->getPageNum() == 0) {
      (*itPages)->setLinked(true);
    }
    if ((*itPages)->getType() != 'N') {
      //(*itPages)->setLinked(true);
      continue;
    }
    // set all next pages linked to true
    std::vector<std::pair<size_t, std::string> > nextPages = (*itPages)->getNextPages();
    typename std::vector<std::pair<size_t, std::string> >::const_iterator itNP =
        nextPages.begin();
    for (; itNP != nextPages.end(); ++itNP) {
      if ((*itNP).first != (*itPages)->getPageNum()) {
        size_t nextPageInd = getPageIndex((*itNP).first, pages);
        //check whether the next page is existed
        if (nextPageInd >= pages.size()) {
          std::cerr << "Cannot find page " << (*itNP).first << "." << std::endl;
          exit(EXIT_FAILURE);
        }
        pages[nextPageInd]->setLinked(true);
      }
    }
  }
}

// check all pages are linked with other page
void checkLinked(std::vector<page *> & pages) {
  // check and set all pages linked
  linkedCheckSet(pages);

  // check all page if any one did not linked return false
  typename std::vector<page *>::const_iterator itPages = pages.begin();
  for (; itPages != pages.end(); ++itPages) {
    if (!(*itPages)->getLinked()) {
      //return false;
      std::cerr << "page:" << (*itPages)->getPageNum() << " no other page reference(s)."
                << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  //return true;
}

// read and save information from story into pages.
void readStoryFile(std::vector<page *> & pages,
                   std::istream & story,
                   const std::string & path) {
  std::string line;
  while (getline(story, line)) {
    try {
      parseLine(pages, line, path);
    }
    catch (InvalidInput & e) {
      std::cerr << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

// get an invalid positive integer input for next page selection
size_t inputNextIndexHelp(size_t nextPageCho) {
  size_t seleIndex = 1;
  std::string inputSele;
  bool invalidInputCheck = false;

  do {
    invalidInputCheck = false;
    getline(std::cin, inputSele);

    // if the input is positive integer check whether it in the range
    // else the input is not invalid
    if (checkInputPosInt(inputSele)) {
      std::stringstream ssSeleInd;
      ssSeleInd << inputSele;
      ssSeleInd >> seleIndex;
      if (seleIndex < 1 || seleIndex > nextPageCho)
        invalidInputCheck = true;
    }
    else {
      invalidInputCheck = true;
    }
    // if the input is not invalid output the message
    if (invalidInputCheck) {
      std::cout << "That is not a valid choice, please try again" << std::endl;
    }

  } while (invalidInputCheck);

  return --seleIndex;
}

// check whether the story has at least one win page and lose page
bool checkWLPage(const std::vector<page *> & pages) {
  bool wCheck = false;
  bool lCheck = false;

  typename std::vector<page *>::const_iterator itPages = pages.begin();

  for (; itPages != pages.end(); ++itPages) {
    if ((*itPages)->getType() == 'W') {
      wCheck = true;
    }
    else if ((*itPages)->getType() == 'L') {
      lCheck = true;
    }
  }

  return (wCheck && lCheck);
}

// check whether the story has at least one win page
bool checkWPage(const std::vector<page *> & pages) {
  typename std::vector<page *>::const_iterator itPages = pages.begin();
  for (; itPages != pages.end(); ++itPages) {
    if ((*itPages)->getType() == 'W') {
      return true;
    }
  }
  return false;
}

// print story by input
void printStoryByInput(const std::vector<page *> & pages, const std::string & path) {
  // check if the story has at least one win page and one lose page
  if (!checkWLPage(pages)) {
    std::cerr << "Story cannot find at least one win and one lost pages.\n" << std::endl;
    exit(EXIT_FAILURE);
  }

  // if the curr page type is N which means it have nextpage selection(s)
  // else if the type is W/L means get ending
  size_t nextPageInd = 0;
  char currPageType = (*pages[nextPageInd]).getType();
  while (currPageType == 'N') {
    // print curr page and get invlid selection number
    if ((*pages[nextPageInd]).getNextPages().size() < 1) {
      std::cerr << "Cannot find any next page.\n" << std::endl;
      exit(EXIT_FAILURE);
    }
    size_t nextPageCho = printPages(path, (*pages[nextPageInd]));
    size_t nextPageSele = inputNextIndexHelp(nextPageCho);
    // get next page num
    size_t nextPageNum = (*pages[nextPageInd]).getNextPages()[nextPageSele].first;
    // get next page index
    nextPageInd = getPageIndex(nextPageNum, pages);
    if (nextPageInd >= pages.size()) {
      //throw InvalidInput("Story page cannot be found when read pages.\n");
      std::cerr << "Story page cannot be found when read pages.\n" << std::endl;
      exit(EXIT_FAILURE);
    }
    // go to next page and get next page type
    currPageType = (*pages[nextPageInd]).getType();
    std::cout /*<< "\n\n"*/ << std::endl;
  }

  // print story ending
  printPages(path, (*pages[nextPageInd]));
}

// print win path
void printWinPath(const std::vector<std::pair<size_t, int> > & path) {
  typename std::vector<std::pair<size_t, int> >::const_iterator itPath = path.begin();
  for (; itPath != path.end(); ++itPath) {
    if ((*itPath).second == -1)
      std::cout << (*itPath).first << "(win)" << std::endl;
    else
      std::cout << (*itPath).first << "(" << (*itPath).second << "),";
  }
}

// find win path and call print function to print the path
void findWinPath(const std::vector<page *> & pages,
                 const size_t currPageNum,
                 std::vector<std::pair<size_t, int> > & wPath,
                 bool & winCheck) {
  // get curr page's index in the pages vector
  size_t currPageInd = getPageIndex(currPageNum, pages);
  // if the curr page is visited go back
  if (pages[currPageInd]->getVisited())
    return;
  // if the curr page is w page, print
  if (pages[currPageInd]->getType() == 'W') {
    winCheck = true;
    std::pair<size_t, int> p(currPageNum, -1);
    wPath.push_back(p);
    printWinPath(wPath);
    wPath.pop_back();
    return;
  }
  // if the curr page is l page, go back
  if (pages[currPageInd]->getType() == 'L')
    return;

  // if the page is n type and did not be visited set it to visited
  pages[currPageInd]->setVisited(true);

  // use recursion to check all next page
  std::vector<std::pair<size_t, std::string> > nextPages =
      pages[currPageInd]->getNextPages();
  typename std::vector<std::pair<size_t, std::string> >::const_iterator itNP =
      nextPages.begin();
  int index = 1;
  for (; itNP != nextPages.end(); ++itNP, ++index) {
    std::pair<size_t, int> p(currPageNum, index);
    // put the curr page into the page vector
    wPath.push_back(p);
    findWinPath(pages, (*itNP).first, wPath, winCheck);
    // pop the curr page for next time use
    wPath.pop_back();
  }

  // before track back make vistied false;
  pages[currPageInd]->setVisited(false);
}

// find and print win path
void winPath(const std::vector<page *> & pages) {
  // check if the story has at least one win page and one lose page
  if (!checkWLPage(pages)) {
    std::cerr << "Story cannot find at least one win and one lost pages.\n" << std::endl;
    exit(EXIT_FAILURE);
  }

  // check whether it can arrive win page
  bool winCheck = false;
  std::vector<std::pair<size_t, int> > wPath;

  // try to find win path
  findWinPath(pages, 0, wPath, winCheck);
  // if cannot find a win page give a massage
  if (!winCheck)
    std::cout << "This story is unwinnable!" << std::endl;
}

// help check buff with bufflist
bool checkBuffInList(const std::pair<std::string, long int> & buffReq,
                     const std::map<std::string, long int> & buffs) {
  // try to find buff in buff list
  typename std::map<std::string, long int>::const_iterator itBuff = buffs.begin();
  //try to find buff in buff list
  for (; itBuff != buffs.end(); ++itBuff) {
    // if find the buff, check the buff's value, if match return true, else return false
    if (buffReq.first == (*itBuff).first) {
      if (buffReq.second == (*itBuff).second) {
        return true;
      }
      else {
        return false;
      }
    }
  }

  // if cannot find the buff in the buff list but the reqirement is 0, return true
  if (buffReq.second == 0)
    return true;

  return false;
}

// print out each N type page selections
size_t printChoWithBuff(page & pages,
                        std::vector<bool> & buffsBool,
                        const std::map<std::string, long int> & buffs) {
  size_t index = 0;
  std::cout << "\nWhat would you like to do?\n" << std::endl;

  // print out all selections with buffs
  std::vector<std::pair<size_t, std::string> > nextPages = pages.getNextPages();
  std::vector<std::pair<std::string, long int> > seleReq = pages.getSeleReq();

  // check whether the requirements are matched with nextpages amount
  if (nextPages.size() != seleReq.size()) {
    std::cerr << "Selections and requirements are not match." << std::endl;
    exit(EXIT_FAILURE);
  }

  // iterate all next page and its own requirement to check the selection
  // with buffs, and print out all available selections
  typename std::vector<std::pair<size_t, std::string> >::const_iterator itNP =
      nextPages.begin();
  typename std::vector<std::pair<std::string, long int> >::iterator itReq =
      seleReq.begin();
  for (; itNP != nextPages.end(); ++itNP, ++itReq) {
    ++index;
    if (checkBuffInList((*itReq), buffs)) {
      buffsBool.push_back(true);
      std::cout << " " << index << ". " << (*itNP).second << std::endl;
    }
    else {
      buffsBool.push_back(false);
      std::cout << " " << index << ". <UNAVAILABLE>" << std::endl;
    }
  }
  return index;
}

// print out N type page in the page file with buffs
size_t printPagesWithBuff(const std::string & path,
                          page & pages,
                          std::vector<bool> & buffsBool,
                          const std::map<std::string, long int> & buffs) {
  // read file
  size_t index = 0;  // get the selections amount
  std::string pagePath = path + "/" + pages.getPageFileName();
  std::ifstream fPage(pagePath.c_str());
  if (!fPage.is_open()) {
    //throw InvalidInput("Cannot open the page file\n");
    std::cerr << "Cannot open the page file: " << pagePath << "\n" << std::endl;
    exit(EXIT_FAILURE);
  }

  // output each line
  std::string line;
  while (getline(fPage, line)) {
    std::cout << line << std::endl;
  }

  // print selections or story ending
  index = printChoWithBuff(pages, buffsBool, buffs);

  fPage.close();
  return index;
}

// get an invalid positive integer input for next page selection with buff
size_t inputNextIndexHelpBuff(size_t nextPageCho, std::vector<bool> & buffs) {
  size_t seleIndex = 1;
  std::string inputSele;
  bool invalidInputCheck = false;
  bool avaCheck = false;

  do {
    avaCheck = false;
    invalidInputCheck = false;
    getline(std::cin, inputSele);

    // if the input is positive integer check whether it in the range
    // else the input is not invalid
    if (checkInputPosInt(inputSele)) {
      std::stringstream ssSeleInd;
      ssSeleInd << inputSele;
      ssSeleInd >> seleIndex;
      if (seleIndex < 1 || seleIndex > nextPageCho) {
        invalidInputCheck = true;
      }
      else {
        // if the input number is valid, check if it is an available selection,
        // if no print a error message and let player input again, else return
        // next page's index.
        if (!buffs[seleIndex - 1]) {
          std::cout << "That choice is not available at this time, please try again"
                    << std::endl;
        }
        else {
          avaCheck = true;
        }
      }
    }
    else {
      invalidInputCheck = true;
    }
    // if the input is not invalid output the message
    if (invalidInputCheck) {
      std::cout << "That is not a valid choice, please try again" << std::endl;
    }

  } while (invalidInputCheck || !avaCheck);

  return --seleIndex;
}

// add page buffs into buff list
void addBuff(std::map<std::string, long int> & buffStatus,
             const std::map<std::string, long int> & buffs) {
  typename std::map<std::string, long int>::const_iterator itBuff = buffs.begin();
  for (; itBuff != buffs.end(); ++itBuff) {
    buffStatus[(*itBuff).first] = (*itBuff).second;
  }
}

// print story by input with buffs
void printStoryByInputWBuff(const std::vector<page *> & pages, const std::string & path) {
  // check if the story has at least one win page and one lose page
  if (!checkWLPage(pages)) {
    std::cerr << "Story cannot find at least one win and one lost pages.\n" << std::endl;
    exit(EXIT_FAILURE);
  }

  // save all buff player get
  std::map<std::string, long int> buffStatus;
  // if the curr page type is N which means it have nextpage selection(s)
  // else if the type is W/L means get ending
  size_t nextPageInd = 0;
  char currPageType = (*pages[nextPageInd]).getType();
  while (currPageType == 'N') {
    // print curr page and get invlid selection number
    if ((*pages[nextPageInd]).getNextPages().size() < 1) {
      std::cerr << "Cannot find any next page.\n" << std::endl;
      exit(EXIT_FAILURE);
    }
    // add all of the buff in current page to buff list
    addBuff(buffStatus, (*pages[nextPageInd]).getBuffs());
    // the vector is a help vector for check each selection's availability
    std::vector<bool> buffsBool;
    size_t nextPageCho =
        printPagesWithBuff(path, (*pages[nextPageInd]), buffsBool, buffStatus);
    size_t nextPageSele = inputNextIndexHelpBuff(nextPageCho, buffsBool);
    // get next page num
    size_t nextPageNum = (*pages[nextPageInd]).getNextPages()[nextPageSele].first;
    // get next page index
    nextPageInd = getPageIndex(nextPageNum, pages);
    if (nextPageInd >= pages.size()) {
      //throw InvalidInput("Story page cannot be found when read pages.\n");
      std::cerr << "Story page cannot be found when read pages.\n" << std::endl;
      exit(EXIT_FAILURE);
    }
    // go to next page and get next page type
    currPageType = (*pages[nextPageInd]).getType();
    std::cout /*<< "\n\n"*/ << std::endl;
  }

  // print story ending
  printPages(path, (*pages[nextPageInd]));
}
