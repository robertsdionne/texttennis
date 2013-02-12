(function() {
  var load = function() {
    setup();
    requestAnimationFrame(animate);
  };
  var animate = function() {
    update();
    draw();
    requestAnimationFrame(animate);
  };
  window.addEventListener('load', load, false);
})();
