#version 400

layout (location = 0) in vec3 vPos;

uniform vec3 uCameraPos;
uniform float uSize;
uniform vec3 uOffset;
uniform vec4 uColor;
uniform mat4 uVP;

out vec4 color;
out vec2 uv;

void main()
{
   color = uColor;
   uv = vPos.xy;
   
   vec3 d = uOffset - (uSize / 2.0f);
   mat4 TranslationMatrix = mat4(
      1.0, 0.0, 0.0, 0.0,
      0.0, 1.0, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0,
      d, 1.0
   );

   mat4 ScaleMatrix = mat4(
      uSize, 0.0, 0.0, 0.0,
      0.0, uSize, 0.0, 0.0,
      0.0, 0.0, uSize, 0.0,
      0.0, 0.0, 0.0, 1.0
   );


   vec4 OriginalVector = vec4(vPos, 1.0);
   
   gl_Position = TranslationMatrix * ScaleMatrix * OriginalVector; 
}
