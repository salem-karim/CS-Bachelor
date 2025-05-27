<?php
include("businesslogic/simpleLogic.php");

$param = "";
$method = "";

if ($_SERVER["REQUEST_METHOD"] == "POST"){
    isset($_POST["method"]) ? $method = $_POST["method"] : false;
    isset($_POST["param"]) ? $param = $_POST["param"] : false;
} else {
    isset($_GET["method"]) ? $method = $_GET["method"] : false;
    isset($_GET["param"]) ? $param = $_GET["param"] : false;
}

$logic = new SimpleLogic();
$result = $logic->handleRequest($method, $param);

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if ($result === null || (isset($result["success"]) && $result["success"] === false)) {
        response("POST", 400, $result);
    } else {
        response("POST", 200, $result);
    }
} elseif ($_SERVER["REQUEST_METHOD"] == "GET") {
    if ($result === null) {
        //User can not make mistakes in GET requests
        //response("GET", 404, null);
        // Our argumentation here, that it simply returns an empty result, which in itself is not an error
    } else {
        response("GET", 200, $result);
    }
}

function response($method, $httpStatus, $data)
{
    header('Content-Type: application/json');
    switch ($method) {
        case "GET":
        case "POST":
            http_response_code($httpStatus);
            echo (json_encode($data));
            break;
        default:
            http_response_code(405);
            echo ("Method not supported yet!");
    }
}