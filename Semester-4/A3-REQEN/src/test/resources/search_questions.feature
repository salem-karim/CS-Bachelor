Feature: Searching for quiz questions
  As a Lecturer
  I want to search for quiz questions using filter criteria or search queries
  In order to efficiently retrieve relevant question records

  Scenario: Search by keyword in title
    Given the database contains questions titled "Merge Sort Overview" and "Binary Search Trees"
    When I input the search query "Merge"
    Then only the entry titled "Merge Sort Overview" is returned in the result set

  Scenario: Filter by subject area
    Given questions are tagged with subject areas "Algorithms" and "Data Structures"
    When I apply the subject filter "Algorithms"
    Then only records associated with "Algorithms" are displayed

  Scenario: Dynamic result updates on input
    Given I begin entering the keyword "tree" in the search field
    Then the result list refreshes in real-time
    And all entries with "tree" in the title or body are included in the output
