<?php
include("db/dataHandler.php");

class SimpleLogic
{

    private $dh;

    function __construct()
    {
        $this->dh = new DataHandler();
    }

    function handleRequest($method, $param)
    {
        switch ($method) {

            case "insertDate": 
                $res = $this->dh->insertDate($param);
                break;

            case "insertAppointment" :
                $res = $this->dh->insertAppointment($param);
                break;

            case "queryAppointments":
                $res = $this->dh->queryAppointments();
                break;

            case "queryDates":
                $res = $this->dh->queryDates($param);
                break;
            
            case "insertComment": 
                $res = $this->dh->insertComment($param);
                break;
    
            case "insertVote" :
                $res = $this->dh->insertVote($param);
                break;
    
            case "queryComment":
                $res = $this->dh->queryComment($param);
                break;
    
            case "queryVote":
                $res = $this->dh->queryVote();
                break;

            default:
                $res = null;
                break;
        }
        return $res;
    }
}

