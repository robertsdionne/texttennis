/**
 * @constructor
 * @implements {ScrollBehavior}
 */
var PerCharacterScrollBehavior = function() {};


/**
 * @param {string} value
 * @return {number} the length
 */
PerCharacterScrollBehavior.prototype.length = function(value) {
  return value.length;
};


/**
 * @param {string} value
 * @param {number} start
 * @param {number} stop
 * @return {string}
 */
PerCharacterScrollBehavior.prototype.slice = function(value, start, stop) {
  return value.slice(start, stop);
};


PerCharacterScrollBehavior.prototype.indexInto = function(line, cursor) {
  for (var i = 0; i < line.gameStates.length; ++i) {
    cursor -= this.length(line.gameStates[i].description);
    if (cursor < 0) {
      return i;
    }
  }
};
