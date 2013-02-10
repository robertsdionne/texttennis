var LINE_COUNT = 25;
var SCROLL_DELAY = 80;

var t = 0.0;
var stack = [new GameState(t, "Text Tennis")];
var lineCursor = 0;
var characterCursor = 0;
var container;
var commandline;
var lastScrollTime = new Date().getTime();
var load = function() {
  document.addEventListener('mousewheel', mousewheel, false);
  document.addEventListener('keypress', command, false);
  document.addEventListener('keydown', backspace, false);
  container = document.getElementById('container');
  commandline = document.getElementById('commandline');
};
var scrollDown = function() {
  stack.push(new GameState(t += 1, "The time is " + t + "."));
  while (lineCursor < stack.length - LINE_COUNT) {
    lineCursor += 1;
  }
  display();
};
var scrollUp = function() {
  var state = stack.pop();
  t = state.timestamp - 1;
  if (lineCursor > 0) {
    lineCursor -= 1;
  }
  display();
};
var mousewheel = function(e) {
  var time = new Date().getTime();
  if (time - lastScrollTime > SCROLL_DELAY) {
    if (e.wheelDelta < 0) {
      scrollDown();
    } else if (e.wheelDelta > 0) {
      scrollUp();
    }
    lastScrollTime = time;
  }
  e.preventDefault();
};
var backspace = function(e) {
  if (e.keyCode == KeyCode.BACKSPACE) {
    commandline.textContent = commandline.textContent.slice(0, -1);
    e.preventDefault();
  } else if (e.keyCode == KeyCode.LEFT) {
    commandline.textContent = commandline.textContent.slice(0, -1);
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
  stack.slice(lineCursor).forEach(function(state) {
    var content = document.createTextNode();
    content.textContent = state.description;
    var newline = document.createElement('br');
    container.appendChild(content);
    container.appendChild(newline);
  });
};
window.addEventListener('load', load, false);
