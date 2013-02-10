var LINE_COUNT = 25;
var SCROLL_DELAY = 80;
var CHARACTER_CURSOR_INCREMENT = 1;

var t = 0.0;
var lines = [new Line([new GameState(t, 'Text Tennis')])];
var lineCursor = 0;
var characterCursor = lines[0] ? lines[0].description.length : 0;
var container;
var commandline;
var scrollBehavior = new PerWordScrollBehavior();
var load = function() {
  document.addEventListener('mousewheel', mousewheel, false);
  document.addEventListener('keypress', command, false);
  document.addEventListener('keydown', backspace, false);
  container = document.getElementById('container');
  commandline = document.getElementById('commandline');
  display();
};
var scrollDown = function() {
  if (lineCursor >= 0 && characterCursor < scrollBehavior.length(lines[lineCursor].description)) {
    characterCursor += CHARACTER_CURSOR_INCREMENT;
  } else {
    characterCursor = CHARACTER_CURSOR_INCREMENT;
    lines.push(new Line([
        makeClockState(t += 1),
        makeClockState(t += 1),
        makeClockState(t += 1),
        makeClockState(t += 1)
    ]));
    lineCursor += 1;
  }
  display();
};
var makeClockState = function(time) {
  var choice = Math.random() * 8;
  var description;
  if (0 <= choice && choice < 1) {
    description = 'The clock on the wall reads ';
  } else if (1 <= choice && choice < 2) {
    description = 'The time is ';
  } else if (2 <= choice && choice < 3) {
    description = 'The clock says ';
  } else if (3 <= choice && choice < 4) {
    description = 'The time reads ';
  } else if (4 <= choice && choice < 5) {
    description = 'You read the clock to be ';
  } else if (5 <= choice && choice < 6) {
    description = 'Clock\'s busy at ';
  } else if (6 <= choice && choice < 7) {
    description = 'Clock says ';
  } else if (7 <= choice && choice < 8) {
    description = 'Clock tells you ';
  }
  return new GameState(time, description + makeTime(time) + '.')
};
var makeTime = function(time) {
  var second = time % 60;
  var minute = Math.floor(time / 60) % 60;
  var hour = Math.floor(time / 3600) % 12;
  return hour + ':' + minute + ':' + second;
};
var scrollUp = function() {
  if (characterCursor > CHARACTER_CURSOR_INCREMENT) {
    characterCursor -= CHARACTER_CURSOR_INCREMENT;
  } else {
    var line = lines.pop();
    if (lines[lines.length - 1]) {
      characterCursor = scrollBehavior.length(lines[lines.length - 1].description);
      t = lines[lines.length - 1].timestamp - 1;
    }
    if (lineCursor >= 0) {
      lineCursor -= 1;
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
  } else if (e.keyCode == KeyCode.UP || e.keyCode == KeyCode.LEFT) {
    scrollUp();
  } else if (e.keyCode == KeyCode.DOWN || e.keyCode == KeyCode.RIGHT) {
    scrollDown();
  }
};
var command = function(e) {
  if (e.keyCode == KeyCode.RETURN) {
    if (commandline.textContent) {
      var line = new Line([new GameState(t += 1, 'You did "' + commandline.textContent + '."')]);
      characterCursor = scrollBehavior.length(line.description);
      lines[lineCursor] = line;
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
  var startIndex = lineCursor - LINE_COUNT >= 0 ? lineCursor - LINE_COUNT : 0;
  lines.slice(startIndex, lineCursor).forEach(function(line) {
    var content = document.createTextNode();
    content.textContent = line.description;
    var newline = document.createElement('br');
    container.appendChild(content);
    container.appendChild(newline);
  });
  if (lineCursor >= 0 && lines.length > lineCursor) {
    var content = document.createTextNode();
    content.textContent = scrollBehavior.slice(lines[lineCursor].description, 0, characterCursor);
    var newline = document.createElement('br');
    container.appendChild(content);
    container.appendChild(newline);
  }
};
window.addEventListener('load', load, false);
