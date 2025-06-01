describe("Spaceship finder", function () {
  beforeEach(function () {
    finder = new findSapceship();
  });

  it('should return "Spaceship lost forever" for an empty string', function () {
    expect(finder.add("")).toEqual("Spaceship lost forever");
  });

  it('should return Spaceship found at [7, 2] for string: "..........\n..........\n..........\n.......X..\n..........\n.........."', function () {
    expect(
      finder.add(
        "..........\n..........\n..........\n.......X..\n..........\n..........",
      ),
    ).toEqual("Spaceship found at [7, 2]");
  });

  it('should return Spaceship found at [4, 5] for string: "....X.....\n..........\n..........\n..........\n..........\n.........."', function () {
    expect(
      finder.add(
        "....X.....\n..........\n..........\n..........\n..........\n..........",
      ),
    ).toEqual("Spaceship found at [4, 5]");
  });

  it('should return Spaceship found at [0, 0] for string: "..........\n..........\n..........\n..........\n..........\nX........."', function () {
    expect(
      finder.add(
        "..........\n..........\n..........\n..........\n..........\nX.........",
      ),
    ).toEqual("Spaceship found at [0, 0]");
  });

  it('should return Spaceship found at [2, 3] for string: "..........\n..........\n..X.......\n..........\n..........\n.........."', function () {
    expect(
      finder.add(
        "..........\n..........\n..X.......\n..........\n..........\n..........",
      ),
    ).toEqual("Spaceship found at [2, 3]");
  });

  it('should return Spaceship found at [9, 4] for string: "..........\n.........X\n..........\n..........\n..........\n.........."', function () {
    expect(
      finder.add(
        "..........\n.........X\n..........\n..........\n..........\n..........",
      ),
    ).toEqual("Spaceship found at [9, 4]");
  });

  it('should return Spaceship lost forever for string: "..........\n..........\n..........\n..........\n..........\n..........', function () {
    expect(
      finder.add(
        "..........\n..........\n..........\n..........\n..........\n..........",
      ),
    ).toEqual("Spaceship lost forever");
  });
});
