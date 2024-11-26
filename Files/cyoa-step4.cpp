#include "eval3.hpp"
int main(int argc, char ** argv) {
  Story * story = buildCondStory(argc, argv);
  playCondStory(story);
  delete story;
  return EXIT_SUCCESS;
}
