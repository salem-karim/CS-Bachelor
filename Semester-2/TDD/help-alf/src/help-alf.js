// StringCalculator.js
function findSapceship() {}
findSapceship.prototype.add = function (map) {
  grid = map.split("\n").reverse();
  result = "Spaceship lost forever";
  grid.forEach((row, rowIndex) => {
    if (row.includes("X")) {
      console.log(row);
      console.log(row.indexOf("X"));
      console.log(rowIndex);
      result = `Spaceship found at [${row.indexOf("X")}, ${rowIndex}]`;
      return;
    }
  });

  return result;
};
