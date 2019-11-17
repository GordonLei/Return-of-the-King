uniform sampler2D diffuse;
varying vec2 texCoordVar;
void main() {
    vec4 color = texture2D(diffuse, texCoordVar);
    vec3 luminance = vec3(dot(vec3(0.2126,0.7152,0.0722), color.rgb));
    vec3 m = mix(luminance, color.rgb, 1.0);
    
    gl_FragColor = vec4(m, color.a);
    
}

/*
 uniform sampler2D diffuse;
 varying vec2 texCoordVar;
 void main() {
 vec4 color = texture2D(diffuse, texCoordVar);
 //c is for grayscale
 float c = (color.r + color.g + color.b) / 3.0;
 //gl_FragColor = vec4(c, c , c, color.a);
 //invert colors
 //gl_FragColor = vec4(1.0 - color.r, 1.0 - color.g , 1.0 - color.b, color.a);
 
 vec3 luminance = vec3(dot(vec3(0.2126,0.7152,0.0722), color.rgb));
 gl_FragColor = vec4(luminance, color.a);
 }
*/
