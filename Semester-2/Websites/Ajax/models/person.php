<?php
class Person
{
  public $id;
  public $firstname;
  public $lastname;
  public $email;
  public $phone;
  public $department;
  //Extension B
  public $status;
  public $country;

  function __construct($id, $fn, $ln, $mail, $phone, $dept, $status, $country)
  {
    $this->id = $id;
    $this->firstname = $fn;
    $this->lastname = $ln;
    $this->email = $mail;
    $this->phone = $phone;
    $this->department = $dept;
    //Extension B
    $this->status = $status;
    $this->country = $country;
  }
}
