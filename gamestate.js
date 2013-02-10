
/**
 * @constructor
 * @param {number} timestamp
 * @param {string} description
 * @param {boolean=} opt_isCommand
 */
var GameState = function(timestamp, description, opt_isCommand) {
  this.timestamp = timestamp;
  this.description = description;
  this.isCommand = opt_isCommand;
};


GameState.prototype.toDomNode = function(cursor, scrollBehavior) {
  if (cursor <= 0) {
    return document.createTextNode('');
  }
  if (this.isCommand) {
    var element = document.createElement('b');
    element.textContent = scrollBehavior.slice(this.description, 0, cursor);
    return element;
  } else {
    return document.createTextNode(scrollBehavior.slice(this.description, 0, cursor) + '\u00A0');
  }
};
