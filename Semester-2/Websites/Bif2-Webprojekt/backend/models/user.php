<?php

class user {
    public $ID;
    public $AppID;
    public $name;
    public $comment;

    function __construct($ID ,$AppID, $name, $comment){
        $this->ID = $ID;
        $this->AppID = $AppID;
        $this->name = $name;
        $this->comment = $comment;
    }

}