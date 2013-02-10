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
