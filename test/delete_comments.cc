// clang-format off
//                    State Machine of Comment Deleter
//
//        +---------------+ +--------- CommentMultilineHold <----------+
//        |      '"'      | |   '/'             otherwise|       '*'   |
//        V               | V                            |             |
// StringInside -------> Code -------> CommentStart -----+--> CommentMultilineStart
//                '"'     ^     '/'          |  \'/'   '*'
//                        |       otherwise  |   +----------> CommentLine
//                        +------------------+---------------------|'\n'
// clang-format on

#include <fstream>
#include <iostream>
#include <string>

using std::ifstream;
using std::string;

enum class State {
  kCode = 0,
  kCommentStart,
  kCommentLine,
  kCommentMultilineStart,
  kCommentMultilineHold,
  kStringInside,
  kCount  // = 6
};

enum class Event {
  kSlash = 0,
  kStar,
  kNewLine,
  kDoubleQuotes,
  kOtherwise,
  kCount  // = 5
};

enum class Status { kDrop, kPrint };

struct StateMachine {
  State state;
  Status status;
  std::string ch;
};

StateMachine state_machine[(int)State::kCount][(int)Event::kCount] = {
    {
        // kCode
        {State::kCommentStart, Status::kDrop, ""},   // kSlash
        {State::kCode, Status::kPrint, ""},          // kStar
        {State::kCode, Status::kPrint, ""},          // kNewLine
        {State::kCommentStart, Status::kPrint, ""},  // kDoubleQuotes
        {State::kCode, Status::kPrint, ""}           // kOtherwise
    },
    {
        // kCommentStart
        {State::kCommentLine, Status::kDrop, ""},            // kSlash
        {State::kCommentMultilineStart, Status::kDrop, ""},  // kStar
        {State::kCode, Status::kPrint, "/"},                 // kNewLine
        {State::kCode, Status::kPrint, "/"},                 // kDoubleQuotes
        {State::kCode, Status::kPrint, "/"}                  // kOtherwise
    },
    {
        // kCommentLine
        {State::kCommentLine, Status::kDrop, ""},  // kSlash
        {State::kCommentLine, Status::kDrop, ""},  // kStar
        {State::kCode, Status::kDrop, ""},         // kNewLine
        {State::kCommentLine, Status::kDrop, ""},  // kDoubleQuotes
        {State::kCommentLine, Status::kDrop, ""}   // kOtherwise
    },
    {
        // kCommentMultilineStart
        {State::kCommentMultilineStart, Status::kDrop, ""},  // kSlash
        {State::kCommentMultilineHold, Status::kDrop, ""},   // kStar
        {State::kCommentMultilineStart, Status::kDrop, ""},  // kNewLine
        {State::kCommentMultilineStart, Status::kDrop, ""},  // kDoubleQuotes
        {State::kCommentMultilineStart, Status::kDrop, ""}   // kOtherwise
    },
    {
        // kCommentMultilineHold
        {State::kCode, Status::kDrop, ""},                  // kSlash
        {State::kCommentMultilineHold, Status::kDrop, ""},  // kStar
        {State::kCommentMultilineHold, Status::kDrop, ""},  // kNewLine
        {State::kCommentMultilineHold, Status::kDrop, ""},  // kDoubleQuotes
        {State::kCommentMultilineHold, Status::kDrop, ""}   // kOtherwise
    },
    {
        // kStringInside
        {State::kStringInside, Status::kPrint, ""},  // kSlash
        {State::kStringInside, Status::kPrint, ""},  // kStar
        {State::kStringInside, Status::kPrint, ""},  // kNewLine
        {State::kCode, Status::kPrint, ""},          // kDoubleQuotes
        {State::kStringInside, Status::kPrint, ""}   // kOtherwise
    }};

class FileReader {
 public:
  FileReader(const char* filename) : ifs_(filename) {
    if (!ifs_.is_open()) {
      std::cerr << filename << " does not open!" << std::endl;
    }
  }

  char next_char() { return current_char_ = ifs_.get(); }
  char current_char() const { return current_char_; }
  bool good() { return ifs_.good(); }
  Event make_event() {
    switch (next_char()) {
      case '/':
        return Event::kSlash;
      case '*':
        return Event::kStar;
      case '\n':
        return Event::kNewLine;
      case '"':
        return Event::kDoubleQuotes;
      default:
        return Event::kOtherwise;
    }
  }

 private:
  ifstream ifs_;
  char current_char_;
};

int main() {
  State state = State::kCode;

  FileReader freader("../uuu.txt.cc");
  while (freader.good()) {
    int event = (int)freader.make_event();
    auto machine = state_machine[(int)state][event];
    if (machine.status == Status::kPrint) {
      std::cout << machine.ch << freader.current_char();
    }
    state = machine.state;
  }

  return 0;
}
