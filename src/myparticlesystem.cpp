// Bryn Mawr College, alinen, 2020
//

#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include "myparticlesystem.h"

using namespace std;
using namespace agl;
using namespace glm;

void MyParticleSystem::createParticles(int size) 
{
   mTexture = theRenderer.loadTexture("../textures/particle.png");
   for (int i = 0; i < size; i++) {
     Particle newParticle = {initPos, random_unit_vector(), vec4(random_unit_vector(), 1.0f), 0.1f, 0.5f, random_float() + 1.0f};
     mParticles.push_back(newParticle);
   }
}

void MyParticleSystem::update(float dt)
{
   for (int i = 0; i < mParticles.size(); i++) {
      Particle current = mParticles[i];

      if (current.life < 0.0){
			mParticles[i] = {initPos, random_unit_vector(), vec4(random_unit_vector(), 1.0f), 0.1f, 0.5f, random_float() + 1.0f};
		} else {
         current.vel -= vec3(0.0, 9.8*0.5, 0.0) * dt;
         current.pos += current.vel * dt;
         current.life -= dt;
         mParticles[i] = current;
      }
  }

  // selection sort
  int i, j, min_idx; 
  
  for (i = 0; i < mParticles.size()-1; i++) { 
      min_idx = i; 
      for (j = i+1; j < mParticles.size(); j++) 
      if (mParticles[j].pos.z < mParticles[min_idx].pos.z) 
            min_idx = j; 

      swap(mParticles[min_idx], mParticles[i]); 
   }
}

void MyParticleSystem::setInitPos(glm::vec3 pos) {
   initPos = pos;
}