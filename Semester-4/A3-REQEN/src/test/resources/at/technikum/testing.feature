Feature: SingleChoiceQQ
  As lector
  I want to add Single Choice Questions
  So that I can test basic knowledge
  
  Scenario: adding Single Choice Question
    When lector adds the quiz question "Which programming language is not a compiler language?"
    And lector adds the following answers:
      |anr|answer |
      |  1|chill  |
      |  2|c++    |
      |  3|python |
      |  4|go     |
    And marks answer 3 as correct answer
    Then "python" is the correct answer
    And the number of possible answers is 4
    But "go" is the wrong answer