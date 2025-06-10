package at.technikum;

import io.cucumber.java.en.*;

public class SingleQ {
  @Given("I am on the {string} page")
  public void iAmOnThePage(String arg0) {
  }

  @And("I select {string} as the question type")
  public void iSelectAsTheQuestionType(String arg0) {
  }

  @When("I enter the question text {string}")
  public void iEnterTheQuestionText(String arg0) {
  }

  @And("I enter answer options {string}, {string}, {string}, and {string}")
  public void iEnterAnswerOptions(String arg0, String arg1, String arg2, String arg3) {
  }

  @And("I mark {string} as the correct answer")
  public void iMarkAsTheCorrectAnswer(String arg0) {
  }

  @And("I click {string}")
  public void iClick(String arg0) {
  }

  @Then("the question is saved successfully")
  public void theQuestionIsSavedSuccessfully() {
  }

  @And("I can preview it with only one correct answer")
  public void iCanPreviewItWithOnlyOneCorrectAnswer() {
  }

  @When("I enter a question and answer options")
  public void iEnterAQuestionAndAnswerOptions() {
  }

  @And("I do not select any correct answer")
  public void iDoNotSelectAnyCorrectAnswer() {
  }

  @Then("an error message is displayed")
  public void anErrorMessageIsDisplayed() {
  }

  @And("the question is not saved")
  public void theQuestionIsNotSaved() {
  }

  @Given("I have saved a single-choice question")
  public void iHaveSavedASingleChoiceQuestion() {
  }

  @Then("I see the question text")
  public void iSeeTheQuestionText() {
  }

  @And("I see all answer options with one marked as correct")
  public void iSeeAllAnswerOptionsWithOneMarkedAsCorrect() {
  }
}
