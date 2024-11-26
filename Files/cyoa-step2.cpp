#include "eval3.hpp"
int main(int argc, char ** argv) {
  Story * story = buildStory(argc, argv);
  playStory(story);
  delete story;
  return EXIT_SUCCESS;
}
