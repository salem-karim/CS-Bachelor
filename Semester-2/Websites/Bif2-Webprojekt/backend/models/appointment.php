<?php

/*include("dates.php");
include("user.php");*/
class Appointment {
    public $id;
    public $title;
    public $location;
    public $endDate;
    public $description;

    function __construct($id, $title, $location, $endDate, $description) {
        $this->id = $id;
        $this->title = $title;
        $this->location = $location;
        $this->endDate = $endDate;
        $this->description =$description;
      }
}