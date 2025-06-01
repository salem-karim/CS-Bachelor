//New Import Syntax
import { Shop, Item } from "../src/gilded_rose.js";
describe("Gilded Rose", function () {
  it("should return 0 for Item with Quality of 0", function () {
    const gildedRose = new Shop([new Item("foo", 5, 0)]);
    const items = gildedRose.updateQuality();
    expect(items[0].quality).toEqual(0);
  });
  it("should return 2 for Item with Quality 4 and sellin of -1", function () {
    const gildedRose = new Shop([new Item("foo", -1, 4)]);
    const items = gildedRose.updateQuality();
    expect(items[0].quality).toEqual(2);
  });
  it("should return 0 for Item with Quality 0 and sellin of -1", function () {
    const gildedRose = new Shop([new Item("foo", -1, 0)]);
    const items = gildedRose.updateQuality();
    expect(items[0].quality).toEqual(0);
  });
  it("should return 4 for Item with Quality 6 and sellin of 0", function () {
    const gildedRose = new Shop([new Item("foo", 0, 6)]);
    const items = gildedRose.updateQuality();
    expect(items[0].quality).toEqual(4);
  });
  it("should return 7 for Aged Brie with Quality 5 and sellin of 0", function () {
    const gildedRose = new Shop([new Item("Aged Brie", 0, 5)]);
    const items = gildedRose.updateQuality();
    expect(items[0].quality).toEqual(7);
  });
  it("should return 0 for Backstage Pass with Quality 5 and sellin of -1", function () {
    const gildedRose = new Shop([
      new Item("Backstage passes to a TAFKAL80ETC concert", -1, 5),
    ]);
    const items = gildedRose.updateQuality();
    expect(items[0].quality).toEqual(0);
  });
  it("should return 50 for Aged Brie with Quality 50 and sellin of 3", function () {
    const gildedRose = new Shop([new Item("Aged Brie", 3, 50)]);
    const items = gildedRose.updateQuality();
    expect(items[0].quality).toEqual(50);
  });
  it("should return 34 for Aged Brie with Quality 33 and sellin of 3", function () {
    const gildedRose = new Shop([new Item("Aged Brie", 3, 33)]);
    const items = gildedRose.updateQuality();
    expect(items[0].quality).toEqual(34);
  });
  it("should return 35 for Aged Brie with Quality 33 and sellin of -4", function () {
    const gildedRose = new Shop([new Item("Aged Brie", -4, 33)]);
    const items = gildedRose.updateQuality();
    expect(items[0].quality).toEqual(35);
  });
  it("should return 6 for Backstage Pass with Quality 5 and sellin of 15", function () {
    const gildedRose = new Shop([
      new Item("Backstage passes to a TAFKAL80ETC concert", 15, 5),
    ]);
    const items = gildedRose.updateQuality();
    expect(items[0].quality).toEqual(6);
  });
  it("should return 7 for Backstage Pass with Quality 5 and sellin of 9", function () {
    const gildedRose = new Shop([
      new Item("Backstage passes to a TAFKAL80ETC concert", 9, 5),
    ]);
    const items = gildedRose.updateQuality();
    expect(items[0].quality).toEqual(7);
  });
  it("should return 8 for Backstage Pass with Quality 5 and sellin of 4", function () {
    const gildedRose = new Shop([
      new Item("Backstage passes to a TAFKAL80ETC concert", 4, 5),
    ]);
    const items = gildedRose.updateQuality();
    expect(items[0].quality).toEqual(8);
  });
  it("should return 3 for Conjured Item with Quality 5 and sellin of 5", function () {
    const gildedRose = new Shop([new Item("Conjured Mana Cake", 5, 5)]);
    const items = gildedRose.updateQuality();
    expect(items[0].quality).toEqual(3);
  });
  it("should return 4 for Conjured Item with Quality 8 and sellin of -2", function () {
    const gildedRose = new Shop([new Item("Conjured Mana Cake", -2, 8)]);
    const items = gildedRose.updateQuality();
    expect(items[0].quality).toEqual(4);
  });
  it("should return 80 for Sulfuras Item with Quality 80 and sellin of -2", function () {
    const gildedRose = new Shop([
      new Item("Sulfuras, Hand of Ragnaros", -2, 80),
    ]);
    const items = gildedRose.updateQuality();
    expect(items[0].quality).toEqual(80);
  });
});
