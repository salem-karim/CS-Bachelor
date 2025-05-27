// StringCalculator.js
function StringCalculator() {}
StringCalculator.prototype.add = function (dices) {
  let  result = 0;
  if (dices.length > 6) {
    return "no more than 6 numbers";
  } else if (dices.length == 0) {
    return 0;
  } else if (dices.length < 4) {
    return "needs at least 4 numbers";
  } else {
    dices.forEach(function (dice) {
      if (dice == 3 || dice == 5) {
        result += dice - 1;
      }
    });
  }
  return result;
};
