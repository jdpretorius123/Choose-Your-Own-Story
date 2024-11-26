#include <ctype.h>
#include <errno.h>

#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// PAGE CLASS
class Page {
  size_t pagenum;
  std::string pagetype;
  std::string file;
  std::vector<std::string> text;
  std::string closing;
  std::vector<std::string> choices;
  std::vector<size_t> destpages;
  std::map<int, std::pair<std::string, long int> > conditions;

 public:
  Page();
  Page(size_t pagenum,
       std::string pagetype,
       std::string file,
       std::vector<std::string> text,
       std::string closing,
       std::vector<std::string> choices,
       std::vector<size_t> destpages);
  ~Page();
  std::string & getClosing();
  const std::string & getClosing() const;
  std::string & getPagetype();
  const std::string & getPagetype() const;
  std::vector<std::string> & getText();
  const std::vector<std::string> & getText() const;
  std::string & getFile();
  const std::string & getFile() const;
  size_t & getPagenum();
  const size_t & getPagenum() const;
  std::vector<std::string> & getChoices();
  const std::vector<std::string> & getChoices() const;
  std::vector<size_t> & getDestpages();
  const std::vector<size_t> & getDestpages() const;
  std::string toString() const;
  std::map<int, std::pair<std::string, long int> > & getConditions();
  const std::map<int, std::pair<std::string, long int> > & getConditions() const;
  void setConditions(std::map<int, std::pair<std::string, long int> > & conds);
  bool doesMatchExist(std::map<std::string, long int> & memory,
                      std::string & var,
                      long int val) const;
  std::vector<std::string> process(std::map<std::string, long int> & memory) const;
  std::vector<std::string> processChoices(std::map<std::string, long int> & memory) const;
  std::set<size_t> getInvalidChoices(std::map<std::string, long int> & memory) const;
  std::string toStringCond(std::map<std::string, long int> & memory) const;
};

// STORY CLASS
class Story {
  std::map<size_t, Page *> pages;
  std::vector<std::string> vars;
  std::map<std::string, long int> memory;

 public:
  Story();
  Story(std::map<size_t, Page *> pages);
  ~Story();
  std::map<size_t, Page *> & getPages();
  const std::map<size_t, Page *> & getPages() const;
  Page * getPage(size_t pagenum);
  size_t size();
  std::set<size_t> getPagetypes(std::string & pagetype);
  std::vector<std::string> & getVars();
  const std::vector<std::string> & getVars() const;
  void setVars(std::vector<std::string> & v);
  std::vector<std::string> filterVars(size_t pagenum);
  std::string parseVar(std::string & str);
  long int parseVal(std::string & str);
  void buildMemory();
  void updateMemory(size_t pagenum);
  std::map<std::string, long int> & getMemory();
  const std::map<std::string, long int> & getMemory() const;
};

// ERROR HANDLING
void checkPath(std::string & path);
void checkNumArgs(int numArgs);
void checkInfile(const std::ifstream & infile, std::string & file);
int checkPagenum(std::string & str);
int checkFormat(std::string & str, std::string & substr);
int checkDeclaration(std::string & str);
int charCount(std::string & str, char c);
int checkChoice(std::string & str);
void checkMalloc(Page * page);
void checkPageSeq(std::vector<std::string> & declarations);
void checkDups(std::vector<std::string> & lines);
void checkOrder(std::string & str, std::set<size_t> & logged, bool flag);
void checkStoryFile(std::vector<std::string> & lines);
std::set<size_t> findNormalpages(std::vector<std::string> & lines);
void checkMembership(std::set<size_t> & members, std::vector<std::string> & candidates);
void checkEndPages(std::pair<std::vector<std::string>, std::vector<std::string> > & data);
std::set<size_t> addDestpages(std::set<size_t> & members,
                              std::vector<size_t> & candidates);
void helpInvalidRefs(std::map<size_t, Page *> & pages, std::set<size_t> & references);
void checkInvalidRefs(Story * story);
void helpMissingRefs(std::map<size_t, Page *> & pages, std::set<size_t> & references);
void checkMisingRefs(Story * story);
void checkNumEndPages(Story * story);
void checkStory(Story * story);
int checkVarValue(std::string & str);
int checkVarDeclaration(std::string & str);
int checkCondChoice(std::string & str);
void checkCondStory(std::vector<std::string> & lines);

// PROCESS INPUT
std::string checkDir(char * dir);
std::string buildPath(char * dir, std::string & file);
std::string getPath(int numArgs, char ** inputs, std::string & file);
std::vector<std::string> readInfile(std::string & path, std::string & file, bool flag);
std::pair<std::vector<std::string>, std::vector<std::string> > parseStoryFile(
    std::vector<std::string> & lines);
size_t getPagenum(std::string & str);
std::string getPagetype(std::string & str);
std::string getFile(std::string & str);
std::string createClosing(std::string & pagetype);
std::vector<std::string> parseChoices(std::vector<std::string> & choices, size_t pagenum);
std::vector<size_t> parseDestpages(std::vector<std::string> & choices);
std::vector<std::string> parseChoiceText(std::vector<std::string> & choices);
Page * matchChoices(size_t pagenum,
                    std::string & pagetype,
                    std::string & file,
                    std::vector<std::string> & text,
                    std::string & closing,
                    std::vector<std::string> & choices);
Page * buildPage(char * dir,
                 std::string & declaration,
                 std::vector<std::string> & choices);
std::map<size_t, Page *> buildPages(char * dir,
                                    std::vector<std::string> & declarations,
                                    std::vector<std::string> & choices);
Story * buildStory(int argc, char ** argv);
void printStory(Story * story);
void initStory(Story * story);
void playStory(Story * story);
int getFrequency(std::vector<size_t> & currentPath, size_t currentNode);
std::map<int, std::vector<size_t> > dfs(Story * story, size_t from, size_t to);
std::map<int, std::map<int, std::vector<size_t> > > runDFS(Story * story);
size_t getChoiceNum(Page * page, size_t destpage);
void printPath(Story * story, std::vector<size_t> & pages);
void printPagePaths(Story * story, std::map<int, std::vector<size_t> > & paths);
bool doesPathExit(std::map<int, std::map<int, std::vector<size_t> > > & allPaths);
void printAllPaths(Story * story);
std::vector<std::string> readCondFile(std::string & path, std::string & file, bool flag);
void checkParsing(std::map<std::string, std::vector<std::string> > & data);
std::map<std::string, std::vector<std::string> > parseCondStory(
    std::vector<std::string> & lines);
std::string getVariable(std::string & str, std::string & substr);
long int getValue(std::string & str);
std::map<int, std::pair<std::string, long int> > parseConditions(
    std::vector<std::string> & choices);
Page * matchCondChoices(size_t pagenum,
                        std::string & pagetype,
                        std::string & file,
                        std::vector<std::string> & text,
                        std::string & closing,
                        std::vector<std::string> & choices);
std::map<size_t, Page *> buildCondPages(char * dir,
                                        std::vector<std::string> & declarations,
                                        std::vector<std::string> & choices);
Story * buildCondStory(int argc, char ** argv);
void playCondStory(Story * story);
