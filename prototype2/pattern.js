
/**
 * @constructor
 * @param {Array.<string>} tokens
 */
var Pattern = function(tokens) {
  /**
   * @type {Array.<string>}
   */
  this.tokens = tokens;

  /**
   * @private
   * @type {RegExp}
   */
  this.regularExpression_ = null;
};


/**
 * @private
 * @return {RegExp}
 */
Pattern.prototype.getRegularExpression_ = function() {
  if (!this.regularExpression_) {
    this.regularExpression_ = new RegExp(this.tokens.join(''));
  }
  return this.regularExpression_;
};


/**
 * @param {Array.<Event>} log
 */
Pattern.prototype.exec = function(log) {
  return this.getRegularExpression_().exec(log.join(''));
};


/**
 * @param {Array.<Event>} log
 */
Pattern.prototype.test = function(log) {
  return this.getRegularExpression_().test(log.join(''));
};
