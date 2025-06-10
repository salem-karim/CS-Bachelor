Feature: Grouping questions into subject areas
  In order to find and organize questions efficiently
  As a Lecturer
  I want to group questions into subject areas

  Scenario: Add a new subject area
    Given I am on the Subject Areas page
    When I click "Add Subject Area"
    And I enter "Algebra"
    Then a new subject area "Algebra" is created

  Scenario: Assign question to a subject area
    Given I have created a question
    When I assign it to "Calculus"
    Then the question is listed under the "Calculus" category

  Scenario: Rename and delete subject areas
    Given I have a subject area "Old Name"
    When I rename it to "New Name"
    Then "New Name" appears in the list

    When I delete the subject area "New Name"
    Then it is removed from the list
    And any associated questions are not deleted
