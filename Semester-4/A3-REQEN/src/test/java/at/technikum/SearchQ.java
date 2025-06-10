package at.technikum;

import io.cucumber.java.en.*;

public class SearchQ {
  @Given("I have questions titled {string} and {string}")
  public void iHaveQuestionsTitledAnd(String arg0, String arg1) {
  }

  @When("I search for {string}")
  public void iSearchFor(String arg0) {
  }

  @Then("only {string} appears in the results")
  public void onlyAppearsInTheResults(String arg0) {
  }

  @Given("I have questions grouped by {string} and {string}")
  public void iHaveQuestionsGroupedByAnd(String arg0, String arg1) {
  }

  @When("I filter by {string}")
  public void iFilterBy(String arg0) {
  }

  @Then("only questions under {string} are shown")
  public void onlyQuestionsUnderAreShown(String arg0) {
  }

  @Given("I start typing {string}")
  public void iStartTyping(String arg0) {
  }

  @Then("the result list updates dynamically")
  public void theResultListUpdatesDynamically() {
  }

  @And("questions with {string} in the title or content are shown")
  public void questionsWithInTheTitleOrContentAreShown(String arg0) {
  }
}
