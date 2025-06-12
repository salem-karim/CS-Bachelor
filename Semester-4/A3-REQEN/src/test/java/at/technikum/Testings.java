package at.technikum;

import io.cucumber.java.en.*;
import io.cucumber.datatable.DataTable;

import java.util.List;
import java.util.Map;
import java.util.HashMap;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

class QuizQuestion {
  public String question;
  public Map<Integer, String> answers = new HashMap<>();
  public Integer correctAnswer;
}

public class Testings {

  QuizQuestion myQuizQuestion = new QuizQuestion();

  @When("lector adds the quiz question {string}")
  public void lectorAddsTheQuizQuestion(String arg0) {
    myQuizQuestion.question = arg0;
  }

  @And("lector adds the following answers:")
  public void lectorAddsTheFollowingAnswers(DataTable dataTable) {
    List<Map<String, String>> rows = dataTable.asMaps();
    for (Map<String, String> columns : rows)
      myQuizQuestion.answers.put(Integer.valueOf(columns.get("anr")), columns.get("answer"));
  }

  @And("marks answer {int} as correct answer")
  public void marksAnswerAsCorrectAnswer(int arg0) {
    myQuizQuestion.correctAnswer = arg0;
  }

  @Then("{string} is the correct answer")
  public void isTheCorrectAnswer(String arg0) {
    String actual = myQuizQuestion.answers.get(myQuizQuestion.correctAnswer);
    assertEquals(arg0, actual);
  }

  @And("the number of possible answers is {int}")
  public void theNumberOfPossibleAnswersIs(int arg0) {
    Integer expected = arg0;
    Integer actual = myQuizQuestion.answers.size();
    assertEquals(expected, actual);
  }

  @But("{string} is the wrong answer")
  public void isTheWrongAnswer(String arg0) {
    String actual = myQuizQuestion.answers.get(myQuizQuestion.correctAnswer);
    assertNotEquals(arg0, actual);
  }
}
