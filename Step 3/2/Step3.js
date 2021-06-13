
var canvas;
var gl;
var program;

var points = [];
var indices = [];
var nFaces;

var axis = 0;
var xAxis = 0;
var yAxis = 1;
var zAxis = 2;
var theta = [0, 0, 0];

window.onload = function init()
{
    initGL();

    rectangle();

    initTexture();

    //event listeners for buttons

    document.getElementById("xButton").onclick = function () {
        axis = xAxis;
    };
    document.getElementById("yButton").onclick = function () {
        axis = yAxis;
    };
    document.getElementById("zButton").onclick = function () {
        axis = zAxis;
    };

    render();
}

function initGL()
{
    canvas = document.getElementById("gl-canvas");

    gl = WebGLUtils.setupWebGL(canvas);
    if (!gl) { alert("WebGL isn't available"); }

    gl.viewport(0, 0, canvas.width, canvas.height);
    gl.clearColor(1.0, 1.0, 1.0, 1.0);

    program = initShaders(gl, "vertex-shader", "fragment-shader");
    gl.useProgram(program);
}

function rectangle()
{
    points.push(vec3(0., 0., 0.));
    points.push(vec3(1., 0., 0.));
    points.push(vec3(1., 1., 0.));
    points.push(vec3(0., 1., 0.));

    points.push(vec3(0., 0.1, 0.));
    points.push(vec3(0.4, 0.1, 0.));
    points.push(vec3(0.4, 0.9, 0.));
    points.push(vec3(0., 0.9, 0.));
    points.push(vec3(1., 0.1, 0.));
    points.push(vec3(0.6, 0.1, 0.));
    points.push(vec3(0.6, 0.9, 0.));
    points.push(vec3(1., 0.9, 0.));

    points.push(vec3(0., 0., 0.2));
    points.push(vec3(1., 0., 0.2));
    points.push(vec3(1., 1., 0.2));
    points.push(vec3(0., 1., 0.2));

    points.push(vec3(0., 0.1, 0.2));
    points.push(vec3(0.4, 0.1, 0.2));
    points.push(vec3(0.4, 0.9, 0.2));
    points.push(vec3(0., 0.9, 0.2));
    points.push(vec3(1., 0.1, 0.2));
    points.push(vec3(0.6, 0.1, 0.2));
    points.push(vec3(0.6, 0.9, 0.2));
    points.push(vec3(1., 0.9, 0.2));

    indices.push([0, 1, 8]);
    indices.push([0, 4, 8]);

    indices.push([5, 6, 9]);
    indices.push([9, 10, 6]);

    indices.push([3, 2, 7]);
    indices.push([7, 11, 2]);

    indices.push([0+12, 1+12, 8+12]);
    indices.push([0+12, 4+12, 8+12]);

    indices.push([5+12, 6+12, 9+12]);
    indices.push([9+12, 10+12, 6+12]);

    indices.push([3+12, 2+12, 7+12]);
    indices.push([7+12, 11+12, 2+12]);

    indices.push([2, 3, 2+12]);
    indices.push([2+12, 3+12, 3]);

    indices.push([2, 11, 11+12]);
    indices.push([2+12, 11+12, 2]);

    nFaces = indices.length;

    //Create buffer to store the vertex coordinates
    var vBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(points), gl.STATIC_DRAW);

    //Link data to vertex shader input
    var vPosition = gl.getAttribLocation(program, "vPosition");
    gl.vertexAttribPointer(vPosition, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(vPosition);

    //Create buffer to store the triangle elements
    var tBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, tBuffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(flatten(indices)), gl.STATIC_DRAW);
}

var squareTexture;

function initTexture() {
    squareTexture = gl.createTexture();
    var squareImage = new Image();
    squareImage.onload = function () { handleTextureLoaded(squareImage, squareTexture); }
    squareImage.src = "Material/sunset.bmp";
}

function handleTextureLoaded(image, texture) {
    gl.bindTexture(gl.TEXTURE_2D, texture);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_NEAREST);
    gl.generateMipmap(gl.TEXTURE_2D);
    gl.bindTexture(gl.TEXTURE_2D, null);
}


function render()
{
    theta[axis] += 2.0;
    gl.uniform3fv(gl.getUniformLocation(program, "theta"), theta);

    gl.clear(gl.COLOR_BUFFER_BIT);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, squareTexture);
    gl.uniform1i(gl.getUniformLocation(program, "uSampler"), 0);

    gl.drawElements(gl.TRIANGLES, nFaces * 3, gl.UNSIGNED_SHORT, 0);

    requestAnimationFrame(render);
}
