var input = prompt("Geben Sie Ihren Namen ein:");
var seconds = 1;
var tries = 0;
var prevoiusCardId = 0;
var cards = [];
createCards();

document.getElementById("player").textContent = input;
setInterval(countTimer, 1000);

function countTimer() {
  seconds++;
  document.getElementById("timer").textContent = seconds;
}

function incrementTries() {
  tries++;
  document.getElementById("tries").textContent = tries;
}

function createCards() {
  for (var i = 0; i < 16; i++) {
    cards[i] = document.createElement("div");
    cards[i].setAttribute("id", i + 1);
    cards[i].setAttribute("class", "karte");
    cards[i].addEventListener("click", clickCard);
  }
  shuffleCards();
  showCards();
}

function shuffleCards() {
  for (var i = 0; i < cards.length; i++) {
    const random = Math.floor(Math.random() * cards.length);
    var temp = cards[i];
    cards[i] = cards[random];
    cards[random] = temp;
  }
}

function showCards() {
  for (var i = 0; i < cards.length; i++) {
    document.getElementById("spielbereich").appendChild(cards[i]);
    if ((i + 1) % 4 === 0) {
      document
        .getElementById("spielbereich")
        .appendChild(document.createElement("br"));
    }
  }
}

function clickCard(event) {
  flipCard(event.target.id);
}

function flipCard(id) {
  var currentCard = document.getElementById(id);
  currentCard.style.backgroundImage = "url('pics/card" + id + ".png')";

  if (prevoiusCardId === 0) {
    currentCard.removeEventListener("click", clickCard);
    prevoiusCardId = id;
  } else {
    incrementTries();
    if (parseInt(prevoiusCardId) + parseInt(id) === 17) {
      document
        .getElementById(prevoiusCardId)
        .removeEventListener("click", clickCard);
      currentCard.removeEventListener("click", clickCard);
      setTimeout(function() {
        currentCard.style.backgroundImage = "url('pics/memoryBgI.png')";
        document.getElementById(prevoiusCardId).style.backgroundImage =
          "url('pics/memoryBgI.png')";
        prevoiusCardId = 0;
      }, 350);
    } else {
      document
        .getElementById(prevoiusCardId)
        .addEventListener("click", clickCard);
      currentCard.addEventListener("click", clickCard);
      setTimeout(function() {
        currentCard.style.backgroundImage = "url('pics/memoryBg.png')";
        document.getElementById(prevoiusCardId).style.backgroundImage =
          "url('pics/memoryBg.png')";
        prevoiusCardId = 0;
      }, 350);
    }
  }
}
