$(document).ready(() => {
  // Select the necessary HTML elements for the interactive list using jQuery
  const [$input, $list, $addButton, $hideButton] = [
    "#input",
    "ol",
    "#add",
    "#toggle",
  ].map((q) => $(q));

  // Function to add a new item to the list
  const addItem = (text) => {
    // Create a new list item element with text and three buttons for delete, move up, and move down
    const $newItem = $("<li>").append(
      "<button>x</button><button>↑</button><button>↓</button>",
      " ",
      text,
    );
    // Hide the new item, append it to the list, and fade it in
    $newItem.hide().appendTo($list).fadeIn();
    // Clear the input field
    $input.val("");
  };

  $list.on("click", "button", function() {
    // event listener,ordered list element, clicks, button elements
    const $clicked = $(this),
      $parent = $clicked.parent();
    // 0 delete 1 up 2 down

    if ($clicked.index() === 0) {
      // delete (index 0), fade out display message
      $parent.fadeOut(() => $parent.remove());
    } else if ($clicked.index() === 1) {
      $parent.insertBefore($parent.prev()); // index 1 up
    } else $parent.insertAfter($parent.next()); // index 2 down
  });

  // event listener addItem function input field
  $addButton.on("click", () => addItem($input.val()));

  // same, hide visib
  $hideButton.on("click", () => $list.slideToggle());
});
