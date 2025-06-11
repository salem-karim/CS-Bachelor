#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// 1. Define the Maybe monad
template <typename ValueType> struct Maybe {
  const optional<ValueType> value;

  // Constructor
  Maybe(optional<ValueType> val) : value(val) {}

  typedef function<optional<ValueType>(const ValueType)> OperationType;

  // Apply operation if value exists, otherwise return nullopt
  optional<ValueType> apply(const OperationType operation) const {
    if (value == nullopt)
      return nullopt;
    return operation(value.value());
  }

  // Chain operations (monadic bind)
  template <typename NewType>
  Maybe<NewType>
  bind(function<optional<NewType>(const ValueType)> operation) const {
    if (value == nullopt)
      return Maybe<NewType>(nullopt);
    return Maybe<NewType>(operation(value.value()));
  }
};

// 2. Lambda function to read letters from a file
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

// 3. Immutable function to extract words from text
auto extractWords = [](const string &text) -> vector<string> {
  vector<string> words;
  string word;

  for (size_t i = 0; i < text.size(); ++i) {
    char ch = text[i];

    // Accept only letters and apostrophes inside words (for contractions like
    // "don't")
    if (isalpha(static_cast<unsigned char>(ch)) ||
        (ch == '\'' && !word.empty() && i + 1 < text.size() &&
         isalpha(static_cast<unsigned char>(text[i + 1])))) {
      word += ch;
    } else if (!word.empty()) {
      // End of word - add it to the list
      words.push_back(word);
      word.clear();
    }
  }

  // Don't forget the last word if the text doesn't end with punctuation
  if (!word.empty())
    words.push_back(word);

  return words;
};

// 4. Lambda function to count words in text
auto countWords = [](const string &text) -> optional<int> {
  vector<string> words = extractWords(text);
  // cout << endl << "Words found: ";
  // for (size_t i = 0; i < words.size(); ++i) {
  //   cout << "'" << words[i] << "'";
  //   if (i < words.size() - 1)
  //     cout << ", ";
  // }
  cout << endl;
  return static_cast<int>(words.size());
};

// to_string lambda for optional<int>
auto to_string_optional = [](optional<int> value) -> string {
  return (value.has_value()) ? to_string(value.value()) : "None";
};

// 5. Main function to demonstrate usage
int main() {
  string filename = "_1/input.txt";
  cout << "Attempting to read from file: " << filename << endl << endl;

  // Create Maybe monad with file content
  Maybe<string> maybeContent{readLettersFromFile(filename)};

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
