//Starting point for JQuery init
$(document).ready(function() {
  //Hide everything first
  $(".appointment-form").hide();
  $(".option-form").hide();
  $(".option-list").hide();
  //Show the Form to add a new Appointment and hide the list of appointments
  $("#btn_New-Appointment").click(function() {
    $(".appointment-list").hide(1000);
    $(".appointment-form").show(1000);
  });
  //The same thing but for the option form
  $("#btn_New-Option").click(function() {
    $(".option-list").hide(1000);
    $(".option-form").show(1000);
  });
  //Goes back to the list of appointments from the option list
  $("#btn_Back").click(function() {
    $(".option-list").hide(1000);
    $(".appointment-list").show(1000);
    $("#comments-collapse").collapse("hide");
  });
  //Goes back to the list of appointments from the appointment form
  $("#btn_BackToApp").click(function() {
    $(".appointment-form").hide(1000);
    $(".appointment-list").show(1000);
  });
  //Goes back to the option list from the option form
  $("#btn_BackToOpt").click(function() {
    $(".option-form").hide(1000);
    $(".option-list").show(1000);
  });
  //Loads the Appointment list
  loadAppointments();
  //Loads the Options list for the selected appointment with the votes and comments usign the appointmentId
  $(document).on("click", ".details", function() {
    //appointmentId = $(this).parent().attr("id");
    var appointmentId = $(this).parent().attr("id");
    //console.log(appointmentId);
    $(".appointment-list").hide(1000);
    $(".option-list").show(1000);
    loadOptions(appointmentId);
    loadComments(appointmentId);
    loadVotes(appointmentId);
  });

  //Form in submit check Validity and if so add the appointment using the Appointment object
  $("#appointment-form").submit(function(event) {
    // Preventing the Browser from submitting the form by default
    event.preventDefault();
    // Check if the form is valid according to HTML validation
    if (this.checkValidity() === false) {
      //With preventDefault prevents the Form from submitting even further when invalid form is detected
      event.stopPropagation();
    } else {
      //else make the Appointment Object and call the addAppointment function with it
      var Appointment = {
        title: $("#title").val(),
        location: $("#location").val(),
        enddate: $("#enddate").val(),
        description: $("#description").val(),
      };
      //console.log(Appointment);
      addAppointment(Appointment);
    }
  });
  //Same thing for Option Form but this time it also checks if the start time is before the end time
  $("#option-form").submit(function(event) {
    event.preventDefault();
    if ($("#starttime").val() >= $("#endtime").val()) {
      alert("Please enter a valid time range");
      event.stopPropagation();
    } else if (this.checkValidity() === false) {
      event.stopPropagation();
    } else {
      var appointmentId = $(".option-list").attr("id");
      //console.log(appointmentId);
      var Option = {
        id: appointmentId,
        starttime: $("#starttime").val(),
        endtime: $("#endtime").val(),
        date: $("#date").val(),
      };
      //console.log(Option);
      addOption(Option);
    }
  });
  //Also similar but checks if a comment has been written or a checkbox has been checked
  $("#vote-form").submit(function(event) {
    event.preventDefault();
    if (this.checkValidity() === false) {
      event.stopPropagation();
    } else {
      // Check if either a comment has been written or a checkbox has been checked
      var isCommentWritten = $("#comment").val().trim() !== "";
      var CheckedList = checkboxControl();
      var isCheckboxChecked = CheckedList.length > 0;
      var appointmentId = $(".option-list").attr("id");

      if (!isCommentWritten && !isCheckboxChecked) {
        event.stopPropagation();
        return;
      }
      if (isCheckboxChecked) {
        // If Form is valid, add Vote for every Id in the CheckedList
        for (var i = 0; i < CheckedList.length; i++) {
          var Vote = {
            VotedName: $("#name").val(),
            ForeignDate: CheckedList[i],
          };
          addVote(Vote);
        }
        $(".option-list .option input[type='checkbox']").prop("checked", false);
        loadVotes(appointmentId);
      }
      if (isCommentWritten) {
        // If the form is valid, add the Comment
        var User = {
          AppID: appointmentId,
          name: $("#name").val(),
          comment: $("#comment").val(),
        };
        addComment(User);
      }
      $("#name").val("");
    }
  });
});

function checkboxControl() {
  //Iterates through option-list and checks if the checkboxes of options have been checked 
  //and appends their id to the checkedList and then reutrns it
  var checkedList = [];
  $(".option-list .option input[type='checkbox']").each(function() {
    if ($(this).is(":checked")) {
      var optionID = $(this).parent().attr("id");
      checkedList.push(optionID);
    }
  });
  return checkedList;
}

function addAppointment(Appointment) {
  //ajax Post request to add the appointment and then reloads the list of appointments
  //Also clears the inputs, hides the form and shows the list of appointments
  $.ajax({
    method: "POST",
    url: "../backend/serviceHandler.php",
    cache: false,
    data: { method: "insertAppointment", param: Appointment },
    dataType: "json",
    success: function(response) {
      //console.log(response);
      $("#searchResult").show(1000).delay(1000).hide(1000);
      $("#title").val("");
      $("#location").val("");
      $("#enddate").val("");
      $("#description").val("");

      $(".appointment-form").hide(1000);
      loadAppointments();
      $(".appointment-list").show(1000);
    },
  });
}

function loadAppointments() {
  //ajax Get request to load the appointments
  $(".appointment-list .appointment").remove();
  $.ajax({
    method: "GET",
    url: "../backend/serviceHandler.php",
    cache: false,
    data: { method: "queryAppointments", param: "" },
    dataType: "json",
    success: function(response) {
      //Foramts Date, makes a div with all the information of the appointment and appends it to the appointment-list
      //console.log(response);
      for (var i = 0; i < response.length; i++) {
        for (var j = 0; j < response[i].length; j++) {
          var formattedDate = formatDate(response[i][j]["endDate"]);
          var currentDate = new Date();
          var endDate = new Date(response[i][j]["endDate"]);
          endDate.setHours(23, 59, 0, 0);
          var isPast = endDate < currentDate;
          var appointmentContainer = $(
            `<div class='appointment border' id="${response[i][j]["id"]}" ></div>`,
          ); //isPast Class gets Grayed out and hides it form to submit Comments and votes
          if (isPast) {
            appointmentContainer.addClass("past");
          }
          var title = $("<h3>" + response[i][j]["title"] + "</h3>");
          appointmentContainer.append(title);
          var location = $(
            "<p>Location: " + response[i][j]["location"] + "</p>",
          );
          appointmentContainer.append(location);
          var enddate = $(
            `<p class="date" id="${response[i][j]["endDate"]}">Voting ends on ${formattedDate}</p>`,
          );
          appointmentContainer.append(enddate);
          var description = $(
            "<p>Description: " + response[i][j]["description"] + "</p>",
          );
          appointmentContainer.append(description);
          var options = $(
            "<button class='details btn btn-primary'>Details</button>",
          );
          appointmentContainer.append(options);
          $(".appointment-list").append(appointmentContainer);
        }
      }
    },
  });
}

function addOption(Option) {
  //ajax Post request to add the option and then reloads the list of options
  //Also clears the inputs, hides the form and shows the list of options
  var appointmentId = $(".option-list").attr("id");
  //console.log(Option);
  $.ajax({
    method: "POST",
    url: "../backend/serviceHandler.php",
    cache: false,
    data: { method: "insertDate", param: Option },
    dataType: "json",
    success: function(response) {
      //console.log(response);
    },
  });
  $("#starttime").val("");
  $("#endtime").val("");
  $("#date").val("");
  $(".option-form").hide(1000);
  $(".option-list").show(1000, function() {
    loadOptions(appointmentId);
  });
}

function loadOptions(appointmentId) {
  $(".option-list .option").remove();
  $("#name").val("");
  $("#comment").val("");
  var endDate = new Date(
    $(".appointment#" + appointmentId + " .date").attr("id"),
  ); //if the end date is in the past, hide the form to submit comments and votes
  var currentDate = new Date();
  endDate.setHours(23, 59, 0, 0);
  if (currentDate > endDate) {
    $("#vote-form").hide();
    $("#btn_New-Option").hide();
  } else {
    $("#vote-form").show();
    $("#btn_New-Option").show();
  }
  $(".option-list").attr("id", appointmentId);
  //ajax Get request to load the options for the selected appointment
  $.ajax({
    method: "GET",
    url: "../backend/serviceHandler.php",
    cache: false,
    data: { method: "queryDates", param: appointmentId },
    dataType: "json",
    success: function(response) {
      //console.log(response);
      //Foramts Date, makes a div with all the information of the option and appends it to the option-list
      for (var i = 0; i < response.length; i++) {
        response[i]["date"] = formatDate(response[i]["date"]);
        var optionContainer = $(
          `<div class='option border' id="${response[i]["ID"]}"></div>`,
        );
        var date = $("<p><b>Date</b>: " + response[i]["date"] + "</p>");
        optionContainer.append(date);
        var time = $(
          "<p><b>Time</b>: " +
          response[i]["startTime"] +
          "-" +
          response[i]["endTime"] +
          "</p>",
        );
        optionContainer.append(time);
        var checkbox = $(
          "<input type='checkbox' class='form-check-input' id='checkbox'>",
        );
        optionContainer.append(checkbox);
        $(".option-list").append(optionContainer);
      }
      // Call processVotes function after loading options
      loadVotes();
    },
  });
}

function addComment(User) {
  //console.log(User);
  //ajax Post request to add the comment and then reloads the list of comments
  var appointmentId = $(".option-list").attr("id");
  $.ajax({
    method: "POST",
    url: "../backend/serviceHandler.php",
    cache: false,
    data: { method: "insertComment", param: User },
    dataType: "json",
    success: function(response) {
      //console.log(response);
      $("#name").val("");
      $("#comment").val("");
      loadComments(appointmentId);
    },
  });
}

//appends comments-list consisting of each names and comments and appends it to the option-list
function loadComments(appointmentId) {
  //console.log(appointmentId);
  //ajax Get request to load the comments for the selected appointment
  $("#comment-list").empty();
  $.ajax({
    method: "GET",
    url: "../backend/serviceHandler.php",
    cache: false,
    data: { method: "queryComment", param: appointmentId },
    dataType: "json",
    success: function(response) {
      //console.log(response);
      for (var i = 0; i < response.length; i++) {
        var commentContainer = $("<div class='comment'></div>");
        var name = $("<label><b>" + response[i]["name"] + ": </b></label>");
        var comment = $("<span> " + response[i]["comment"] + "</span>");
        commentContainer.append(name).append(comment);
        $("#comment-list").append(commentContainer);
      }
    },
  });
}

function addVote(vote) {
  //console.log(vote);
  //Same as the other post requests but for votes
  $.ajax({
    method: "POST",
    url: "../backend/serviceHandler.php",
    cache: false,
    data: { method: "insertVote", param: vote },
    dataType: "json",
    success: function(response) {
      //console.log(response);
    },
  });
}

function loadVotes() {
  //ajax Get request to load the votes for the selected appointment
  //And then calls processVotes function
  $.ajax({
    method: "GET",
    url: "../backend/serviceHandler.php",
    cache: false,
    data: { method: "queryVote", param: "" },
    dataType: "json",
    success: function(response) {
      //console.log(response);
      processVotes(response);
    },
  });
}

function processVotes(response) {
  $(".option-list .option").each(function() {
    //Get the option ID and the existing dropdown menu
    var optionID = $(this).attr("id");
    var existingDropdown = $(this).find(".dropdown");

    // Check if a dropdown menu already exists for this option
    if (existingDropdown.length > 0) { 
      // Makes Copys of the already existing dropdown menu and button
      var dropdownButton = existingDropdown.find(".dropdown-toggle");
      var dropdownMenu = existingDropdown.find(".dropdown-menu");
      // Get the votes for the option with the optionID
      var votesForOption = response.filter(
        (item) => item["ForeignDate"] == optionID,
      ); //Gets the number of votes and appends it to the button
      var numOfVotes = votesForOption.length;
      dropdownButton.text(`${numOfVotes} Votes`);
      // Clear the existing dropdown menu
      dropdownMenu.empty();
      // Makes new list items for each vote and appends them to the new dropdown menu
      votesForOption.forEach(function(item) {
        var listItem = $(
          `<li><a class="dropdown-item" href="#">${item["VotedName"]}</a></li>`,
        );
        dropdownMenu.append(listItem);
      });
    } else {
      // Get the right votes for the option with the optionID
      var votesForOption = response.filter(
        (item) => item["ForeignDate"] == optionID,
      );  //Makes the new div and Button for the dropdown menu and appends it to the option
      if (votesForOption.length > 0) {
        var numOfVotes = votesForOption.length;
        var dropdown = $("<div class='dropdown'></div>");
        var dropdownButton = $(
          `<button class='btn btn-secondary dropdown-toggle' type='button' data-toggle='dropdown' aria-expanded='false'>${numOfVotes} Votes</button>`,
        );
        dropdown.append(dropdownButton);
        //Makes a unordered list and goes through the votes and appends them to the list as list items
        var ulElement = $('<ul class="dropdown-menu"></ul>');
        votesForOption.forEach(function(item) {
          var listItem = $(
            `<li><a class="dropdown-item" href="#">${item["VotedName"]}</a></li>`,
          );
          ulElement.append(listItem);
        });
        dropdown.append(ulElement);
        $(this).append(dropdown);
      }
    }
  });
  loadVotes();
}

//Didnt work before but withs it does ?
$(document).on("click", ".dropdown-toggle", function() {
  $(this).next(".dropdown-menu").toggle();
});

$(document).on("mouseleave", ".dropdown", function() {
  $(this).find(".dropdown-menu").hide();
});

function formatDate(isoDate) {
  //Gets a ISO date and makes it into a JS date object
  const date = new Date(isoDate);
  // Get the day of the week and format the date
  const dayOfWeek = new Intl.DateTimeFormat("en-US", {
    weekday: "long",
  }).format(date);
  // Get the month abbreviation
  const monthAbbreviation = new Intl.DateTimeFormat("en-US", {
    month: "short",
  }).format(date);
  // Get the day of the month
  const dayOfMonth = date.getDate();
  // Get the year
  const year = date.getFullYear();
  // Combine the formatted parts
  const formattedDate = `${dayOfWeek}, ${monthAbbreviation} ${dayOfMonth}, ${year}`;
  return formattedDate;
}
