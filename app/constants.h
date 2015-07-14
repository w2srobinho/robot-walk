
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

namespace w2s
{ 
  enum rotate_axis {
    TRONCO_Y = 0,
    BCO_DIR_X,
    BCO_ESQ_X,
    COXA_DIR_X,
    COXA_ESQ_X
  };

  enum state
  {
    STOPPED,
    WALKING,
    RUNNING
  };

  enum position
  {
    CENTER,
    RIGHT,
    LEFT
  };

  const int ESC_KEY = 27;
  const int A_KEY   = 97;
  const int D_KEY   = 100;
  const int S_KEY   = 115;
  const int W_KEY   = 119;

  const float STOP = 0.;
  const float RUN = 0.02f;
  const float WALK = 0.005f;

  const float ALTURA_DO_TRONCO = 5.f;
  const float RAIO_DO_TRONCO = 1.3f;

  const float ALTURA_DA_CABECA = 1.7f;
  const float RAIO_DA_CABECA = 1.3f;

  const float ALTURA_DO_BRACO = 3.f;
  const float ALTURA_DO_ANTEBRACO = 2.f;

  const float RAIO_DO_BRACO = 0.65f;
  const float RAIO_DO_ANTEBRACO = 0.5f;

  const float ALTURA_DA_CANELA = 3.f;
  const float ALTURA_DA_COXA = 3.f;

  const float RAIO_DA_COXA = 0.65f;
  const float RAIO_DA_CANELA = 0.5f;
  
  const float RAIO_DAS_ARTICULACOES_DO_BRACO = 0.85f;
  const float RAIO_DAS_ARTICULACOES_DA_PERNA = 0.85f;
}