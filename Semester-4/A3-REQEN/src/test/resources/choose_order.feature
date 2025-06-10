Feature: Choosing question order in a quiz
  As a Lecturer
  I want to choose between fixed or randomized question order
  So that I can manage quiz fairness and control difficulty

  Scenario: Toggle is available during quiz creation
    Given I am on the "Create Quiz" page
    Then I see an option to choose between "Fixed Order" and "Randomized Order"

  Scenario: Rearranging quiz question order after creation
    Given I have already created a quiz with multiple questions
    And I am on the "Edit Quiz" page
    When I drag and drop questions to a new order
    And I save the updated quiz
    Then the quiz reflects the new question order
    And students will see the updated order when taking the quiz

  Scenario: Student sees randomized order
    Given a quiz is configured with randomized question order
    When a student starts the quiz
    Then the question order differs from the original defined order
