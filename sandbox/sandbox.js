var box;
var x = 0, y = 0;

var setup = function() {
  box = document.getElementById('box');
};


var update = function() {
  x = (x + 1) % window.innerWidth;
};


var draw = function() {
  box.style['-webkit-transform'] = 'perspective(1000px) translate3d(' + x + 'px, ' + x + 'px, ' + -100*x + 'px)';
};
