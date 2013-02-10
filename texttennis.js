var LINE_COUNT = 25;
var SCROLL_DELAY = 80;
var CHARACTER_CURSOR_INCREMENT = 1;

var t = 0.0;
var stack = [new GameState(t, 'Text Tennis')];
var lineCursor = 0;
var characterCursor = 'Text Tennis'.length;
var container;
var commandline;
var scrollBehavior = new PerWordScrollBehavior();
var load = function() {
  document.addEventListener('mousewheel', mousewheel, false);
  document.addEventListener('keypress', command, false);
  document.addEventListener('keydown', backspace, false);
  container = document.getElementById('container');
  commandline = document.getElementById('commandline');
};
var scrollDown = function() {
  if (stack.length && characterCursor < scrollBehavior.length(stack[stack.length - 1].description)) {
    characterCursor += CHARACTER_CURSOR_INCREMENT;
  } else {
    characterCursor = CHARACTER_CURSOR_INCREMENT;
    stack.push(new GameState(t += 1, "The time is " + t + "."));
    while (lineCursor < stack.length - LINE_COUNT) {
      lineCursor += 1;
    }
  }
  display();
};
var scrollUp = function() {
  if (characterCursor > CHARACTER_CURSOR_INCREMENT) {
    characterCursor -= CHARACTER_CURSOR_INCREMENT;
  } else {
    var state = stack.pop();
    if (state) {
      characterCursor = scrollBehavior.length(state.description);
      t = state.timestamp - 1;
      if (lineCursor > 0) {
        lineCursor -= 1;
      }
    }
  }
  display();
};
var mousewheel = function(e) {
  if (e.wheelDelta < 0) {
    scrollDown();
  } else if (e.wheelDelta > 0) {
    scrollUp();
  }
  e.preventDefault();
};
var backspace = function(e) {
  if (e.keyCode == KeyCode.BACKSPACE) {
    commandline.textContent = commandline.textContent.slice(0, -1);
    e.preventDefault();
  } else if (e.keyCode == KeyCode.UP) {
    scrollUp();
  } else if (e.keyCode == KeyCode.DOWN) {
    scrollDown();
  }
};
var command = function(e) {
  if (e.keyCode == KeyCode.RETURN) {
    if (commandline.textContent) {
      stack.push(new GameState(t += 1, 'You did "' + commandline.textContent + '."'));
      commandline.textContent = '';
      display();
    }
  } else {
    commandline.textContent = commandline.textContent + String.fromCharCode(e.keyCode);
  }
};
var display = function () {
  while (container.childNodes.length) {
    container.removeChild(container.childNodes[0]);
  }
  stack.slice(lineCursor, stack.length - 1).forEach(function(state) {
    var content = document.createTextNode();
    content.textContent = state.description;
    var newline = document.createElement('br');
    container.appendChild(content);
    container.appendChild(newline);
  });
  if (stack.length) {
    var content = document.createTextNode();
    content.textContent = scrollBehavior.slice(stack[stack.length - 1].description, 0, characterCursor);
    var newline = document.createElement('br');
    container.appendChild(content);
    container.appendChild(newline);
  }
};
window.addEventListener('load', load, false);
