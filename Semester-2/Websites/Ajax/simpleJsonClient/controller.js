//Starting point for JQuery init
$(document).ready(function() {
  $("#searchResult").hide();
  $("#searchResult1").hide();
  $("#searchResult2").hide();
  $("#searchResult3").hide();
  $("#btn_Search").click(function(e) {
    loaddata($("#seachfield").val());
  });
});

function loaddata(searchterm) {
  $.ajax({
    type: "GET",
    url: "../serviceHandler.php",
    cache: false,
    data: { method: "queryPersonByName", param: searchterm },
    dataType: "json",
    success: function(response) {
      $("#names").empty();
      $("#noOfentries").val(response.length);
      $("#searchResult").show(1000).delay(1000).hide(1000);

      for (var i = 0; i < response.length; i++) {
        var li = $("<li>" + response[i][0]["firstname"] + "</li>");
        $("#names").append(li);
      }
    },
  });

  $.ajax({
    type: "GET",
    url: "../serviceHandler.php",
    cache: false,
    data: { method: "queryPersonByDepartment", param: searchterm },
    dataType: "json",
    success: function(response) {
      $("#departments").empty();
      $("#noOfentries1").val(response.length);
      $("#searchResult1").show(1000).delay(1000).hide(1000);

      for (var i = 0; i < response.length; i++) {
        var li = $(
          "<li>" +
          response[i][0]["firstname"] +
          " " +
          response[i][0]["lastname"] +
          "</li>",
        );
        $("#departments").append(li);
      }
    },
  });

  $.ajax({
    type: "GET",
    url: "../serviceHandler.php",
    cache: false,
    data: { method: "queryPersonByStatus", param: searchterm },
    dataType: "json",
    success: function(response) {
      $("#status").empty();
      $("#statuslabel").empty();
      $("#statuslabel").append("Number of People who are " + searchterm + ":");
      $("#noOfentries2").val(response.length);
      $("#searchResult2").show(1000).delay(1000).hide(1000);

      for (var i = 0; i < response.length; i++) {
        var li = $(
          "<li>" +
          response[i][0]["firstname"] +
          " " +
          response[i][0]["lastname"] +
          "</li>",
        );
        $("#status").append(li);
      }
    },
  });

  $.ajax({
    type: "GET",
    url: "../serviceHandler.php",
    cache: false,
    data: { method: "queryPersonByCountry", param: searchterm },
    dataType: "json",
    success: function(response) {
      $("#country").empty();
      $("#countrylabel").empty();
      $("#countrylabel").append("Number of People live in " + searchterm + ":");
      $("#noOfentries3").val(response.length);
      $("#searchResult3").show(1000).delay(1000).hide(1000);

      for (var i = 0; i < response.length; i++) {
        var li = $("<li>" + response[i][0]["firstname"] + "</li>");
        $("#country").append(li);
      }
    },
  });
}
