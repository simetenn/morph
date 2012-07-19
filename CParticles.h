#include <vector>
#include "CParticle.h"

class CParticles : public CParticle {
 public:
  CParticle();
  ~CParticle();

  
 protected:
  vector<CParticle*> Particles;
  
  

};
