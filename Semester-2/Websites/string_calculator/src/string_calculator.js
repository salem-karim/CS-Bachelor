// StringCalculator.js
function StringCalculator() {}
StringCalculator.prototype.add = function (string_numbers) {
  let result = 0;
  if (string_numbers.includes(",")) {
    let numbers = string_numbers.split(",");
    numbers.forEach((number) => {
      if (!isNaN(number)) {
        result += Number(number);
      }
    });
  } else {
    result = Number(string_numbers);
  }
  return result;
};
