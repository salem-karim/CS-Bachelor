<?php

class vote{
    public $ForeignDate;
    public $VotedName;

    function __construct($ForeignDate, $VotedName){
        $this->ForeignDate = $ForeignDate;
        $this->VotedName = $VotedName;
    }

}