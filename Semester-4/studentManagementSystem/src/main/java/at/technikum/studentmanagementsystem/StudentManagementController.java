package at.technikum.studentmanagementsystem;

import java.net.URL;
import java.util.ResourceBundle;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;

public class StudentManagementController implements Initializable {
  @FXML
  private Label welcomeText;

  @FXML
  private Button newButton;

  @FXML
  private Button editButton;

  @FXML
  private Button deleteButton;

  @FXML
  private TableView studentTable;

  @FXML
  private TableColumn idColumn;

  @FXML
  private TableColumn nameColumn;

  @FXML
  private TableColumn semesterColumn;

  @FXML
  protected void onHelloButtonClick() {
    welcomeText.setText("Welcome to JavaFX Application!");
  }

  @Override
  public void initialize(URL location, ResourceBundle resources) {

  }
}
