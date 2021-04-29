// Bryn Mawr College, alinen, 2020
//

#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include "confetti.h"

using namespace std;
using namespace agl;
using namespace glm;

void Confetti::createParticles(int size) 
{
   mTexture = theRenderer.loadTexture("../textures/particle.png");
   for (int i = 0; i < size; i++) {
     Particle newParticle = {random_unit_cube(), random_unit_vector(), vec4(random_unit_vector(), 1.0), 0.25f, 1.0f};
     mParticles.push_back(newParticle);
   }
}

void Confetti::update(float dt)
{
  for (int i = 0; i < mParticles.size(); i++) {
    Particle current = mParticles[i];
    vec3 pos = current.pos;
    vec3 vel = current.vel;
    if (pos.x <= -1 || pos.x >= 1) vel.x = -vel.x;
    if (pos.y <= -1 || pos.y >= 1) vel.y = -vel.y;
    if (pos.z <= -1 || pos.z >= 1) vel.z = -vel.z;
    current.pos = pos + vel * dt;
    current.vel = vel;
    mParticles[i] = current;
  }

  vec3 camPos = theRenderer.cameraPosition();
  for (int j = 1; j < mParticles.size(); j++) {
    float d2 = length(camPos - mParticles[j].pos);
    float d1 = length(camPos - mParticles[j-1].pos);
    if (d2 < d1) {
      Particle temp = mParticles[j];
      mParticles[j] = mParticles[j-1];
      mParticles[j-1] = temp;
    }
  }
}

