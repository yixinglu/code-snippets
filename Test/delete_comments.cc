
#include <fstream>
#include <iostream>
#include <string>

using std::ifstream;
using std::string;

enum class kState {
  Code = 0,
  CommentLine,
  CommentMultiline,
  Count = 3
};

enum class kCharType {
  SlashStar = 0,
  StarSlash,
  SlashSlash,
  NewLine,
  Count = 4
};

struct StateMachine {
  kState state;
  bool drop_char;
};

StateMachine state_machine[(int)kState::Count][(int)kCharType::Count] = {
  {
    // Code
    {kState::CommentMultiline, true}, // SlashStar
    {kState::Code, false},            // StarSlash
    {kState::CommentLine, true},      // SlashSlash
    {kState::Code, false}             // NewLine
  },
  {
    // CommentLine
    {kState::CommentLine, true},      // SlashStar
    {kState::CommentLine, true},      // StarSlash
    {kState::CommentLine, true},      // SlashSlash
    {kState::Code, false}             // NewLine
  },
  {
    // CommentMultiline
    {kState::CommentMultiline, true}, // SlashStar
    {kState::Code, false},            // StarSlash
    {kState::CommentMultiline, true}, // SlashSlash
    {kState::CommentMultiline, true}  // NewLine
  }
};

class FileReader {
public:
  FileReader(const char* filename) : ifs_(filename) {
    if (!ifs_.is_open()) {
      std::cerr << filename << " does not open!" << std::endl;
    }
  }

  char next_char() { return current_char_ = ifs_.get(); }
  bool good() { return ifs_.good(); }
  char current_char() const { return current_char_; }
  kCharType get_char_type() {
    switch(current_char_) {
      case '/':
        switch(next_char()) {
          case '/': return kCharType::SlashSlash;
          case '*': return kCharType::SlashStar;
          default: break;
        }
        break;
      case '*':
        if (next_char() == '/') return kCharType::StarSlash;
        break;
      case '\n':
        return kCharType::NewLine;
      default: break;
    }
    return kCharType::Count;
  }


private:
  ifstream ifs_;
  char current_char_;
};


int main() {

  kState state;

  FileReader freader("uuu.txt.cc");
  while(freader.good()) {
    int char_type = (int)freader.get_char_type();
    if (!state_machine[(int)state][char_type].drop_char) {
      std::cout << freader.current_char();
    }
    state = state_machine[(int)state][char_type].state;
  }

  return 0;
}
