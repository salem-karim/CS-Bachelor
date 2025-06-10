Feature: Assigning quiz questions to courses
  As a Lecturer
  I want to assign quiz questions to one or more courses
  In order to reuse relevant content

  Scenario: Assign question to a single course
    Given I have created a quiz question
    When I open the course assignment panel
    And I select "Math" from the dropdown
    And I click "Assign"
    Then the question is added to the Math quiz bank

  Scenario: Assign question to multiple courses
    Given I have created a quiz question
    When I select "Math" and "Physics" from the course list
    And I click "Assign"
    Then the question appears in both courses' quiz banks

  Scenario: Courses appear in dropdown
    Given I open the assignment section
    Then I see a list of all courses I teach
    And I can search and select multiple courses
