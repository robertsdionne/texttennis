var Line = function(gameStates) {
  this.gameStates = gameStates;
};


Object.defineProperties(Line.prototype, {
  "timestamp": {
    get: function() {
      return this.gameStates.map(function(state) {
        return state.timestamp;
      }).reduce(function(timestamp0, timestamp1) {
        return Math.min(timestamp0, timestamp1);
      });
    }
  },
  "description": {
    get: function() {
      return this.gameStates.map(function(state) {
        return state.description;
      }).join(' ');
    }
  }
});


Line.prototype.toDomNode = function(prefix, cursor, scrollBehavior) {
  var index = scrollBehavior.indexInto(this, cursor);
  var element = document.createElement('p');
  element.appendChild(document.createTextNode(prefix));
  this.gameStates.forEach(function(state) {
    element.appendChild(state.toDomNode(cursor, scrollBehavior));
    cursor -= scrollBehavior.length(state.description);
  });
  return element;
};
