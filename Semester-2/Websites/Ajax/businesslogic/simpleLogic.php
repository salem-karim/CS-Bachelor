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
      case "queryPersons":
        $res = $this->dh->queryPersons();
        break;
      case "queryPersonById":
        $res = $this->dh->queryPersonById($param);
        break;
      case "queryPersonByName":
        $res = $this->dh->queryPersonByName($param);
        break;
        //Extension B 
      case "queryPersonByDepartment":
        $res = $this->dh->queryPersonByDepartment($param);
        break;
      case "queryPersonByStatus":
        $res = $this->dh->queryPersonByStatus($param);
        break;
      case "queryPersonByCountry":
        $res = $this->dh->queryPersonByCountry($param);
        break;

      default:
        $res = null;
        break;
    }
    return $res;
  }
}
