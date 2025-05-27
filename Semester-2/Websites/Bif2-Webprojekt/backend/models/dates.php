<?php

class dates {
    public $ID;
    public $AppointmentID;
    public $date;
    public $startTime;
    public $endTime;

    function __construct($ID, $AppointmentID, $date, $startTime, $endTime){
        $this->ID = $ID;
        $this->AppointmentID = $AppointmentID;
        $this->date = $date;
        $this->startTime = $startTime;
        $this->endTime = $endTime;
    }
}