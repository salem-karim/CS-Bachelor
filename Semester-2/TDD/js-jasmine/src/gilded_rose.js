class Item {
  constructor(name, sellIn, quality) {
    this.name = name;
    this.sellIn = sellIn;
    this.quality = quality;
  }
}

class Shop {
  constructor(items = []) {
    this.items = items;
  }

  updateQuality() {
    this.items.forEach((item) => {
      if (item.name.includes("Sulfuras")) return;

      this.updateItemQuality(item);
      this.updateSellIn(item);

      if (item.sellIn < 0) {
        this.handleExpiredItem(item);
      }
    });

    return this.items;
  }

  updateItemQuality(item) {
    if (item.name.includes("Brie")) {
      this.increaseQuality(item, 1);
    } else if (item.name.includes("Backstage passes")) {
      this.updateBackstagePasses(item);
    } else {
      this.decreaseQuality(item, item.name.includes("Conjured") ? 2 : 1);
    }
  }

  updateBackstagePasses(item) {
    if (item.sellIn < 0) {
      item.quality = 0;
    } else {
      this.increaseQuality(item, 1);
      if (item.sellIn < 10) {
        this.increaseQuality(item, 1);
      }
      if (item.sellIn < 5) {
        this.increaseQuality(item, 1);
      }
    }
  }

  updateSellIn(item) {
    item.sellIn -= 1;
  }

  handleExpiredItem(item) {
    if (item.name.includes("Brie")) {
      this.increaseQuality(item, 1);
    } else if (item.name.includes("Backstage passes")) {
      item.quality = 0;
    } else {
      this.decreaseQuality(item, item.name.includes("Conjured") ? 2 : 1);
    }
  }

  increaseQuality(item, amount) {
    item.quality = Math.min(50, item.quality + amount);
  }

  decreaseQuality(item, amount) {
    item.quality = Math.max(0, item.quality - amount);
  }
}

// New export Syntax
export { Item, Shop };
