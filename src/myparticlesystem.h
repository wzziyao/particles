#ifndef MyParticleSystem_H_
#define MyParticleSystem_H_

#include "particlesystem.h"

namespace agl {

   class MyParticleSystem : public ParticleSystem {
   public:
      virtual void createParticles(int size) override;
      virtual void update(float dt) override;
      void setInitPos(glm::vec3 pos);
   protected:
      glm::vec3 initPos = glm::vec3(0.0, 0.0, 0.0);
   };
}
#endif