Feature: Creating single-choice quiz questions
  In order to assess students' knowledge with one correct answer
  As a Lecturer
  I want to create single-choice quiz questions

  Scenario: Create a single-choice question with one correct option
    Given I am on the "Create Question" page
    And I select "Single Choice" as the question type
    When I enter the question text "What is 2 + 2?"
    And I enter answer options "2", "3", "4"
    And I mark "4" as the correct answer
    And I click "Save"
    Then the question is saved successfully
    And I can preview it with only one correct answer

  Scenario: Validation fails when no correct answer is selected
    Given I am on the "Create Question" page
    When I enter a question and answer options
    And I do not select any correct answer
    And I click "Save"
    Then an error message is displayed
    And the question is not saved

  Scenario: Preview displays the correct format
    Given I have saved a single-choice question
    When I click "Preview"
    Then I see the question text
    And I see all answer options with one marked as correct
