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
     vec3 velocity = random_unit_vector();
     Particle newParticle = {random_unit_cube(), vec3(0.5*velocity.x, 0.5*velocity.y, 0.5*velocity.z), vec4(random_unit_vector(), 1.0), 0.1f, 1.0f};
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

  // selection sort
  int i, j, min_idx; 
  
  for (i = 0; i < mParticles.size()-1; i++) 
  { 
      min_idx = i; 
      for (j = i+1; j < mParticles.size(); j++) 
      if (mParticles[j].pos.z < mParticles[min_idx].pos.z) 
          min_idx = j; 

      swap(mParticles[min_idx], mParticles[i]); 
  }
}

