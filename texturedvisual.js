/**
 * @param {WebGLProgram} program
 * @param {WebGLBuffer} buffer
 * @param {number} count
 * @param {WebGLTexture} texture
 */
var TexturedVisual = function(program, buffer, count, mode, texture) {
  this.program = program;
  this.buffer = buffer;
  this.count = count;
  this.mode = mode;
  this.texture = texture;
};


TexturedVisual.FRAGMENT_SHADER_SOURCE =
    'precision highp float;' +
    'uniform vec3 uniform_color;' +
    'uniform sampler2D uniform_texture;' +
    'varying vec2 varying_texture_coordinate;' +
    'void main() {' +
      'gl_FragColor = vec4(uniform_color, 1.0);' +
    '}';


TexturedVisual.VERTEX_SHADER_SOURCE =
    'uniform mat4 uniform_projection;' +
    'uniform vec3 uniform_position;' +
    'attribute vec3 attribute_position;' +
    'attribute vec2 attribute_texture_coordinate;' +
    'varying vec2 varying_texture_coordinate;' +
    'void main() {' +
      'gl_Position = uniform_projection * vec4(attribute_position + uniform_position, 1.0);' +
    '}';


/**
 * @param {WebGLRenderingContext} gl
 */
TexturedVisual.prototype.disable = function(gl) {
  gl.disableVertexAttribArray(gl.getAttribLocation(this.program, 'attribute_position'));
};


/**
 * @param {WebGLRenderingContext} gl
 */
TexturedVisual.prototype.draw = function(gl, projection, position) {
  gl.uniformMatrix4fv(gl.getUniformLocation(this.program, 'uniform_projection'), false, projection);
  gl.uniform3f(
      gl.getUniformLocation(this.program, 'uniform_position'), position.x, position.y, position.z);
  gl.uniform3f(
      gl.getUniformLocation(this.program, 'uniform_color'), this.color.x, this.color.y, this.color.z);
  gl.drawArrays(this.mode, 0, this.count);
};


/**
 * @param {WebGLRenderingContext} gl
 * @param {Float32Array} projection
 * @param {Vector} position
 */
TexturedVisual.prototype.enable = function(gl) {
  gl.useProgram(this.program);
  gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer);
  var attributePosition = gl.getAttribLocation(this.program, 'attribute_position');
  gl.vertexAttribPointer(attributePosition, 3, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(attributePosition);
};
