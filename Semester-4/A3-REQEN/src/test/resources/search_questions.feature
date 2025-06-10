Feature: Searching for quiz questions
  In order to quickly locate existing questions
  As a Lecturer
  I want to search for quiz questions using filters or keywords

  Scenario: Search by keyword in title
    Given I have questions titled "Photosynthesis Basics" and "Cell Division"
    When I search for "Photosynthesis"
    Then only "Photosynthesis Basics" appears in the results

  Scenario: Filter by subject area
    Given I have questions grouped by "Biology" and "Chemistry"
    When I filter by "Biology"
    Then only questions under "Biology" are shown

  Scenario: Results update instantly as user types
    Given I start typing "cell"
    Then the result list updates dynamically
    And questions with "cell" in the title or content are shown
