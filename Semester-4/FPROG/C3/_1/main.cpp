#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Maybe Monad with bind operation
template <typename Type> struct Maybe {
  const optional<Type> value;

  Maybe(optional<Type> val) : value(val) {}

  // typedef
  using OperationType = function<optional<Type>(const Type)>;

  // Apply operation if value exists, otherwise return nullopt
  optional<Type> apply(const OperationType operation) const {
    if (value == nullopt)
      return nullopt;
    return operation(value.value());
  }

  // bind, make new Monad and bind the operation to it
  template <typename NewType>
  Maybe<NewType> bind(function<optional<NewType>(const Type)> operation) const {
    if (value == nullopt)
      return Maybe<NewType>(nullopt);
    return Maybe<NewType>(operation(value.value()));
  }
};

// read file into ifstram then into sstream and return its string
auto readLettersFromFile = [](const string &filename) -> optional<string> {
  ifstream file(filename);
  if (!file) {
    cout << "Error: Could not open file '" << filename << "'" << endl;
    return nullopt;
  }
  stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
};

// go through text and check for letters and words like don't
auto extractWords = [](const string &text) -> vector<string> {
  vector<string> words;
  string currentWord;

  for (size_t i = 0; i < text.size(); ++i) {
    char ch = text[i];

    // Accept only letters and apostrophes inside words (for contractions like
    // "don't")
    if (isalpha(static_cast<unsigned char>(ch)) ||
        // check for ' , currentWord is not empty and if its end of text
        (ch == '\'' && !currentWord.empty() && i + 1 < text.size() &&
         // also check if next char is an letter
         isalpha(static_cast<unsigned char>(text[i + 1])))) {
      currentWord += ch;
      // if its not a letter or ' and the word is not empty push to vector
    } else if (!currentWord.empty()) {
      // End of word - add it to the list
      words.push_back(currentWord);
      currentWord.clear();
    }
  }

  // Don't forget the last word if the text doesn't end with punctuation
  if (!currentWord.empty())
    words.push_back(currentWord);

  return words;
};

// call the function to extract words and return the size of the vector
auto countWords = [](const string &text) -> optional<int> {
  vector<string> words = extractWords(text);
  // cout << endl << "Words found: ";
  // for (size_t i = 0; i < words.size(); ++i) {
  //   cout << "'" << words[i] << "'";
  //   if (i < words.size() - 1)
  //     cout << ", ";
  // }
  cout << endl;
  return make_optional(static_cast<int>(words.size()));
};

// to_string lambda for optional<int>
auto to_string_optional = [](optional<int> value) -> string {
  return (value.has_value()) ? to_string(value.value()) : "None";
};

int main() {
  string filename = "_1/input.txt";
  cout << "Attempting to read from file: " << filename << endl << endl;

  // Create Maybe monad with file content
  Maybe<string> maybeContent{readLettersFromFile(filename)};

  // If it has content count the Words
  if (maybeContent.value.has_value()) {
    cout << "File content successfully read!" << endl;
    cout << "Content preview: \"" << maybeContent.value.value().substr(0, 50)
         << (maybeContent.value.value().length() > 50 ? "..." : "") << "\""
         << endl;

    // Use the monad to chain operations
    auto wordCount = maybeContent.bind<int>(countWords);

    cout << "Final word count: " << to_string_optional(wordCount.value) << endl;
  } else {
    cout << "Failed to read file content." << endl;
    cout << "Word count: None" << endl;
  }

  return 0;
}
