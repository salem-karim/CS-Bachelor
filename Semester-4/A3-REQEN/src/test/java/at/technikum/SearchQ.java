package at.technikum;

import io.cucumber.java.en.*;

public class SearchQ {
  @Given("the database contains questions titled {string} and {string}")
  public void theDatabaseContainsQuestionsTitledAnd(String arg0, String arg1) {
  }

  @When("I input the search query {string}")
  public void iInputTheSearchQuery(String arg0) {
  }

  @Then("only the entry titled {string} is returned in the result set")
  public void onlyTheEntryTitledIsReturnedInTheResultSet(String arg0) {
  }

  @Given("questions are tagged with subject areas {string} and {string}")
  public void questionsAreTaggedWithSubjectAreasAnd(String arg0, String arg1) {
  }

  @When("I apply the subject filter {string}")
  public void iApplyTheSubjectFilter(String arg0) {
  }

  @Then("only records associated with {string} are displayed")
  public void onlyRecordsAssociatedWithAreDisplayed(String arg0) {
  }

  @Given("I begin entering the keyword {string} in the search field")
  public void iBeginEnteringTheKeywordInTheSearchField(String arg0) {
  }

  @Then("the result list refreshes in real-time")
  public void theResultListRefreshesInRealTime() {
  }

  @And("all entries with {string} in the title or body are included in the output")
  public void allEntriesWithInTheTitleOrBodyAreIncludedInTheOutput(String arg0) {
  }
}
