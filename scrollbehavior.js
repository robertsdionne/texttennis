/**
 * @interface
 */
var ScrollBehavior = function() {};


/**
 * @param {string} value
 * @return {number} the length
 */
ScrollBehavior.prototype.length = function(value) {};


/**
 * @param {string} value
 * @param {number} start
 * @param {number} stop
 * @return {string}
 */
ScrollBehavior.prototype.slice = function(value, start, stop) {};
