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
