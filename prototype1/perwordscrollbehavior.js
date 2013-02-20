/**
 * @constructor
 * @implements {ScrollBehavior}
 */
var PerWordScrollBehavior = function() {};


/**
 * @param {string} value
 * @return {number} the length
 */
PerWordScrollBehavior.prototype.length = function(value) {
  return value.split(' ').length;
};


/**
 * @param {string} value
 * @param {number} start
 * @param {number} stop
 * @return {string}
 */
PerWordScrollBehavior.prototype.slice = function(value, start, stop) {
  return value.split(' ').slice(start, stop).join(' ');
};


PerWordScrollBehavior.prototype.indexInto = function(line, cursor) {
  for (var i = 0; i < line.gameStates.length; ++i) {
    cursor -= this.length(line.gameStates[i].description);
    if (cursor < 0) {
      return i;
    }
  }
};
