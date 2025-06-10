Feature: Creating multiple-choice quiz questions
  As a Lecturer
  I want to create multiple-choice quiz questions
  In order to assess students’ understanding with multiple correct answers

  Scenario: Create a multiple-choice question with two correct answers
    Given I am creating a multiple-choice question
    When I enter the question text
    And I add four options
    And I mark two of them as correct
    And I click "Save"
    Then the question is saved with two correct answers

  Scenario: Validation fails when less than two answers are provided
    Given I am creating a multiple-choice question
    When I enter the question text
    And I only add one answer option
    And I try to save the question
    Then an error is displayed
    And the question is not saved

  Scenario: Preview shows multiple correct answers
    Given I have saved a multiple-choice question
    When I click "Preview"
    Then all options are shown
    And multiple correct answers are shown
