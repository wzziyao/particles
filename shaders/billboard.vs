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
   
   vec3 d = -vec3(1.0, 1.0, 0.0) / 2.0f;
   mat4 TranslationMatrixOrigin = mat4(
      1.0, 0.0, 0.0, 0.0,
      0.0, 1.0, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0,
      d, 1.0
   );

   vec4 OriginalVector = TranslationMatrixOrigin * vec4(vPos, 1.0);

   mat4 ScaleMatrix = mat4(
      uSize, 0.0, 0.0, 0.0,
      0.0, uSize, 0.0, 0.0,
      0.0, 0.0, uSize, 0.0,
      0.0, 0.0, 0.0, 1.0
   );

   vec3 newPos = vec3(OriginalVector.x, OriginalVector.y, OriginalVector.z);
   vec3 y = vec3(0.0, 1.0, 0.0);
   vec3 z = normalize(uCameraPos - newPos);
   vec3 x = normalize(cross(y, z));
   mat4 RotationMatrix = mat4(
      x, 0.0,
      y, 0.0, 
      z, 0.0,
      0.0, 0.0, 0.0, 1.0
   );

   mat4 TranslationMatrixOffset = mat4(
      1.0, 0.0, 0.0, 0.0,
      0.0, 1.0, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0,
      uOffset, 1.0
   );
   
   gl_Position = uVP * TranslationMatrixOffset * RotationMatrix * ScaleMatrix * OriginalVector; 
}
