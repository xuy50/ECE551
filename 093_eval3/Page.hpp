#ifndef _PAGE_HPP_
#define _PAGE_HPP_

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

//using namespace std;

class page {
 private:
  size_t pageNum;
  std::string pageFileName;
  char pageType;
  std::vector<std::pair<size_t, std::string> > empty;
  bool visited;
  bool linked;
  std::map<std::string, long int> emptyBuff;
  std::vector<std::pair<std::string, long int> > seleReqEmpty;

 public:
  /*
   * default constructor
   */
  page() {}

  /*
   * page constructor
   */
  page(size_t _pageNum, std::string _pageFileName, char _pageType) :
      pageNum(_pageNum),
      pageFileName(_pageFileName),
      pageType(_pageType),
      visited(false),
      linked(false) {}

  /*
   * page copy constructor
   */
  page(const page & rhs) {
    //nextPages = rhs.nextPages;
    pageNum = rhs.pageNum;
    pageFileName = rhs.pageFileName;
    pageType = rhs.pageType;
  }

  /*
   * page operator assign = overload
   */
  virtual page & operator=(const page & rhs) {
    if (this != &rhs) {
      pageNum = rhs.pageNum;
      pageFileName = rhs.pageFileName;
      pageType = rhs.pageType;
    }
    return *this;
  }

  /*
   * page destructor
   */
  virtual ~page() {}

  /*
   * function to get page number
   */
  size_t getPageNum() const { return pageNum; }

  /*
   * function to get page type
   */
  char getType() const { return pageType; }

  /*
   * function to get the name of page file
   */
  std::string getPageFileName() const { return pageFileName; }

  /*
   * function to get whether the page has been visited
   */
  bool getVisited() const { return visited; }

  /*
   * function to get whether the page has been linked
   */
  bool getLinked() const { return linked; }

  /*
  * set values
  */
  void setPageNum(const size_t & nPageNum) { pageNum = nPageNum; }
  void setType(const char & nPageType) { pageType = nPageType; }
  void setPageFileName(const std::string & nPageFileName) {
    pageFileName = nPageFileName;
  }
  void setVisited(const bool v) { visited = v; }
  void setLinked(const bool l) { linked = l; }

  /*
   * function to get the vector of next pages selections of the page
   */
  virtual const std::vector<std::pair<size_t, std::string> > & getNextPages() {
    return empty;
  }

  /*
   * function to get the vector of buff selections of the page
   */
  virtual const std::map<std::string, long int> & getBuffs() { return emptyBuff; }

  /*
   * add next pages information
   */
  virtual void addNextPages(std::pair<size_t, std::string> oneNextPage) {}

  /*
   * add an buff into bufflist
   */
  virtual void addBuff(std::string buffName, long int buffVal) {}

  /*
  * get story ending information
  */
  virtual std::string getEnding() const { return ""; }

  // get each selections' buff needed status request
  virtual const std::vector<std::pair<std::string, long int> > & getSeleReq() {
    return seleReqEmpty;
  }

  // add selections' request for next page selection
  virtual void addSeleReq(std::string buffName, long int buffVal) {}
};

/*
 * N type page calss
 */
class nPage : public page {
 private:
  std::vector<std::pair<size_t, std::string> > nextPages;
  std::vector<std::pair<std::string, long int> > seleReq;
  std::map<std::string, long int> buffs;

 public:
  /*
  * copy constructor
  */
  nPage(size_t _pageNum, std::string _pageFileName, char _pageType) :
      page(_pageNum, _pageFileName, _pageType) {}

  /*
  * copy constructor
  */
  nPage(const nPage & rhs) : page(rhs) { nextPages = rhs.nextPages; }

  /*
  * operator assign =
  */
  virtual nPage & operator=(const nPage & rhs) {
    if (this != &rhs) {
      nextPages = rhs.nextPages;
      this->setPageNum(rhs.getPageNum());
      this->setType(rhs.getType());
      this->setPageFileName(rhs.getPageFileName());
    }
    return *this;
  }

  virtual ~nPage() {}

  // get the vector of the next pages
  virtual const std::vector<std::pair<size_t, std::string> > & getNextPages() {
    return this->nextPages;
  }

  // add next info into next page vector
  virtual void addNextPages(std::pair<size_t, std::string> oneNextPage) {
    nextPages.push_back(oneNextPage);
  }

  // get the vector of the buffs
  virtual const std::map<std::string, long int> & getBuffs() { return this->buffs; }

  // add next info into next buffs vector
  virtual void addBuff(std::string buffName, long int buffVal) {
    buffs[buffName] = buffVal;
  }

  // get each selections' buff needed status request
  virtual const std::vector<std::pair<std::string, long int> > & getSeleReq() {
    return seleReq;
  }

  // add selections' request for next page selection
  virtual void addSeleReq(std::string buffName, long int buffVal) {
    std::pair<std::string, long int> newReq(buffName, buffVal);
    this->seleReq.push_back(newReq);
  }
};

/*
 * W type page calss
 */
class wPage : public page {
 private:
  std::string hapEnding;

 public:
  wPage(size_t _pageNum, std::string _pageFileName, char _pageType) :
      page(_pageNum, _pageFileName, _pageType),
      hapEnding("Congratulations! You have won. Hooray!") {}

  /*
  * copy constructor
  */
  wPage(const wPage & rhs) :
      page(rhs), hapEnding("Congratulations! You have won. Hooray!") {}

  /*
  * operator assign =
  */
  virtual wPage & operator=(const wPage & rhs) {
    if (this != &rhs) {
      this->setPageNum(rhs.getPageNum());
      this->setType(rhs.getType());
      this->setPageFileName(rhs.getPageFileName());
      hapEnding = "Congratulations! You have won. Hooray!";
    }
    return *this;
  }

  virtual ~wPage() {}

  virtual std::string getEnding() const { return hapEnding; }
};

/*
 * L type page calss
 */
class lPage : public page {
 private:
  std::string badEnding;

 public:
  lPage(size_t _pageNum, std::string _pageFileName, char _pageType) :
      page(_pageNum, _pageFileName, _pageType),
      badEnding("Sorry, you have lost. Better luck next time!") {}

  /*
  * copy constructor
  */
  lPage(const lPage & rhs) :
      page(rhs), badEnding("Congratulations! You have won. Hooray!") {}

  /*
  * operator assign =
  */
  virtual lPage & operator=(const lPage & rhs) {
    if (this != &rhs) {
      this->setPageNum(rhs.getPageNum());
      this->setType(rhs.getType());
      this->setPageFileName(rhs.getPageFileName());
      badEnding = "Sorry, you have lost. Better luck next time!";
    }
    return *this;
  }

  virtual ~lPage() {}

  virtual std::string getEnding() const { return badEnding; }
};

// input invalid exception
class InvalidInput : std::exception {
 private:
  std::string errMsg;

 public:
  InvalidInput(std::string _errMsg) : errMsg(_errMsg) {}
  virtual ~InvalidInput() throw() {}
  virtual const char * what() const throw() { return errMsg.c_str(); }
};

// free all page in the pages vector
void freePages(std::vector<page *> pages);

// print out each pages selections or story ending
size_t printByPageType(page & pages);

// out all in the page file
size_t printPages(const std::string & path, page & pages);

// to get page number
size_t getPageNum(const std::string & pageNumStr);

// get next pages information
std::pair<size_t, std::string> nextPages(const std::string & nextPageNumStr,
                                         const std::string & nextPageStr);

// get the new page's type from string to char
char getNewPageType(const std::string & pageTypeStr);

// add new page into pages vector
// and add the ending into the page if it is w/l type page
void addIntoVec(std::vector<page *> & pages,
                size_t & pageNum,
                std::string & pageFileName,
                char & pageType);

// for each line in file, parse to key and assoc values
void parseLine(std::vector<page *> & pages,
               const std::string & line,
               const std::string & path);

// check all pages are linked with other page
void checkLinked(std::vector<page *> & pages);

// read and save information from story into pages.
void readStoryFile(std::vector<page *> & pages,
                   std::istream & story,
                   const std::string & path);

// print story by input
void printStoryByInput(const std::vector<page *> & pages, const std::string & path);

// find and print win path
void winPath(const std::vector<page *> & pages);

// print story by input with buffs
void printStoryByInputWBuff(const std::vector<page *> & pages, const std::string & path);

#endif
