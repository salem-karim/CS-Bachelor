const verlauf = [];

function add() {
  let a = document.getElementById("num1").value;
  let b = document.getElementById("num2").value;
  let result = parseFloat(a) + parseFloat(b);
  document.getElementById("ergebnis").innerText = result;
  verlauf.push(a + " + " + b + " = " + result);
  showHistory();
}

function sub() {
  let a = document.getElementById("num1").value;
  let b = document.getElementById("num2").value;
  let result = parseFloat(a) - parseFloat(b);
  document.getElementById("ergebnis").innerText = result;
  verlauf.push(a + " - " + b + " = " + result);
  showHistory();
}

function mul() {
  let a = document.getElementById("num1").value;
  let b = document.getElementById("num2").value;
  let result = parseFloat(a) * parseFloat(b);
  debugger;
  document.getElementById("ergebnis").innerText = result;
  verlauf.push(a + " * " + b + " = " + result);
  showHistory();
}

function div() {
  let a = document.getElementById("num1").value;
  let b = document.getElementById("num2").value;
  let result = parseFloat(a) / parseFloat(b);
  if (b == 0) {
    result = "Division by Zero";
  }
  document.getElementById("ergebnis").innerText = result;
  verlauf.push(a + " / " + b + " = " + result);
  showHistory();
}

function showHistory() {
  const history = document.getElementById("verlauf");
  history.innerHTML = "";
  for (let i = 0; i < verlauf.length; i++) {
    history.innerHTML += "<li>" + verlauf[i] + "</li>";
  }
}
