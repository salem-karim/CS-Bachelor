package at.technikum.studentmanagementsystem2;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Locale;
import java.util.ResourceBundle;

public class StudentManagementApplication extends Application {
  @Override
  public void start(Stage stage) throws IOException {
    Locale locale = new Locale.Builder().setLanguage("de").build();
    ResourceBundle i18n = ResourceBundle.getBundle("at.technikum.studentmanagementsystem2.i18n", locale);
    FXMLLoader fxmlLoader = new FXMLLoader(
        StudentManagementApplication.class.getResource("studentManagementWindow.fxml"), i18n);
    Scene scene = new Scene(fxmlLoader.load(), 640, 480);
    stage.setTitle(i18n.getString("main.title"));
    stage.setScene(scene);
    stage.show();
    stage.sizeToScene();
  }

  public static void main(String[] args) {
    launch();
  }
}
