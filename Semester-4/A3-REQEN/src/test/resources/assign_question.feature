Feature: Assigning quiz questions to courses
  In order to reuse relevant content
  As a Lecturer
  I want to assign quiz questions to one or more courses

  Scenario: Assign question to a single course
    Given I have created a quiz question
    When I open the course assignment panel
    And I select "Math 101" from the dropdown
    And I click "Assign"
    Then the question is added to the Math 101 quiz bank

  Scenario: Assign question to multiple courses
    Given I have created a quiz question
    When I select "Math 101" and "Physics 101" from the course list
    And I click "Assign"
    Then the question appears in both courses' quiz banks

  Scenario: Courses appear in dropdown
    Given I open the assignment section
    Then I see a list of all courses I teach
    And I can search and select multiple courses
