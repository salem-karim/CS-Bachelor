module at.technikum.studentmanagementsystem2 {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;


    opens at.technikum.studentmanagementsystem2 to javafx.fxml;
    exports at.technikum.studentmanagementsystem2;
    exports at.technikum.studentmanagementsystem2.models;
    exports at.technikum.studentmanagementsystem2.mvvm;
}