<?php
include("models/appointment.php");
include("models/dates.php");
include("models/user.php");
include("models/vote.php");


class DataHandler
{
    public $host = "localhost";
    public $user = "root";
    public $password = "";
    public $database = "appointmentfinder";
    public $db_obj;

    public function insertAppointment($param) {  //declares function
        if ($param != null) {                    //checks for parameter value
            $Title = $param['title'];            //Assigns to local variables
            $Location = $param['location'];
            $EndDate = $param['enddate'];
            $Description = $param['description'];
        
            $sql = "INSERT INTO appointments (Title, Location, EndDate, Description) VALUES (?, ?, ?, ?)"; //defines sql query; database insertion
            $stmt = $this->db_obj->prepare($sql);   //prepares sql query an creates statement object
            $stmt->bind_param("ssss", $Title, $Location, $EndDate, $Description); //binds parameter to sql query(s for string, i for integer)
        
            if ($stmt->execute()) { //statement execution 
                $response = array("success" => true, "message" => "Appointment made successfully!");
            } else {
                $response = array("success" => false, "message" => "Error: " . $stmt->error);
            }
        
            $stmt->close(); //closes prepared statement
            $this->db_obj->close(); //closes database connection
            return $response; //return response from execution
        } else {
            return null;    //if param equals null, return null
        }
    }

    public function insertDate($param) {  //as above in insertAppointment-Commentation
        if ($param != null){
            $ID = $param['id'];
            $StartTime = $param['starttime'];
            $EndTime = $param['endtime'];
            $Date = $param['date'];
        
            $sql = "INSERT INTO optiondate (AppointmentID, StartTime, EndTime, Date) VALUES (?, ?, ?, ? )";
            $stmt = $this->db_obj->prepare($sql);
            $stmt->bind_param("isss", $ID, $StartTime, $EndTime, $Date);
        
            if ($stmt->execute()) {
                $response = array("success" => true, "message" => "Date created Successfully!");
            } else {
                $response = array("success" => false, "message" => "Error: " . $stmt->error);
            }
        
            $stmt->close();
            $this->db_obj->close();
            return $response;
        } else {
            return null;
        }
    }

    public function insertComment($param) {       //as above in insertAppointment-Commentation 
        if ($param != null){
            $AppID = $param['AppID'];
            $Name = $param['name'];
            $Comment = $param['comment'];
        
            $sql = "INSERT INTO user (AppID, Name, Comment) VALUES (?, ?, ?)";
            $stmt = $this->db_obj->prepare($sql);
            $stmt->bind_param("iss", $AppID, $Name, $Comment);
        
            if ($stmt->execute()) {
                $response = array("success" => true, "message" => "Comment created Successfully!");
            } else {
                $response = array("success" => false, "message" => "Error: " . $stmt->error);
            }
        
            $stmt->close();
            $this->db_obj->close();
            return $response;
        } else {
            return null;
        }
    }

    public function insertVote($param) {       //as above in insertAppointment-Commentation 
        if ($param != null){
            $ForeignDate = $param['ForeignDate'];
            $VotedName = $param['VotedName']; 
        
            $sql = "INSERT INTO hasvoted (ForeignDate, VotedName) VALUES (?, ?)";
            $stmt = $this->db_obj->prepare($sql);
            $stmt->bind_param("is", $ForeignDate, $VotedName);
        
            if ($stmt->execute()) {
                $response = array("success" => true, "message" => "Voted Successfully!");
            } else {
                $response = array("success" => false, "message" => "Error: " . $stmt->error);
            }
        
            $stmt->close();
            $this->db_obj->close();
            return $response;
        } else {
            return null;
        }
    }

    public function queryVote(){ //as above in insertAppointment-Commentation
            $votes = array();   //defines an empty array

            $sql = "SELECT * FROM hasvoted"; //queries from database
            $stmt = $this->db_obj->prepare($sql);
            $stmt->execute();
            $result = $stmt->get_result();

            if ($result->num_rows > 0) { //while database is not empty
                while ($row = $result->fetch_assoc()) { //iterates through the table and fetches every row
                    $votes[] = 
                        new vote($row['ForeignDate'], $row['VotedName']);    //assignes values from every table-entry to array
                }
                $result->free();
                $stmt->close();
                $this->db_obj->close();
                return $votes;
            } else {
                echo "Error: " . $this->db_obj->error; //displays error-message
                $stmt->close();
                $this->db_obj->close();
                return null;
            }
    }

    public function queryAppointments() { //as above in insertAppointment and queryVotes-Commentation; takes no parameter as it fetches every appointment
        $appointments = array();
        
        $sql = "SELECT * FROM appointments";
        $result = $this->db_obj->query($sql);
        
        if ($result) {
            while ($row = $result->fetch_assoc()) {
                $appointments[] = array( //made a double array by mistake, net to rewrite datahandling in order to fix
                    new Appointment($row['ID'], $row['Title'], $row['Location'], $row['EndDate'], $row['Description'])
                );
            }
            $result->free();
            $this->db_obj->close();
            return $appointments;
        } else {
            echo "Error: " . $this->db_obj->error;
            $this->db_obj->close();
            return null;
        }
    }

    public function queryDates($param) { //as above in insertAppointment and queryVotes-Commentation;
        if($param != null) {
            $OptionDates = array();
            
            $sql = "SELECT * FROM optiondate WHERE AppointmentID = ?";
            $stmt = $this->db_obj->prepare($sql);
            $stmt->bind_param("i", $param);
            $stmt->execute();
            $result = $stmt->get_result();
            
            if ($result->num_rows > 0) {
                while ($row = $result->fetch_assoc()) {
                    $OptionDates[] = 
                        new dates($row['ID'], $row['AppointmentID'], $row['Date'], $row['StartTime'], $row['EndTime']);    
                }
                $result->free();
                $stmt->close();
                $this->db_obj->close();
                return $OptionDates;
            } else {
                echo "Error: " . $this->db_obj->error;
                $stmt->close();
                $this->db_obj->close();
                return null;
            }
        }
    }
    public function queryComment($param) { //as above in insertAppointment and queryVotes-Commentation;
        if($param != null) {
            $User = array();
            
            $sql = "SELECT * FROM user WHERE AppID = ?";
            $stmt = $this->db_obj->prepare($sql);
            $stmt->bind_param("i", $param);
            $stmt->execute();
            $result = $stmt->get_result();
            
            if ($result->num_rows > 0) {
                while ($row = $result->fetch_assoc()) {
                    $User[] = new user($row['ID'], $row['AppID'], $row['Name'], $row['Comment']);
                }
                $result->free();
                $stmt->close();
                $this->db_obj->close();
                return $User;
            } else {
                echo "Error: " . $this->db_obj->error;
                $stmt->close();
                $this->db_obj->close();
                return null;
            }
        }
    }

    function __construct(){ //connects to database
        $this->db_obj = new mysqli($this->host, $this->user, $this->password, $this->database);
    }
}