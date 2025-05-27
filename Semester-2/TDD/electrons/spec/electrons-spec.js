describe("String Calculator", function () {
  beforeEach(function () {
    calculator = new StringCalculator();
  });

  it("should return 0 for an empy number array", function () {
    expect(calculator.add([])).toEqual(0);
  });
  it("[1,2,3,4,5] should return 6", function () {
    expect(calculator.add([1, 2, 3, 4, 5])).toEqual(6);
  });
  it("[2,2,3,3] should return 4", function () {
    expect(calculator.add([2, 2, 3, 3])).toEqual(4);
  });
  it("[6,6,4,4,1,3] should return 2", function () {
    expect(calculator.add([6,6,4,4,1,3])).toEqual(2);
  });
  it("[3,5,3,5,4,2] should return 12", function () {
    expect(calculator.add([3, 5, 3, 5, 4, 2])).toEqual(12);
  });
  it("[3,5,3,5,4,2,5] should return 'no more than 6 numbers'", function () {
    expect(calculator.add([3, 5, 3, 5, 4, 2, 5])).toEqual(
      "no more than 6 numbers",
    );
  });
  it("[3,5,3] should return 'needs at least 4 numbers'", function () {
    expect(calculator.add([3, 5, 3])).toEqual("needs at least 4 numbers");
  });
});
