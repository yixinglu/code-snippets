// clang-format off
//                    State Machine of Comment Deleter
//                                        +------------+
//                                        V         '*'|
//        +---------------+ +--------- CommentMultilineHold <----------+
//        |      '"'      | |   '/'             otherwise|       '*'   |
//        V               | V                            |             |
// StringInside -------> Code -------> CommentStart -----+--> CommentMultilineStart
//      | ^       '"'     /^    '/'          |  \     '*'
//   '\'| |otherwise     / |                 |   +----------> CommentLine
//      V |             /  |        otherwise|       '/'           |
//  StringEscape       +   |                 |                     |'\n'
//                  '''|   +-----------------+---------------------+
//                     |   |
//               '\'   V   |'''
//   CharEscape <--- CharInside
//      |                 ^
//      |    otherwise    |
//      +-----------------+
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
  kStringEscape,
  kCharInside,
  kCharEscape,
  kCount  // = 9
};

enum class Event {
  kSlash = 0,
  kEscape,
  kStar,
  kNewLine,
  kDoubleQuotes,
  kQuote,
  kOtherwise,
  kCount  // = 7
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
        {State::kCode, Status::kPrint, ""},          // kEscape
        {State::kCode, Status::kPrint, ""},          // kStar
        {State::kCode, Status::kPrint, ""},          // kNewLine
        {State::kStringInside, Status::kPrint, ""},  // kDoubleQuotes
        {State::kCharInside, Status::kPrint, ""},    // kQuote
        {State::kCode, Status::kPrint, ""}           // kOtherwise
    },
    {
        // kCommentStart
        {State::kCommentLine, Status::kDrop, ""},            // kSlash
        {State::kCode, Status::kPrint, "/"},                 // kEscape
        {State::kCommentMultilineStart, Status::kDrop, ""},  // kStar
        {State::kCode, Status::kPrint, "/"},                 // kNewLine
        {State::kCode, Status::kPrint, "/"},                 // kDoubleQuotes
        {State::kCode, Status::kPrint, "/"},                 // kQuote
        {State::kCode, Status::kPrint, "/"}                  // kOtherwise
    },
    {
        // kCommentLine
        {State::kCommentLine, Status::kDrop, ""},  // kSlash
        {State::kCommentLine, Status::kDrop, ""},  // kEscape
        {State::kCommentLine, Status::kDrop, ""},  // kStar
        {State::kCode, Status::kPrint, ""},        // kNewLine
        {State::kCommentLine, Status::kDrop, ""},  // kDoubleQuotes
        {State::kCommentLine, Status::kDrop, ""},  // kQuote
        {State::kCommentLine, Status::kDrop, ""}   // kOtherwise
    },
    {
        // kCommentMultilineStart
        {State::kCommentMultilineStart, Status::kDrop, ""},   // kSlash
        {State::kCommentMultilineStart, Status::kDrop, ""},   // kEscape
        {State::kCommentMultilineHold, Status::kDrop, ""},    // kStar
        {State::kCommentMultilineStart, Status::kPrint, ""},  // kNewLine
        {State::kCommentMultilineStart, Status::kDrop, ""},   // kDoubleQuotes
        {State::kCommentMultilineStart, Status::kDrop, ""},   // kQuote
        {State::kCommentMultilineStart, Status::kDrop, ""}    // kOtherwise
    },
    {
        // kCommentMultilineHold
        {State::kCode, Status::kDrop, ""},                    // kSlash
        {State::kCommentMultilineStart, Status::kDrop, ""},   // kEscape
        {State::kCommentMultilineHold, Status::kDrop, ""},    // kStar
        {State::kCommentMultilineStart, Status::kPrint, ""},  // kNewLine
        {State::kCommentMultilineStart, Status::kDrop, ""},   // kDoubleQuotes
        {State::kCommentMultilineStart, Status::kDrop, ""},   // kQuote
        {State::kCommentMultilineStart, Status::kDrop, ""}    // kOtherwise
    },
    {
        // kStringInside
        {State::kStringInside, Status::kPrint, ""},  // kSlash
        {State::kStringEscape, Status::kPrint, ""},  // kEscape
        {State::kStringInside, Status::kPrint, ""},  // kStar
        {State::kStringInside, Status::kPrint, ""},  // kNewLine
        {State::kCode, Status::kPrint, ""},          // kDoubleQuotes
        {State::kStringInside, Status::kPrint, ""},  // kQuote
        {State::kStringInside, Status::kPrint, ""}   // kOtherwise
    },
    {
        // kStringEscape
        {State::kStringInside, Status::kPrint, ""},  // kSlash
        {State::kStringInside, Status::kPrint, ""},  // kEscape
        {State::kStringInside, Status::kPrint, ""},  // kStar
        {State::kStringInside, Status::kPrint, ""},  // kNewLine
        {State::kStringInside, Status::kPrint, ""},  // kDoubleQuotes
        {State::kStringInside, Status::kPrint, ""},  // kQuote
        {State::kStringInside, Status::kPrint, ""}   // kOtherwise
    },
    {
        // kCharInside
        {State::kCharInside, Status::kPrint, ""},  // kSlash
        {State::kCharEscape, Status::kPrint, ""},  // kEscape
        {State::kCharInside, Status::kPrint, ""},  // kStar
        {State::kCharInside, Status::kPrint, ""},  // kNewLine
        {State::kCharInside, Status::kPrint, ""},  // kDoubleQuotes
        {State::kCode, Status::kPrint, ""},        // kQuote
        {State::kCharInside, Status::kPrint, ""}   // kOtherwise
    },
    {
        // kCharEscape
        {State::kCharInside, Status::kPrint, ""},  // kSlash
        {State::kCharInside, Status::kPrint, ""},  // kEscape
        {State::kCharInside, Status::kPrint, ""},  // kStar
        {State::kCharInside, Status::kPrint, ""},  // kNewLine
        {State::kCharInside, Status::kPrint, ""},  // kDoubleQuotes
        {State::kCharInside, Status::kPrint, ""},  // kQuote
        {State::kCharInside, Status::kPrint, ""}   // kOtherwise
    }};

class FileReader {
 public:
  FileReader(const char* filename) : fin_(filename) {
    if (!fin_.is_open()) {
      std::cerr << filename << " does not open!" << std::endl;
    }
  }
  ~FileReader() { fin_.close(); }

  char next_char() {
    fin_.get(current_char_);
    return current_char_;
  }
  char current_char() const { return current_char_; }
  bool eof() { return fin_.eof(); }
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
      case '\'':
        return Event::kQuote;
      case '\\':
        return Event::kEscape;
      default:
        return Event::kOtherwise;
    }
  }

 private:
  ifstream fin_;
  char current_char_;
};

int main() {
  State state = State::kCode;
  FileReader freader("../test.input.cc");
  std::ofstream fout("../test.output.cc");
  while (!freader.eof()) {
    int event = (int)freader.make_event();
    auto machine = state_machine[(int)state][event];
    if (machine.status == Status::kPrint) {
      fout << machine.ch << freader.current_char();
    }
    state = machine.state;
  }
  fout.close();

  return 0;
}
