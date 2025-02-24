module at.technikum.studentmanagementsystem {
  requires javafx.controls;
  requires javafx.fxml;


  opens at.technikum.studentmanagementsystem to javafx.fxml;
  exports at.technikum.studentmanagementsystem;
}