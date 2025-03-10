package at.technikum.studentmanagementsystem2;

import at.technikum.studentmanagementsystem2.mediators.ButtonDisableSelectionMediator;
import at.technikum.studentmanagementsystem2.mediators.Mediator;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonBar;
import javafx.scene.control.TableView;

import javax.print.attribute.standard.Media;
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;

public class NewEditDeleteButtonBarController implements Initializable {

    @FXML
    private ButtonBar buttonBar;
    @FXML
    private Button newButton;
    @FXML
    private Button editButton;
    @FXML
    private Button deleteButton;

    private EventHandler newButtonListener;
    private EventHandler editButtonListener;
    private EventHandler deleteButtonListener;

    private TableView tableView;

    private ArrayList<Mediator> mediators = new ArrayList<>();

    public NewEditDeleteButtonBarController() {
    }

    public void setTableView(TableView tableView) {
        this.tableView = tableView;

        if (this.tableView != null) {
            this.mediators.add(new ButtonDisableSelectionMediator(this.editButton, this.tableView, true, false, true));
            this.mediators.add(new ButtonDisableSelectionMediator(this.deleteButton, this.tableView, true, false, false));
        }
    }

    public EventHandler getNewButtonListener() {
        return newButtonListener;
    }

    public void setNewButtonListener(EventHandler newButtonListener) {
        this.newButtonListener = newButtonListener;
    }

    public EventHandler getEditButtonListener() {
        return editButtonListener;
    }

    public void setEditButtonListener(EventHandler editButtonListener) {
        this.editButtonListener = editButtonListener;
    }

    public EventHandler getDeleteButtonListener() {
        return deleteButtonListener;
    }

    public void setDeleteButtonListener(EventHandler deleteButtonListener) {
        this.deleteButtonListener = deleteButtonListener;
    }

    public void onNew(ActionEvent event) {
        if (newButtonListener != null) {
            newButtonListener.handle(event);
        }
    }

    public void onEdit(ActionEvent event) {
        if (editButtonListener != null) {
            editButtonListener.handle(event);
        }
    }

    public void onDelete(ActionEvent event) {
        if (deleteButtonListener != null) {
            deleteButtonListener.handle(event);
        }
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        buttonBar.getProperties().put("newEditDeleteButtonBarController", this);
    }
}
