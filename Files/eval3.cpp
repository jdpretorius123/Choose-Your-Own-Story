/*
This program plays a Choose-Your-Own-Adventure.

Classes
-------
Page:
  A class to represent a story page.

      Attributes
      ----------
      size_t pagenum: page number
      std::string pagetype: page type defined as Normal (N), Win (W), or Lose (L)
      std::string file: name of file with text displayed for page
      std::vector<std::string> text: text displayed for page
      std::string closing: text displayed for end of page
      std::vector<std::string> choices: choices displayed for page
      std::vector<size_t> destpages: destination pages for choices of page
      std::vector<int, std::pair<std::string, long int> > conditions: conditional choices for page

      Methods
      -------
      Page();
        - Default class constructor

      Page(pagenum, pagetype, file, text, closing, choices, destpages);
        - Optional class constructor

      ~Page();
        - Default class destructor

      std::string & getClosing();
      const std::string & getClosing() const;
        - Return closing text for page

      std::string & getPagetype();
      const std::string & getPagetype() const;
        - Return page type for page

      std::vector<std::string> & getText();
      const std::vector<std::string> & getText() const;
        - Return text displayed for page

      std::string & getFile();
      const std::string & getFile() const;
        - Return name of file for page

      size_t & getPagenum();
      const size_t & getPagenum() const;
        - Return page number for page

      std::vector<std::string> & getChoices();
      const std::vector<std::string> & getChoices() const;
        - Return choices displayed for page

      std::vector<size_t> & getDestpages();
      const std::vector<size_t> & getDestpages() const;
        - Return destination pages displayed for page

      std::string toString() const;
        - Convert contents for page to std::string

      std::map<int, std::pair<std::string, long int> > & getConditions();
      const std::map<int, std::pair<std::string, long int> > & getConditions() const;
        - Return conditional choices for page
        - int: choice number
        - std::string: variable
        - long int: variable value

      void setConditions(std::map<int, std::pair<std::string, long int> > & conds);
        - Set conditional choices for page

      bool doesMatchExist(std::map<std::string, long int> & memory,
                        std::string & var,
                        long int val) const;
        - Determines match among set variables and their current values among conditional choices for page
          at time in adventure

        Arguments
        ---------
          - std::map<std::string, long int> & memory:
            - variables and their current values at time in adventure
          - std::string & var:
            - variable of conditional choice for page
          - long int val:
            - value of variable of conditional choice for page

        Return
        ------
          - indicates match for set variables and their current values among conditional choices for page
            at time in adventure

      std::vector<std::string> process(std::map<std::string, long int> & memory) const;
      - Processes choices for page by selecting those displayed normally versus <UNAVAILABLE>

        Arguments
        ---------
          - std::map<std::string, long int> & memory:
            - variables and their current values at time in adventure

        Return
        ------
          - processed choices displayed for page

      std::vector<std::string> processChoices(std::map<std::string, long int> & memory) const;
      - Wrapper function for std::vector<std::string> process(std::map<std::string, long int> & memory) const;

        Arguments
        ---------
          - std::map<std::string, long int> & memory:
            - variables and their current values at time in adventure

        Return
        ------
          - processed choices displayed for page

      std::set<size_t> getInvalidChoices(std::map<std::string, long int> & memory) const;
      - Indicates which choices for page will display as <UNAVAILABLE> and cannot be selected

        Arguments
        ---------
          - std::map<std::string, long int> & memory:
            - variables and their current values at time in adventure

        Return
        ------
          - numbers for choices for page that will display as <UNAVAILABLE>

      std::string toStringCond(std::map<std::string, long int> & memory) const;
      - Convert contents for page to std::string for story with conditional choices

Story:
  A class to represent a Choose-Your-Own-Adventure.

      Attributes
      ----------
      std::map<size_t, Page *> pages: Page(s) of story
      std::vector<std::string> vars: variable declarations for story
      std::map<std::string, long int> memory: variables and their current values at time in adventure

      Methods
      -------
      Story();
        - Default class constructor

      Story(pages);
        - Optional class constructor

      ~Story();
        - Default class destructor

      std::map<size_t, Page *> & getPages();
      const std::map<size_t, Page *> & getPages() const;
        - Return pages for story
        - size_t: page number
        - Page *: pointer to instance of Page class

      Page * getPage(size_t pagenum);
        - Return instance of Page class for size_t pagenum

      size_t size();
        - Return number of pages in story

      std::vector<std::string> & getVars();
      const std::vector<std::string> & getVars() const;
        - Return variable declarations for story

      void setVars(std::vector<std::string> & v);
        - Set variable declarations for story

      std::vector<std::string> filterVars(size_t pagenum);
        - Return variable declarations for size_t pagenum

      std::string parseVar(std::string & str);
        - Return std::string variable in variable declaration str

      long int parseVal(std::string & str);
        - Return long int value in variable declaration str

      void buildMemory();
        - Sets value of all story variables to zero

      void updateMemory(size_t pagenum);
        - Set variable value in memory to that in size_t pagenum variable declaration

      std::map<std::string, long int> & getMemory();
      const std::map<std::string, long int> & getMemory() const;
        - Return current story memory
        - std::string: variable
        - long int: current value
*/

#include "eval3.hpp"

// PAGE CLASS
Page::Page() :
    pagenum(0),
    pagetype(),
    file(),
    text(),
    closing(),
    choices(),
    destpages(),
    conditions() {
}

Page::Page(size_t pagenum,
           std::string pagetype,
           std::string file,
           std::vector<std::string> text,
           std::string closing,
           std::vector<std::string> choices,
           std::vector<size_t> destpages) :
    pagenum(pagenum),
    pagetype(pagetype),
    file(file),
    text(text),
    closing(closing),
    choices(choices),
    destpages(destpages),
    conditions() {
}

Page::~Page() {
}

std::string & Page::getClosing() {
  return closing;
}
const std::string & Page::getClosing() const {
  return closing;
}

std::string & Page::getPagetype() {
  return pagetype;
}
const std::string & Page::getPagetype() const {
  return pagetype;
}

std::vector<std::string> & Page::getText() {
  return text;
}
const std::vector<std::string> & Page::getText() const {
  return text;
}

std::string & Page::getFile() {
  return file;
}
const std::string & Page::getFile() const {
  return file;
}

size_t & Page::getPagenum() {
  return pagenum;
}
const size_t & Page::getPagenum() const {
  return pagenum;
}

std::vector<std::string> & Page::getChoices() {
  return choices;
}
const std::vector<std::string> & Page::getChoices() const {
  return choices;
}

std::vector<size_t> & Page::getDestpages() {
  return destpages;
}
const std::vector<size_t> & Page::getDestpages() const {
  return destpages;
}

std::string Page::toString() const {
  std::stringstream ss;
  const std::vector<std::string> & text = getText();
  std::vector<std::string>::const_iterator it = text.begin();
  while (it != text.end()) {
    ss << *it << std::endl;
    ++it;
  }
  ss << std::endl << getClosing();
  if (!pagetype.compare("N")) {
    ss << std::endl;
    std::vector<std::string>::const_iterator choiceIt = choices.begin();
    int i = 0;
    while (choiceIt != choices.end()) {
      i++;
      ss << " " << i << ". " << *choiceIt << std::endl;
      ++choiceIt;
    }
  }
  return ss.str();
}

std::map<int, std::pair<std::string, long int> > & Page::getConditions() {
  return conditions;
}
const std::map<int, std::pair<std::string, long int> > & Page::getConditions() const {
  return conditions;
}

void Page::setConditions(std::map<int, std::pair<std::string, long int> > & conds) {
  conditions = conds;
}

bool Page::doesMatchExist(std::map<std::string, long int> & memory,
                          std::string & var,
                          long int val) const {
  std::map<std::string, long int>::const_iterator it = memory.find(var);
  if (it != memory.end() && it->second == val) {
    return true;
  }
  return false;
}

std::vector<std::string> Page::process(std::map<std::string, long int> & memory) const {
  int choiceNum = 1;
  std::vector<std::string> processed;
  std::vector<std::string>::const_iterator it = choices.begin();
  while (it != choices.end()) {
    std::map<int, std::pair<std::string, long int> >::const_iterator condIt =
        conditions.find(choiceNum);
    if (condIt != conditions.end()) {
      std::string var = condIt->second.first;
      long int val = condIt->second.second;
      bool match = doesMatchExist(memory, var, val);
      if (match) {
        processed.push_back(*it);
      }
      else {
        std::string unavailable("<UNAVAILABLE>");
        processed.push_back(unavailable);
      }
    }
    else {
      processed.push_back(*it);
    }
    choiceNum++;
    ++it;
  }
  return processed;
}

std::vector<std::string> Page::processChoices(
    std::map<std::string, long int> & memory) const {
  if (!conditions.empty()) {
    std::vector<std::string> processed = process(memory);
    return processed;
  }
  return choices;
}

std::set<size_t> Page::getInvalidChoices(std::map<std::string, long int> & memory) const {
  std::vector<std::string> processed = processChoices(memory);
  size_t choiceNum = 1;
  std::set<size_t> invalidChoices;
  std::vector<std::string>::iterator it = processed.begin();
  while (it != processed.end()) {
    if (!it->compare("<UNAVAILABLE>")) {
      invalidChoices.insert(choiceNum);
    }
    choiceNum++;
    ++it;
  }
  return invalidChoices;
}

std::string Page::toStringCond(std::map<std::string, long int> & memory) const {
  std::stringstream ss;
  const std::vector<std::string> & text = getText();
  std::vector<std::string>::const_iterator it = text.begin();
  while (it != text.end()) {
    ss << *it << std::endl;
    ++it;
  }
  ss << std::endl << getClosing();
  if (!pagetype.compare("N")) {
    ss << std::endl;
    std::vector<std::string> processed = processChoices(memory);
    std::vector<std::string>::const_iterator choiceIt = processed.begin();
    int i = 0;
    while (choiceIt != processed.end()) {
      i++;
      ss << " " << i << ". " << *choiceIt << std::endl;
      ++choiceIt;
    }
  }
  return ss.str();
}

//======================================================================

Story::Story() : pages(), vars() {
}

Story::Story(std::map<size_t, Page *> pages) : pages(pages), vars() {
}

Story::~Story() {
  std::map<size_t, Page *>::iterator it = pages.begin();
  while (it != pages.end()) {
    delete it->second;
    ++it;
  }
}

std::map<size_t, Page *> & Story::getPages() {
  return pages;
}
const std::map<size_t, Page *> & Story::getPages() const {
  return pages;
}

Page * Story::getPage(size_t pagenum) {
  return pages[pagenum];
}

size_t Story::size() {
  return pages.size();
}

std::set<size_t> Story::getPagetypes(std::string & pagetype) {
  std::set<size_t> pagetypes;
  std::map<size_t, Page *>::iterator it = pages.begin();
  while (it != pages.end()) {
    if (!it->second->getPagetype().compare(pagetype)) {
      pagetypes.insert(it->first);
    }
    ++it;
  }
  return pagetypes;
}

std::vector<std::string> & Story::getVars() {
  return vars;
}
const std::vector<std::string> & Story::getVars() const {
  return vars;
}

void Story::setVars(std::vector<std::string> & v) {
  vars = v;
}

std::vector<std::string> Story::filterVars(size_t pagenum) {
  std::vector<std::string> filteredVars;
  std::vector<std::string>::const_iterator it = vars.begin();
  while (it != vars.end()) {
    std::string var = *it;
    size_t pnum = getPagenum(var);
    if (pagenum == pnum) {
      filteredVars.push_back(*it);
    }
    ++it;
  }
  return filteredVars;
}

std::string Story::parseVar(std::string & str) {
  size_t pos = str.find("$");
  size_t pos2 = str.find("=");
  size_t length = pos2 - (pos + 1);
  std::string var = str.substr(pos + 1, length);
  return var;
}

long int Story::parseVal(std::string & str) {
  size_t pos = str.find("=");
  std::string substr = str.substr(pos + 1);
  char * end = NULL;
  long int val = std::strtol(substr.c_str(), &end, 10);
  return val;
}

void Story::buildMemory() {
  std::vector<std::string>::iterator it = vars.begin();
  while (it != vars.end()) {
    std::string var = parseVar(*it);
    memory[var] = 0;
    ++it;
  }
}

void Story::updateMemory(size_t pagenum) {
  std::vector<std::string> fvars = filterVars(pagenum);
  std::vector<std::string>::iterator it = fvars.begin();
  while (it != fvars.end()) {
    std::string var = parseVar(*it);
    long int val = parseVal(*it);
    memory[var] = val;
    ++it;
  }
}

std::map<std::string, long int> & Story::getMemory() {
  return memory;
}
const std::map<std::string, long int> & Story::getMemory() const {
  return memory;
}

// ERROR HANDLING
void checkPath(std::string & path) {
  /*
    Check file path validity

    Arguments
    ---------
    std::string & path: path to file

    Return
    ------
    None
  */
  if (path.empty()) {
    std::cerr << "Failed to build path: " << path << std::endl;
    exit(EXIT_FAILURE);
  }
}

void checkNumArgs(int numArgs) {
  /*
    Check number of command line arguments

    Arguments
    ---------
    int numArgs: number of command line arguments

    Return
    ------
    None
  */
  if (numArgs != 2) {
    std::cerr << "Usage: ./cyoa-step1 <dir>\n";
    exit(EXIT_FAILURE);
  }
}

void checkInfile(const std::ifstream & infile, std::string & file) {
  /*
    Check infile validity

    Arguments
    ---------
    const std::ifstream & infile: file stream to infile
    std::string & file: name of file

    Return
    ------
    None
  */
  if (!infile.good()) {
    std::cerr << "Failed to open " << file << std::endl;
    exit(EXIT_FAILURE);
  }
}

int checkPagenum(std::string & str) {
  /*
    Check page number validity

    Arguments
    ---------
    std::string & str: string with page number

    Return
    ------
    int indicating success (1) or failure (0) to read page number
  */
  char * end = NULL;
  std::strtoul(str.c_str(), &end, 10);
  if (errno == ERANGE || str[0] == *end) {
    std::cerr << "Invalid Page Number: " << str << std::endl;
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

int checkFormat(std::string & str, std::string & substr) {
  /*
    Check str for presence of substr

    Arguments
    ---------
    std::string & str: string to check
    std::string & substr: string to look for in str

    Return
    ------
    int indicating success (1) or failure (0) to find substr in str
  */
  size_t pos = str.find_first_of(substr);
  if (pos == str.npos) {
    std::cerr << "Page Type: Could not find " << substr << std::endl;
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

int checkDeclaration(std::string & str) {
  /*
    Check page declaration validity

    Arguments
    ---------
    std::string & str: page declaration

    Return
    ------
    int indicating success (1) or failure (0) of page declaration validity
  */
  if (!checkPagenum(str)) {
    std::string pagetype("NWL");
    std::string colon(":");
    if (!checkFormat(str, pagetype) && !checkFormat(str, colon)) {
      return EXIT_SUCCESS;
    }
  }
  std::cerr << "Invalid Input: " << str << std::endl;
  exit(EXIT_FAILURE);
}

int charCount(std::string & str, char c) {
  /*
    Count frequency of char c in std::string & str

    Arguments
    ---------
    std::string & str: string searched for char c
    char c: character to look for in str

    Return
    ------
    int indicating frequency of char c in std::string str
  */
  int count = 0;
  for (size_t i = 0; i < str.size(); i++) {
    if (str[i] == c) {
      count++;
    }
  }
  return count;
}

int checkChoice(std::string & str) {
  /*
    Check choice declaration validity

    Arguments
    ---------
    std::string & str: choice declaration

    Return
    ------
    int indicating success (1) or failure (0) to read page number
  */
  if (charCount(str, ':') == 2) {
    size_t pos = str.find_first_of(":");
    std::string substr = str.substr(pos + 1);
    if (!checkPagenum(str) && !checkPagenum(substr)) {
      if (str.find_first_of(":") != str.find_last_of(":")) {
        return EXIT_SUCCESS;
      }
    }
  }
  std::cerr << "Invalid Input: " << str << std::endl;
  exit(EXIT_FAILURE);
}

void checkMalloc(Page * page) {
  /*
    Check Page * validity

    Arguments
    ---------
    Page * page: pointer to instance of Page class

    Return
    ------
    None
  */
  if (page == NULL) {
    std::cerr << "Failed malloc" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void checkPageSeq(std::vector<std::string> & declarations) {
  /*
    Check page sequence validity

    Arguments
    ---------
    std::vector<std::string> & declarations: page declarations

    Return
    ------
    None
  */
  char * pageEnd = NULL;
  char * nextpageEnd = NULL;
  for (size_t i = 0; i < (declarations.size() - 1); i++) {
    size_t page = std::strtoul(declarations[i].c_str(), &pageEnd, 10);
    size_t nextpage = std::strtoul(declarations[i + 1].c_str(), &nextpageEnd, 10);
    if ((page + 1) != nextpage) {
      std::cerr << "Missing Page: " << (nextpage - 1) << std::endl;
      exit(EXIT_FAILURE);
    }
    pageEnd = NULL;
    nextpageEnd = NULL;
  }
}

void checkDups(std::vector<std::string> & lines) {
  /*
    Check story file lines for duplicate entries (page/choice declarations)

    Arguments
    ---------
    std::vector<std::string> & lines: story file lines

    Return
    ------
    None
  */
  std::set<std::string> members;
  std::vector<std::string>::iterator it = lines.begin();
  while (it != lines.end()) {
    if (members.find(*it) != members.end()) {
      std::cerr << *it << " can only appear once" << std::endl;
      exit(EXIT_FAILURE);
    }
    else {
      members.insert(*it);
    }
    ++it;
  }
}

void checkOrder(std::string & str, std::set<size_t> & members, bool flag) {
  /*
    Check page/choice declaration order

    Arguments
    ---------
    std::string & str: page/choice declaration
    std::set<size_t> & members: page numbers for previously processed page declarations
    bool flag: indicates check for page (true) or choice (false) declaration

    Return
    ------
    None
  */
  size_t num = getPagenum(str);
  if (flag) {
    if (members.find(num) == members.end()) {
      if (members.upper_bound(num) != members.end()) {
        std::cerr << str << " must appear in order" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }
  else {
    if (members.find(num) == members.end()) {
      std::cerr << str << " cannot appear before its page declaration" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

void checkStoryFile(std::vector<std::string> & lines) {
  /*
    Check story file validity

    Arguments
    ---------
    std::vector<std::string> & lines: story file lines

    Return
    ------
    None
  */
  size_t num = 0;
  std::set<size_t> declarations;
  std::vector<std::string>::iterator it = lines.begin();
  while (it != lines.end()) {
    num = getPagenum(*it);
    if (it->find("@") != it->npos) {
      checkOrder(*it, declarations, true);
      if (!checkDeclaration(*it)) {
        declarations.insert(num);
      }
    }
    else {
      if (!checkChoice(*it)) {
        checkOrder(*it, declarations, false);
      }
    }
    ++it;
  }
}

std::set<size_t> findNormalpages(std::vector<std::string> & lines) {
  /*
    Find normal page declarations in story file lines

    Arguments
    ---------
    std::vector<std::string> & lines: story file lines

    Return
    ------
    std::set<size_t> of page numbers for normal pages in story
  */
  std::set<size_t> normalpages;
  size_t num = 0;
  std::vector<std::string>::iterator it = lines.begin();
  while (it != lines.end()) {
    if (it->find("N") != it->npos) {
      num = getPagenum(*it);
      normalpages.insert(num);
    }
    ++it;
  }
  return normalpages;
}

void checkMembership(std::set<size_t> & members, std::vector<std::string> & candidates) {
  /*
    Check choice declarations for normal page association

    Arguments
    ---------
    std::set<size_t> & members: page numbers of normal pages
    std::vector<std::string> & candidates: choice declarations

    Return
    ------
    None
  */
  size_t num = 0;
  std::vector<std::string>::iterator it = candidates.begin();
  while (it != candidates.end()) {
    num = getPagenum(*it);
    if (members.find(num) == members.end()) {
      std::cerr << "Win/Lose pages cannot have choices" << std::endl;
      exit(EXIT_FAILURE);
    }
    ++it;
  }
}

void checkEndPages(
    std::pair<std::vector<std::string>, std::vector<std::string> > & data) {
  /*
    Check win/lose page validity

    Arguments
    ---------
    std::pair<std::vector<std::string>, std::vector<std::string> > & data: page/choice declarations
      - first std::vector<std::string>: page declarations
      - second std::vector<std::string>: choice declarations

    Return
    ------
    None
  */
  std::set<size_t> normalpages = findNormalpages(data.first);
  checkMembership(normalpages, data.second);
}

std::set<size_t> addDestpages(std::set<size_t> & members,
                              std::vector<size_t> & candidates) {
  /*
    Check destination page numbers (candidates) for membership in
    processed destination page numbers (members)

    Arguments
    ---------
    std::set<size_t> & members: processed destination page numbers
    std::vector<size_t> & candidates: destination page numbers

    Return
    ------
    std::set<size_t> processed destination page numbers
  */
  std::vector<size_t>::iterator it = candidates.begin();
  while (it != candidates.end()) {
    if (members.find(*it) == members.end()) {
      members.insert(*it);
    }
    ++it;
  }
  return members;
}

void helpInvalidRefs(std::map<size_t, Page *> & pages, std::set<size_t> & references) {
  /*
    Helper function for checkInvalidRefs

    Arguments
    ---------
    std::map<size_t, Page *> & pages: Page(s) of story
    std::set<size_t> & references: destination page numbers

    Return
    ------
    None
  */
  std::set<size_t>::iterator it = references.begin();
  while (it != references.end()) {
    if (pages.find(*it) == pages.end() && *it != 0) {
      std::cerr << "Invalid Page Reference: " << *it << std::endl;
      exit(EXIT_FAILURE);
    }
    ++it;
  }
}

void checkInvalidRefs(Story * story) {
  /*
    Check destination page number validity

    Arguments
    ---------
    Story * story: Choose-Your-Own-Adventure story

    Return
    ------
    None
  */
  std::string normal("N");
  std::set<size_t> normalpages = story->getPagetypes(normal);
  std::map<size_t, Page *> pages = story->getPages();
  std::set<size_t> destpages;
  std::set<size_t>::iterator it = normalpages.begin();
  while (it != normalpages.end()) {
    std::vector<size_t> references = story->getPage(*it)->getDestpages();
    destpages = addDestpages(destpages, references);
    ++it;
  }
  helpInvalidRefs(pages, destpages);
}

void helpMissingRefs(std::map<size_t, Page *> & pages, std::set<size_t> & references) {
  /*
    Helper function for checkMissingRefs

    Arguments
    ---------
    std::map<size_t, Page *> & pages: Page(s) of story
    std::set<size_t> & references: destination page numbers

    Return
    ------
    None
  */
  std::map<size_t, Page *>::iterator it = pages.begin();
  while (it != pages.end()) {
    if (references.find(it->first) == references.end() && it->first != 0) {
      std::cerr << "Missing Reference: page " << it->first << " does not have a reference"
                << std::endl;
      exit(EXIT_FAILURE);
    }
    ++it;
  }
}

void checkMissingRefs(Story * story) {
  /*
    Check story pages for reference

    Arguments
    ---------
    Story * story: Choose-Your-Own-Adventure story

    Return
    ------
    None
  */
  std::string normal("N");
  std::set<size_t> normalpages = story->getPagetypes(normal);
  std::map<size_t, Page *> pages = story->getPages();
  std::set<size_t> destpages;
  std::set<size_t>::iterator it = normalpages.begin();
  while (it != normalpages.end()) {
    std::vector<size_t> references = story->getPage(*it)->getDestpages();
    destpages = addDestpages(destpages, references);
    ++it;
  }
  helpMissingRefs(pages, destpages);
}

void checkNumEndPages(Story * story) {
  /*
    Check story for number of win and lose pages

    Arguments
    ---------
    Story * story: Choose-Your-Own-Adventure story

    Return
    ------
    None
  */
  std::string win("W");
  std::string lose("L");
  size_t numWin = story->getPagetypes(win).size();
  size_t numLose = story->getPagetypes(lose).size();
  if (numWin < 1 || numLose < 1) {
    std::cerr << "There must be at least one Win and one Lose page" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void checkStory(Story * story) {
  /*
    Check story pages for invalid references, missing references, and number of win
    and lose pages

    Arguments
    ---------
    Story * story: Choose-Your-Own-Adventure story

    Return
    ------
    None
  */
  checkInvalidRefs(story);
  checkMissingRefs(story);
  checkNumEndPages(story);
}

// PROCESS INPUT
std::string checkDir(char * dir) {
  /*
    Remove end '/' from directory path if present

    Arguments
    ---------
    char * dir: directory with story.txt file

    Return
    ------
    std::string directory with story.txt file
  */
  std::string strdir = dir;
  if (strdir[strdir.size() - 1] == '/') {
    strdir.resize(strdir.size() - 1);
  }
  return strdir;
}

std::string buildPath(char * dir, std::string & file) {
  /*
    Append std::string & file to char * dir

    Arguments
    ---------
    char * dir: directory with std::string & file
    std::string & file: name of file in char * dir

    Return
    ------
    std::string path to std::string & file
  */
  std::string strdir = checkDir(dir);
  std::string path = strdir + "/" + file;
  return path;
}

std::string getPath(int numArgs, char ** inputs, std::string & file) {
  /*
    Create path to std::string & file

    Arguments
    ---------
    int numArgs: number of command line arguments
    char ** inputs: pointer to array with command line arguments
    std::string & file: name of file for path

    Return
    ------
    std::string path to std::string & file
  */
  char * dir = NULL;
  checkNumArgs(numArgs);
  dir = inputs[1];
  std::string path;
  if (dir != NULL) {
    path = buildPath(dir, file);
  }
  return path;
}

std::vector<std::string> readInfile(std::string & path, std::string & file, bool flag) {
  /*
    Read contents of std::string & file located at std::string & path

    Arguments
    ---------
    std::string & path: path to std::string & file
    std::string & file: name of file
    bool flag: indicates check for story.txt file (true) or not (false)

    Return
    ------
    std::vector<std::string> contents of std::string & file
  */
  std::ifstream story(path.c_str());
  std::string input;
  std::vector<std::string> inputs;
  checkInfile(story, file);
  while (getline(story, input)) {
    if (!story.good()) {
      story.clear();
      story.close();
      std::cerr << "Cannot read " << file << std::endl;
      exit(EXIT_FAILURE);
    }
    if (flag) {
      if (!input.empty()) {
        inputs.push_back(input);
      }
    }
    else {
      inputs.push_back(input);
    }
  }
  if (flag) {
    checkStoryFile(inputs);
  }
  story.close();
  return inputs;
}

std::pair<std::vector<std::string>, std::vector<std::string> > parseStoryFile(
    std::vector<std::string> & lines) {
  /*
    Extract page/choice declarations from story.txt file

    Arguments
    ---------
    std::vector<std::string> & lines: story file lines

    Return
    ------
    std::pair<std::vector<std::string>, std::vector<std::string> > page/choice
    declarations of story file
    - first std::vector<std::string>: page declarations
    - second std::vector<std::string>: choice declarations
  */
  std::vector<std::string> declarations;
  std::vector<std::string> choices;
  std::vector<std::string>::iterator it = lines.begin();
  while (it != lines.end()) {
    if (it->find("@") != it->npos) {
      declarations.push_back(*it);
    }
    else {
      choices.push_back(*it);
    }
    ++it;
  }
  std::pair<std::vector<std::string>, std::vector<std::string> > data =
      std::make_pair(declarations, choices);
  checkDups(data.first);
  checkDups(data.second);
  checkEndPages(data);
  checkPageSeq(data.first);
  return data;
}

size_t getPagenum(std::string & str) {
  /*
    Return page number in std::string & str

    Arguments
    ---------
    std::string & str: string with page number

    Return
    ------
    size_t page number
  */
  char * end;
  size_t pagenum = std::strtoul(str.c_str(), &end, 10);
  return pagenum;
}

std::string getPagetype(std::string & str) {
  /*
    Return page type in std::string & str

    Arguments
    ---------
    std::string & str: string with page type

    Return
    ------
    std::string page type
  */
  size_t pos = str.find_first_of("NWL");
  std::string pagetype;
  pagetype = str[pos];
  return pagetype;
}

std::string getFile(std::string & str) {
  /*
    Return file name in std::string & str

    Arguments
    ---------
    std::string & str: string with file name

    Return
    ------
    std::string file name
  */
  size_t pos = str.find_last_of(":");
  std::string file = str.substr(pos + 1);
  return file;
}

std::string createClosing(std::string & pagetype) {
  /*
    Return closing for std::string & page type

    Arguments
    ---------
    std::string & pagetype: page type defined as N, W, or L

    Return
    ------
    std::string closing for given page type
  */
  std::string closing;
  if (!pagetype.compare("N")) {
    closing = "What would you like to do?\n";
    return closing;
  }
  if (!pagetype.compare("W")) {
    closing = "Congratulations! You have won. Hooray!\n";
    return closing;
  }
  closing = "Sorry, you have lost. Better luck next time!\n";
  return closing;
}

std::vector<std::string> parseChoices(std::vector<std::string> & choices,
                                      size_t pagenum) {
  /*
    Return choices for size_t page number

    Arguments
    ---------
    std::vector<std::string> & choices: choice declarations
    size_t pagenum: page number

    Return
    ------
    std::vector<std::string> choices for size_t page number
  */
  std::vector<std::string> matchingChoices;
  size_t parsedPagenum = 0;
  std::vector<std::string>::iterator it = choices.begin();
  while (it != choices.end()) {
    parsedPagenum = getPagenum(*it);
    if (parsedPagenum == pagenum) {
      matchingChoices.push_back(*it);
    }
    ++it;
  }
  return matchingChoices;
}

std::vector<size_t> parseDestpages(std::vector<std::string> & choices) {
  /*
    Return destination pages for std::vector<std::string> & choices

    Arguments
    ---------
    std::vector<std::string> & choices: choice declarations

    Return
    ------
    std::vector<size_t> destination page numbers
  */
  size_t destpage = 0;
  std::vector<size_t> destpages;
  std::vector<std::string>::iterator it = choices.begin();
  while (it != choices.end()) {
    size_t pos = it->find_first_of(":");
    std::string substr = it->substr(pos + 1);
    destpage = getPagenum(substr);
    destpages.push_back(destpage);
    ++it;
  }
  return destpages;
}

std::vector<std::string> parseChoiceText(std::vector<std::string> & choices) {
  /*
    Return text for std::vector<std::string> & choices

    Arguments
    ---------
    std::vector<std::string> & choices: choice declarations

    Return
    ------
    std::vector<std::string> text for std::vector<std::string> & choices
  */
  std::vector<std::string> choiceText;
  std::vector<std::string>::iterator it = choices.begin();
  while (it != choices.end()) {
    std::string text = getFile(*it);
    choiceText.push_back(text);
    ++it;
  }
  return choiceText;
}

Page * matchChoices(size_t pagenum,
                    std::string & pagetype,
                    std::string & file,
                    std::vector<std::string> & text,
                    std::string & closing,
                    std::vector<std::string> & choices) {
  /*
    Return Page with matching std::vector<std::string> & choices

    Arguments
    ---------
    size_t pagenum: page number
    std::string & pagetype: page type
    std::string & file: name of file with text for page
    std::vector<std::string> & text: text displayed for page
    std::string & closing: closing text displayed for page
    std::vector<std::string> & choices: choice declarations

    Return
    ------
    Page * to instance of Page class
  */
  std::vector<std::string> matchingChoices = parseChoices(choices, pagenum);
  std::vector<size_t> destpages = parseDestpages(matchingChoices);
  std::vector<std::string> parsedChoices = parseChoiceText(matchingChoices);
  Page * page =
      new Page(pagenum, pagetype, file, text, closing, parsedChoices, destpages);
  checkMalloc(page);
  return page;
}

Page * buildPage(char * dir,
                 std::string & declaration,
                 std::vector<std::string> & choices) {
  /*
    Return complete story Page for std::string & declaration

    Arguments
    ---------
    char * dir: directory with Choose-Your-Own-Adventure
    std::string & declaration: page declaration
    std::vector<std::string> & choices: choice declarations

    Return
    ------
    Page * to instance of Page class
  */
  size_t pagenum = getPagenum(declaration);
  std::string pagetype = getPagetype(declaration);
  std::string file = getFile(declaration);
  std::string path = buildPath(dir, file);
  std::vector<std::string> text = readInfile(path, file, false);
  std::string closing = createClosing(pagetype);
  Page * page = matchChoices(pagenum, pagetype, file, text, closing, choices);
  checkMalloc(page);
  return page;
}

std::map<size_t, Page *> buildPages(char * dir,
                                    std::vector<std::string> & declarations,
                                    std::vector<std::string> & choices) {
  /*
    Return complete Page(s) for story

    Arguments
    ---------
    char * dir: directory with Choose-Your-Own-Adventure
    std::vector<std::string> & declarations: page declarations
    std::vector<std::string> & choices: choice declarations

    Return
    ------
    std::map<size_t, Page *> Page(s) for Choose-Your-Own-Adventure
  */
  std::map<size_t, Page *> pages;
  Page * page = NULL;
  std::vector<std::string>::iterator it = declarations.begin();
  while (it != declarations.end()) {
    page = buildPage(dir, *it, choices);
    if (page != NULL) {
      pages[page->getPagenum()] = page;
    }
    ++it;
  }
  return pages;
}

Story * buildStory(int argc, char ** argv) {
  /*
    Return complete Choose-Your-Own-Adventure Story

    Arguments
    ---------
    int arg: number of command line arguments
    char ** argv: pointer to array with command line arguments

    Return
    ------
    Story * to complete Choose-Your-Own-Adventure Story
  */
  std::string storyfile("story.txt");
  std::string path = getPath(argc, argv, storyfile);
  std::vector<std::string> lines;
  checkPath(path);
  lines = readInfile(path, storyfile, true);
  std::pair<std::vector<std::string>, std::vector<std::string> > data =
      parseStoryFile(lines);
  std::map<size_t, Page *> pages = buildPages(argv[1], data.first, data.second);
  Story * story = new Story(pages);
  return story;
}

void printStory(Story * story) {
  /*
    Print complete Choose-Your-Own-Adventure Story

    Arguments
    ---------
    Story * story: pointer to Choose-Your-Own-Adventure Story

    Return
    ------
    None
  */
  std::map<size_t, Page *> pages = story->getPages();
  std::map<size_t, Page *>::iterator it = pages.begin();
  while (it != pages.end()) {
    std::cout << "Page " << it->second->getPagenum() << std::endl << "==========\n";
    std::cout << it->second->toString();
    ++it;
  }
}

void initStory(Story * story) {
  /*
    Initiate Choose-Your-Own-Adventure Story

    Arguments
    ---------
    Story * story: pointer to Choose-Your-Own-Adventure Story

    Return
    ------
    None
  */
  checkStory(story);
  std::cout << story->getPage(0)->toString();
}

void playStory(Story * story) {
  /*
    Run Choose-Your-Own-Adventure Story

    Arguments
    ---------
    Story * story: pointer to Choose-Your-Own-Adventure Story

    Return
    ------
    None
  */
  initStory(story);
  bool flag = false;
  size_t prevPage = 0;
  std::string input;
  char * end = NULL;
  while (!flag) {
    std::cin >> input;
    size_t choice = std::strtoul(input.c_str(), &end, 10);
    Page * page = story->getPage(prevPage);
    size_t max = page->getChoices().size();
    while (!std::cin.good() || errno == ERANGE || choice == 0 ||
           (choice < 1 || max < choice)) {
      std::cout << "That is not a valid choice, please try again" << std::endl;
      std::cin.clear();
      input.clear();
      end = NULL;
      std::cin >> input;
      choice = std::strtoul(input.c_str(), &end, 10);
    }
    size_t newPage = story->getPage(prevPage)->getDestpages()[choice - 1];
    std::cout << story->getPage(newPage)->toString();
    prevPage = newPage;
    if (story->getPage(newPage)->getPagetype().compare("N") != 0) {
      flag = true;
    }
    input.clear();
  }
}

int getFrequency(std::vector<size_t> & currentPath, size_t currentNode) {
  /*
    Return frequency of size_t currentNode in std::vector<size_t> & currentPath

    Arguments
    ---------
    std::vector<size_t> & currentPath: current page sequence
    size_t currentNode: current page along std::vector<size_t> & currentPath

    Return
    ------
    int frequency of size_t currentNode in std::vector<size_t> & currentPath
  */
  int freq = 0;
  std::vector<size_t>::iterator it = currentPath.begin();
  while (it != currentPath.end()) {
    if (currentNode == *it) {
      freq++;
    }
    ++it;
  }
  return freq;
}

std::map<int, std::vector<size_t> > dfs(Story * story, size_t from, size_t to) {
  /*
    Return all paths from starting Page size_t from to win Page size_t to in Story

    Arguments
    ---------
    Story * story: pointer to Choose-Your-Own-Adventure Story
    size_t from: number of starting Page in Story
    size_t to: number of win Page in Story

    Return
    ------
    std::map<int, std::vector<size_t> > all paths from starting Page to win
    Page in Story
      - int: path number
      - std::vector<size_t>: page sequence from size_t from to size_t to
  */
  int pathNum = 0;
  std::map<int, std::vector<size_t> > paths;
  std::stack<std::vector<size_t> > todo;
  std::vector<size_t> path;
  path.push_back(from);
  todo.push(path);
  while (!todo.empty()) {
    std::vector<size_t> currentPath = todo.top();
    todo.pop();
    size_t currentNode = currentPath.back();
    if (currentNode == to) {
      paths[pathNum] = currentPath;
      pathNum++;
    }
    if (!story->getPage(currentNode)->getDestpages().empty() &&
        getFrequency(currentPath, currentNode) < 2) {
      std::vector<size_t> adjacentNodes = story->getPage(currentNode)->getDestpages();
      std::vector<size_t>::iterator it = adjacentNodes.begin();
      while (it != adjacentNodes.end()) {
        std::vector<size_t> newpath = currentPath;
        newpath.push_back(*it);
        todo.push(newpath);
        ++it;
      }
    }
  }
  return paths;
}

std::map<int, std::map<int, std::vector<size_t> > > runDFS(Story * story) {
  /*
    Return all winnable paths in Story

    Arguments
    ---------
    Story * story: pointer to Choose-Your-Own-Adventure Story

    Return
    ------
    std::map<int, std::map<int, std::vector<size_t> > > all paths from starting Page to each win
    Page in Story
      - int: win Page count
      - std::map<int, std::vector<size_t> >: page sequence from size_t from to size_t to for win Page
  */
  std::string win("W");
  std::set<size_t> winpages = story->getPagetypes(win);
  std::set<size_t>::iterator it = winpages.begin();
  int winpageNum = 0;
  std::map<int, std::map<int, std::vector<size_t> > > allPaths;
  while (it != winpages.end()) {
    allPaths[winpageNum] = dfs(story, 0, *it);
    winpageNum++;
    ++it;
  }
  return allPaths;
}

size_t getChoiceNum(Page * page, size_t destpage) {
  /*
    Return choice number for Page associated with size_t destpage

    Arguments
    ---------
    Page * page: pointer to Page in Story
    size_t destpage: destination page number

    Return
    ------
    size_t choice number that corresponds to destpage
  */
  std::vector<size_t>::iterator it = page->getDestpages().begin();
  size_t choiceNum = 1;
  while (it != page->getDestpages().end()) {
    if (*it == destpage) {
      break;
    }
    choiceNum++;
    ++it;
  }
  return choiceNum;
}

void printPath(Story * story, std::vector<size_t> & pages) {
  /*
    Print winnable path in Story for Win Page

    Arguments
    ---------
    Story * story: pointer to Choose-Your-Own-Adventure Story
    std::vector<size_t> & pages: winning page sequence in Story for Win Page

    Return
    ------
    None
  */
  std::vector<size_t>::iterator it = pages.begin();
  std::string delim;
  int idx = 0;
  for (size_t i = 0; i < (pages.size() - 1); i++) {
    size_t choiceNum = getChoiceNum(story->getPage(*it), pages[idx + 1]);
    std::cout << delim << (*it) << "(" << choiceNum << ")";
    delim = ",";
    idx++;
    ++it;
  }
  std::cout << "," << pages.back() << "(win)" << std::endl;
}

void printPagePaths(Story * story, std::map<int, std::vector<size_t> > & paths) {
  /*
    Print all winnable paths in Story for Win Page

    Arguments
    ---------
    Story * story: pointer to Choose-Your-Own-Adventure Story
    std::map<int, std::vector<<size_t> > & paths: all winning page sequences in Story for Win Page

    Return
    ------
    None
  */
  std::map<int, std::vector<size_t> >::iterator it = paths.begin();
  while (it != paths.end()) {
    printPath(story, it->second);
    ++it;
  }
}

bool doesPathExist(std::map<int, std::map<int, std::vector<size_t> > > & allPaths) {
  /*
    Indicates if any winnable paths exist in Story

    Arguments
    ---------
    std::map<int, std::map<int, std::vector<<size_t> > > & allPaths: all winning page sequences in Story

    Return
    ------
    bool indicating if winnable path exists (true), and if not (false)
  */
  bool flag = false;
  std::map<int, std::map<int, std::vector<size_t> > >::iterator it = allPaths.begin();
  while (it != allPaths.end()) {
    if (!it->second.empty()) {
      flag = true;
      break;
    }
    ++it;
  }
  return flag;
}

void printAllPaths(Story * story) {
  /*
    Print all winnable paths in Story for all Win Page(s)

    Arguments
    ---------
    Story * story: pointer to Choose-Your-Own-Adventure Story

    Return
    ------
    None
  */
  checkStory(story);
  std::map<int, std::map<int, std::vector<size_t> > > allPaths = runDFS(story);
  if (doesPathExist(allPaths)) {
    std::map<int, std::map<int, std::vector<size_t> > >::iterator it = allPaths.begin();
    while (it != allPaths.end()) {
      printPagePaths(story, it->second);
      ++it;
    }
  }
  else {
    std::cout << "This story is unwinnable!" << std::endl;
  }
}

int checkVarValue(std::string & str) {
  /*
    Check variable value in std::string & str

    Arguments
    ---------
    std::string & str: string with variable value

    Return
    ------
    int indicating success (1) or failure (0) to read variable value
  */
  char * end = NULL;
  std::strtol(str.c_str(), &end, 10);
  if (errno == ERANGE || str[0] == *end) {
    std::cerr << "Invalid Variable Value: " << str << std::endl;
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

int checkVarDeclaration(std::string & str) {
  /*
    Check variable declaration validity

    Arguments
    ---------
    std::string & str: variable declaration

    Return
    ------
    int indicating success (1) or failure (0) of variable declaration validity
  */
  if (!checkPagenum(str)) {
    std::string dsign("$");
    std::string eqsign("=");
    if (!checkFormat(str, dsign) && !checkFormat(str, eqsign)) {
      size_t pos = str.find(eqsign);
      std::string substr = str.substr(pos + 1);
      if (!checkVarValue(substr)) {
        return EXIT_SUCCESS;
      }
    }
  }
  std::cerr << "Invalid Input: " << str << std::endl;
  exit(EXIT_FAILURE);
}

int checkCondChoice(std::string & str) {
  /*
    Check conditional choice declaration validity

    Arguments
    ---------
    std::string & str: conditional choice declaration

    Return
    ------
    int indicating success (1) or failure (0) of conditional choice declaration validity
  */
  if (!checkPagenum(str)) {
    std::string eqsign("=");
    if (charCount(str, ':') == 2 && !checkFormat(str, eqsign)) {
      if (charCount(str, '[') == 1 && charCount(str, ']') == 1) {
        if (str.find("[") < str.find("]")) {
          size_t pos = str.find_first_of(":");
          std::string substr = str.substr(pos + 1);
          size_t pos2 = str.find(eqsign);
          std::string substr2 = str.substr(pos2 + 1);
          if (!checkVarValue(substr2) && !checkPagenum(substr)) {
            if (str.find_first_of(":") != str.find_last_of(":")) {
              return EXIT_SUCCESS;
            }
          }
        }
      }
    }
  }
  std::cerr << "Invalid Input: " << str << std::endl;
  exit(EXIT_FAILURE);
}

void checkCondStory(std::vector<std::string> & lines) {
  /*
    Check conditional story file validity

    Arguments
    ---------
    std::vector<std::string> & lines: story file lines

    Return
    ------
    None
  */
  size_t num = 0;
  std::set<size_t> declarations;
  std::vector<std::string>::iterator it = lines.begin();
  while (it != lines.end()) {
    num = getPagenum(*it);
    if (it->find("@") != it->npos) {
      checkOrder(*it, declarations, true);
      if (!checkDeclaration(*it)) {
        declarations.insert(num);
      }
    }
    else if (it->find("$") != it->npos) {
      if (!checkVarDeclaration(*it)) {
        checkOrder(*it, declarations, false);
      }
    }
    else if (it->find("[") != it->npos) {
      if (!checkCondChoice(*it)) {
        checkOrder(*it, declarations, false);
      }
    }
    else {
      if (!checkChoice(*it)) {
        checkOrder(*it, declarations, false);
      }
    }
    ++it;
  }
}

std::vector<std::string> readCondFile(std::string & path, std::string & file, bool flag) {
  /*
    Read contents of std::string & file located at std::string & path

    Arguments
    ---------
    std::string & path: path to std::string & file
    std::string & file: name of file
    bool flag: indicates check for story.txt file (true) or not (false)

    Return
    ------
    std::vector<std::string> contents of std::string & file
  */
  std::ifstream story(path.c_str());
  std::string input;
  std::vector<std::string> inputs;
  checkInfile(story, file);
  while (getline(story, input)) {
    if (!story.good()) {
      story.clear();
      story.close();
      std::cerr << "Cannot read " << file << std::endl;
      exit(EXIT_FAILURE);
    }
    if (flag) {
      if (!input.empty()) {
        inputs.push_back(input);
      }
    }
    else {
      inputs.push_back(input);
    }
  }
  if (flag) {
    checkCondStory(inputs);
  }
  story.close();
  return inputs;
}

std::string getVariable(std::string & str, std::string & substr) {
  /*
    Return variable in std::string & str

    Arguments
    ---------
    std::string & str: string with variable
    std::string & substr: position in str to begin search

    Return
    ------
    std::string variable in str
  */
  size_t pos1 = str.find(substr);
  size_t pos2 = str.find("=");
  size_t length = pos2 - (pos1 + 1);
  std::string var = str.substr(pos1 + 1, length);
  return var;
}

void checkParsing(std::map<std::string, std::vector<std::string> > & data) {
  /*
    Check parsing of story.txt file into page, choice, and variable declarations

    Arguments
    ---------
    std::map<std::string, std::vector<std::string> > & data: page, choice, and variable
    declarations from story file

    Return
    ------
    None
  */
  checkDups(data["declarations"]);
  checkDups(data["variables"]);
  checkDups(data["choices"]);
  std::pair<std::vector<std::string>, std::vector<std::string> > subset =
      std::make_pair(data["declarations"], data["choices"]);
  checkEndPages(subset);
  checkPageSeq(data["declarations"]);
}

std::map<std::string, std::vector<std::string> > parseCondStory(
    std::vector<std::string> & lines) {
  /*
    Extract page, variable, and choice declarations from conditional story.txt file

    Arguments
    ---------
    std::vector<std::string> & lines: conditional story file lines

    Return
    ------
    std::map<std::string, std::vector<std::string> > page, variable, and choice
    declarations of story file
  */
  std::map<std::string, std::vector<std::string> > data;
  std::vector<std::string> declarations;
  std::vector<std::string> variables;
  std::vector<std::string> choices;
  std::vector<std::string>::iterator it = lines.begin();
  while (it != lines.end()) {
    if (it->find("@") != it->npos) {
      declarations.push_back(*it);
    }
    else if (it->find("$") != it->npos) {
      variables.push_back(*it);
    }
    else {
      choices.push_back(*it);
    }
    ++it;
  }
  data["declarations"] = declarations;
  data["variables"] = variables;
  data["choices"] = choices;
  checkParsing(data);
  return data;
}

long int getValue(std::string & str) {
  /*
    Return variable value in std::string & str

    Arguments
    ---------
    std::string & str: string with variable value

    Return
    ------
    long int variable value in str
  */
  size_t pos = str.find("=");
  std::string substr = str.substr(pos + 1);
  char * end = NULL;
  long int value = std::strtol(substr.c_str(), &end, 10);
  return value;
}

std::map<int, std::pair<std::string, long int> > parseConditions(
    std::vector<std::string> & choices) {
  /*
    Return conditional choices among std::vector<std::string> & choices

    Arguments
    ---------
    std::vector<std::string> & choice: choice declarations

    Return
    ------
    std::map<int, std::pair<std::string, long int> > conditional choices among choices
    - int: choice number
    - std::pair
      - std::string: variable
      - long int: variable value
  */
  std::map<int, std::pair<std::string, long int> > conditions;
  int choiceNum = 1;
  std::vector<std::string>::iterator it = choices.begin();
  while (it != choices.end()) {
    if (it->find("[") != it->npos) {
      std::string leftBracket("[");
      std::string variable = getVariable(*it, leftBracket);
      long int value = getValue(*it);
      std::pair<std::string, long int> data = std::make_pair(variable, value);
      conditions[choiceNum] = data;
    }
    choiceNum++;
    ++it;
  }
  return conditions;
}

Page * matchCondChoices(size_t pagenum,
                        std::string & pagetype,
                        std::string & file,
                        std::vector<std::string> & text,
                        std::string & closing,
                        std::vector<std::string> & choices) {
  /*
    Return Page with matching std::vector<std::string> & choices in conditional story

    Arguments
    ---------
    size_t pagenum: page number
    std::string & pagetype: page type
    std::string & file: name of file with text for page
    std::vector<std::string> & text: text displayed for page
    std::string & closing: closing text displayed for page
    std::vector<std::string> & choices: choice declarations

    Return
    ------
    Page * to instance of Page class
  */
  std::vector<std::string> matchingChoices = parseChoices(choices, pagenum);
  std::vector<size_t> destpages = parseDestpages(matchingChoices);
  std::map<int, std::pair<std::string, long int> > choiceConds =
      parseConditions(matchingChoices);
  std::vector<std::string> parsedChoices = parseChoiceText(matchingChoices);
  Page * page =
      new Page(pagenum, pagetype, file, text, closing, parsedChoices, destpages);
  if (!choiceConds.empty()) {
    page->setConditions(choiceConds);
  }
  return page;
}

Page * buildCondPage(char * dir,
                     std::string & declaration,
                     std::vector<std::string> & choices) {
  /*
    Return complete story Page for std::string & declaration in conditional story

    Arguments
    ---------
    char * dir: directory with Choose-Your-Own-Adventure
    std::string & declaration: page declaration
    std::vector<std::string> & choices: choice declarations

    Return
    ------
    Page * to instance of Page class
  */
  size_t pagenum = getPagenum(declaration);
  std::string pagetype = getPagetype(declaration);
  std::string file = getFile(declaration);
  std::string path = buildPath(dir, file);
  std::vector<std::string> text = readInfile(path, file, false);
  std::string closing = createClosing(pagetype);
  Page * page = matchCondChoices(pagenum, pagetype, file, text, closing, choices);
  checkMalloc(page);
  return page;
}

std::map<size_t, Page *> buildCondPages(char * dir,
                                        std::vector<std::string> & declarations,
                                        std::vector<std::string> & choices) {
  /*
    Return complete Page(s) for conditional story

    Arguments
    ---------
    char * dir: directory with Choose-Your-Own-Adventure
    std::vector<std::string> & declarations: page declarations
    std::vector<std::string> & choices: choice declarations

    Return
    ------
    std::map<size_t, Page *> Page(s) for Choose-Your-Own-Adventure
  */
  std::map<size_t, Page *> pages;
  Page * page = NULL;
  std::vector<std::string>::iterator it = declarations.begin();
  while (it != declarations.end()) {
    page = buildCondPage(dir, *it, choices);
    if (page != NULL) {
      pages[page->getPagenum()] = page;
    }
    ++it;
  }
  return pages;
}

Story * buildCondStory(int argc, char ** argv) {
  /*
    Return complete Conditional Choose-Your-Own-Adventure Story

    Arguments
    ---------
    int arg: number of command line arguments
    char ** argv: pointer to array with command line arguments

    Return
    ------
    Story * to complete Choose-Your-Own-Adventure Story
  */
  std::string file("story.txt");
  std::string path = getPath(argc, argv, file);
  std::vector<std::string> lines;
  checkPath(path);
  lines = readCondFile(path, file, true);
  std::map<std::string, std::vector<std::string> > data = parseCondStory(lines);
  std::map<size_t, Page *> pages =
      buildCondPages(argv[1], data["declarations"], data["choices"]);
  Story * story = new Story(pages);
  story->setVars(data["variables"]);
  story->buildMemory();
  return story;
}

void playCondStory(Story * story) {
  /*
    Run Conditional Choose-Your-Own-Adventure Story

    Arguments
    ---------
    Story * story: pointer to Choose-Your-Own-Adventure Story

    Return
    ------
    None
  */
  initStory(story);
  bool flag = false;
  size_t prevPage = 0;
  std::string input;
  char * end = NULL;
  while (!flag) {
    std::cin >> input;
    size_t choice = std::strtoul(input.c_str(), &end, 10);
    Page * page = story->getPage(prevPage);
    size_t max = page->getChoices().size();
    story->updateMemory(prevPage);
    std::set<size_t> invalid = page->getInvalidChoices(story->getMemory());
    while (!std::cin.good() || errno == ERANGE || choice == 0 ||
           (choice < 1 || max < choice) || invalid.find(choice) != invalid.end()) {
      if (errno == ERANGE || choice == 0 || (choice < 1 || max < choice)) {
        std::cout << "That is not a valid choice, please try again" << std::endl;
      }
      else {
        std::cout << "That choice is not available at this time, please try again"
                  << std::endl;
      }
      std::cin.clear();
      input.clear();
      end = NULL;
      std::cin >> input;
      choice = std::strtoul(input.c_str(), &end, 10);
    }
    size_t newPage = story->getPage(prevPage)->getDestpages()[choice - 1];
    story->updateMemory(newPage);
    std::cout << story->getPage(newPage)->toStringCond(story->getMemory());
    prevPage = newPage;
    if (story->getPage(newPage)->getPagetype().compare("N") != 0) {
      flag = true;
    }
    input.clear();
  }
}
