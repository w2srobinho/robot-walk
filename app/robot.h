#include "constants.h"

#include <GL/glut.h>
#include <vector>

namespace w2s 
{ 
  namespace robot
  {
    float acao = STOP;
    float acaoAtual = STOP;
    state estadoAtual = STOPPED;
    position posicaoAtual = CENTER;

    std::vector<float> angle(5, 0);       
    std::vector<float> angle_min({ 
      0.,     //       angle[TRONCO_Y]
      200.,   //       angle[BCO_DIR_X]
      160.,   //       angle[BCO_ESQ_X]
      170.,   //       angle[COXA_DIR_X]
      190.    //       angle[COXA_ESQ_X]
    });
    
    std::vector<float> angle_max({
      0.,     //       angle[TRONCO_Y]
      160.,   //       angle[BCO_DIR_X]
      200.,   //       angle[BCO_ESQ_X]
      190.,   //       angle[COXA_DIR_X]
      170.    //       angle[COXA_ESQ_X]
    });                                          

    /* define pointers to walking */
    GLUquadric *_tronco = nullptr;
    GLUquadric *_visao = nullptr;
    GLUquadric *_cabeca = nullptr;
    GLUquadric *_bracoDireito = nullptr;
    GLUquadric *_antebracoDireito = nullptr;
    GLUquadric *_bracoEsquerdo = nullptr;
    GLUquadric *_antebracoEsquerdo = nullptr;
    GLUquadric *_canelaDireita = nullptr;
    GLUquadric *_canelaEsquerda = nullptr;
    GLUquadric *_coxaEsquerda = nullptr;
    GLUquadric *_coxaDireita = nullptr;
    /*******************************/
    
    /* actions */
    void rotateRight()
    {
      switch (posicaoAtual)
      {
      case LEFT:
        angle[TRONCO_Y] = 0;
        posicaoAtual = CENTER;
        break;
      case CENTER:
        angle[TRONCO_Y] = -60;
        posicaoAtual = RIGHT;
        break;
      default:
        break;
      }
    }

    void rotateLeft()
    {
      switch (posicaoAtual)
      {
      case RIGHT:
        angle[TRONCO_Y] = 0;
        posicaoAtual = CENTER;
        break;
      case CENTER:
        angle[TRONCO_Y] = 60;
        posicaoAtual = LEFT;
        break;
      default:
        break;
      }
    }

    void run()
    {
      acaoAtual = RUN;
      estadoAtual = RUNNING;
      angle_max[COXA_DIR_X] = 210.0f;
      angle_min[COXA_DIR_X] = 150.0f;

      angle_max[COXA_ESQ_X] = 150.0f;
      angle_min[COXA_ESQ_X] = 210.0f;
    }

    void walk()
    {
      acaoAtual = WALK;
      estadoAtual = WALKING;
      angle_max[COXA_DIR_X] = 190.0f;
      angle_min[COXA_DIR_X] = 170.0f;

      angle_max[COXA_ESQ_X] = 170.0f;
      angle_min[COXA_ESQ_X] = 190.0f;
    }

    void stop()
    {
      acao = STOP;
      acaoAtual = STOP;
      estadoAtual = STOPPED;
    }

    void defineAnguloDosBracos()
    {
      angle_max[BCO_ESQ_X] = 200.0f;
      angle_min[BCO_ESQ_X] = 160.0f;

      angle_max[BCO_DIR_X] = 160.0f;
      angle_min[BCO_DIR_X] = 200.0f;
    }

    /*******************************/

    float getAngle(float min, float max, float t)
    {
      return static_cast<float>(((max - min) * sin(3.0f * M_PI * t)) + (0.5f * (min + max)));
    }

    void prepareAngles()
    {
      acao += acaoAtual;

      angle[BCO_DIR_X] = getAngle(angle_min[BCO_DIR_X], angle_max[BCO_DIR_X], acao);
      angle[BCO_ESQ_X] = getAngle(angle_min[BCO_ESQ_X], angle_max[BCO_ESQ_X], acao);

      angle[COXA_DIR_X] = getAngle(angle_min[COXA_DIR_X], angle_max[COXA_DIR_X], acao);
      angle[COXA_ESQ_X] = getAngle(angle_min[COXA_ESQ_X], angle_max[COXA_ESQ_X], acao);
    }

    /* member definitions */
    void tronco()
    {
      glPushMatrix();
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(_tronco, RAIO_DO_TRONCO, RAIO_DO_TRONCO * 1.5, ALTURA_DO_TRONCO, 10, 10);	//(*obj, base, top, height, slices, stacks)
      glPopMatrix();
    }

    void cabeca()
    {
      glPushMatrix();
        glTranslatef(0.0f, 0.5f * ALTURA_DA_CABECA, 0.0f);
        glScalef(RAIO_DA_CABECA, ALTURA_DA_CABECA, RAIO_DA_CABECA);
        gluSphere(_cabeca, 1.0f, 10, 10);
      glPopMatrix();
    }

    void visao()
    {
      glPushMatrix();
        glTranslatef(0.0f, 0.5f * ALTURA_DA_CABECA, 0.075f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(_visao, RAIO_DA_CABECA, RAIO_DA_CABECA, ALTURA_DA_CABECA / 2, 10, 10);
      glPopMatrix();
    }

    void ombro()
    {
      glPushMatrix();
        glScalef(RAIO_DAS_ARTICULACOES_DO_BRACO, RAIO_DAS_ARTICULACOES_DO_BRACO,
          RAIO_DAS_ARTICULACOES_DO_BRACO);
        gluSphere(_cabeca, 1.0f, 10, 10);
      glPopMatrix();
    }

    void cotovelo()
    {
      glPushMatrix();
        glScalef(RAIO_DAS_ARTICULACOES_DO_BRACO / 1.2f, RAIO_DAS_ARTICULACOES_DO_BRACO / 1.2f,
          RAIO_DAS_ARTICULACOES_DO_BRACO / 1.2f);
        gluSphere(_cabeca, 1.0f, 10, 10);
      glPopMatrix();
    }

    void mao()
    {
      glPushMatrix();
        glScalef(RAIO_DAS_ARTICULACOES_DO_BRACO / 1.3f, RAIO_DAS_ARTICULACOES_DO_BRACO / 1.3f,
          RAIO_DAS_ARTICULACOES_DO_BRACO / 1.3f);
        gluSphere(_cabeca, 1.0f, 10, 10);
      glPopMatrix();
    }

    void articulacaoDaCoxa()
    {
      glPushMatrix();
        glScalef(RAIO_DAS_ARTICULACOES_DA_PERNA, RAIO_DAS_ARTICULACOES_DA_PERNA,
          RAIO_DAS_ARTICULACOES_DA_PERNA);
        gluSphere(_cabeca, 1.0f, 10, 10);
      glPopMatrix();
    }

    void joelho()
    {
      glPushMatrix();
        glScalef(RAIO_DAS_ARTICULACOES_DA_PERNA, RAIO_DAS_ARTICULACOES_DA_PERNA,
          RAIO_DAS_ARTICULACOES_DA_PERNA);
        gluSphere(_cabeca, 1.0f, 10, 10);
      glPopMatrix();
    }

    void curvaDoOmbro()
    {
      glPushMatrix();
      glScalef(1.5f * RAIO_DO_TRONCO, 0.1f, 1.5f * RAIO_DO_TRONCO);
      gluSphere(_cabeca, 1.0f, 10, 10);
      glPopMatrix();
    }

    void bracoDireito()
    {
      glPushMatrix();
        glRotatef(-100.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(_bracoDireito, RAIO_DO_BRACO * 1.2f, RAIO_DO_BRACO, ALTURA_DO_BRACO, 10, 10);
      glPopMatrix();
    }

    void antebracoDireito()
    {
      glPushMatrix();
        glRotatef(-130.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(_antebracoDireito, RAIO_DO_ANTEBRACO * 1.1f, RAIO_DO_ANTEBRACO,
          ALTURA_DO_ANTEBRACO, 10, 10);
      glPopMatrix();
    }

    void bracoEsquerdo()
    {
      glPushMatrix();
        glRotatef(-100.0f, 1, 0, 0);
        gluCylinder(_bracoEsquerdo, RAIO_DO_BRACO * 1.2f, RAIO_DO_BRACO, ALTURA_DO_BRACO, 10, 10);
      glPopMatrix();
    }

    void antebracoEsquerdo()
    {
      glPushMatrix();
        glRotatef(-130.0f, 1, 0, 0);
        gluCylinder(_antebracoEsquerdo, RAIO_DO_ANTEBRACO * 1.1f, RAIO_DO_ANTEBRACO,
          ALTURA_DO_ANTEBRACO, 10, 10);
      glPopMatrix();
    }

    void coxaDireita()
    {
      glPushMatrix();
        glRotatef(-120.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(_coxaDireita, RAIO_DA_COXA * 1.2f, RAIO_DA_COXA, ALTURA_DA_COXA, 10, 10);
      glPopMatrix();
    }

    void canelaDireita()
    {
      glPushMatrix();
        glTranslatef(0.0f, -0.25f, -ALTURA_DA_COXA / 2);
        glRotatef(-70.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(_canelaDireita, RAIO_DA_CANELA, RAIO_DA_CANELA * 1.5f,
          ALTURA_DA_CANELA, 10, 10);
      glPopMatrix();
    }

    void coxaEsquerda()
    {
      glPushMatrix();
        glRotatef(-120.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(_coxaEsquerda, RAIO_DA_COXA * 1.2f, RAIO_DA_COXA, ALTURA_DA_COXA, 10, 10);
      glPopMatrix();
    }

    void canelaEsquerda()
    {
      glPushMatrix();
        glTranslatef(0.0f, -0.25f, -ALTURA_DA_COXA / 2);
        glRotatef(-70.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(_canelaEsquerda, RAIO_DA_CANELA, RAIO_DA_CANELA * 1.5f, 
          ALTURA_DA_CANELA, 10, 10);
      glPopMatrix();
    }
    /************************************************************************/

    /* body construct */
    void CabecaCompleta()
    {
      glPushMatrix();
        glTranslatef(0.0f, ALTURA_DO_TRONCO + 0.5f * ALTURA_DA_CABECA, 0.0f);
        glTranslatef(0.0f, -0.5f * ALTURA_DA_CABECA, 0.0f);
        cabeca();
        visao();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.0f, ALTURA_DO_TRONCO, 0.0f);
        curvaDoOmbro();
      glPopMatrix();
    }

    void Ombros()
    {
      glPushMatrix();
        /* left */
        glTranslatef(1.5f * RAIO_DO_TRONCO, 0.9f * ALTURA_DO_TRONCO, 0.0f);
        ombro();

        /* right */
        glTranslatef(-3.0f * RAIO_DO_TRONCO, 0.0f, 0.0f);
        ombro();
      glPopMatrix();
    }

    void BracoDireitoCompleto()
    {
      glPushMatrix();
        glTranslatef(-(RAIO_DO_TRONCO + RAIO_DO_BRACO), 0.9f * ALTURA_DO_TRONCO, 0.0f);
        glRotatef(angle[BCO_DIR_X], 1.0f, 0.0f, 0.0f);
        bracoDireito();

        glTranslatef(0.0f, ALTURA_DO_BRACO, -0.5f);
        cotovelo();
        antebracoDireito();

        glTranslatef(0.0f, ALTURA_DO_ANTEBRACO - 0.5f, -1.3f);
        mao();
      glPopMatrix();
    }

    void BracoEsquerdoCompleto()
    {
      glPushMatrix();
        glTranslatef(RAIO_DO_TRONCO + RAIO_DO_BRACO, 0.9f * ALTURA_DO_TRONCO, 0.0f);
        glRotatef(angle[BCO_ESQ_X], 1.0f, 0.0f, 0.0f);
        bracoEsquerdo();

        glTranslatef(0.0f, ALTURA_DO_BRACO, -0.5f);
        cotovelo();
        antebracoEsquerdo();
        
        glTranslatef(0.0f, ALTURA_DO_ANTEBRACO - 0.5f, -1.3f);
        mao();
      glPopMatrix();
    }

    void ArticulacoesDaCoxa()
    {
      glPushMatrix();
        /* left  */
        glTranslatef(1.1f * RAIO_DO_TRONCO, 0.0f, 0.0f);
        articulacaoDaCoxa();

        /* right */
        glTranslatef(-2.2f * RAIO_DO_TRONCO, 0.0f, 0.0f);
        articulacaoDaCoxa();
      glPopMatrix();
    }

    void PernaDireita()
    {
      glPushMatrix();
        glTranslatef(-(RAIO_DO_TRONCO), 0.1f * ALTURA_DA_COXA, 0.0f);
        glRotatef(angle[COXA_DIR_X], 1.0f, 0.0f, 0.0f);
        coxaDireita();

        glTranslatef(0.0f, ALTURA_DA_COXA, -1.5f);
        joelho();

        glTranslatef(0.0f, 0.0f, 1.5f);
        canelaDireita();
      glPopMatrix();
    }

    void PernaEsquerda()
    {
      glPushMatrix();
        glTranslatef(RAIO_DO_TRONCO, 0.1f * ALTURA_DA_COXA, 0.0f);
        glRotatef(angle[COXA_ESQ_X], 1.0f, 0.0f, 0.0f);
        coxaEsquerda();

        glTranslatef(0.0f, ALTURA_DA_COXA, -1.5f);
        joelho();
        
        glTranslatef(0.0f, 0.0f, 1.5f);
        canelaEsquerda();
      glPopMatrix();
    }
    /************************************************************************/

    void alocatePointers()
    {
      _cabeca = gluNewQuadric();
      gluQuadricDrawStyle(_cabeca, GLU_FILL);

      _tronco = gluNewQuadric();
      gluQuadricDrawStyle(_tronco, GLU_FILL);

      _visao = gluNewQuadric();
      gluQuadricDrawStyle(_visao, GLU_FILL);

      _bracoDireito = gluNewQuadric();
      gluQuadricDrawStyle(_bracoDireito, GLU_FILL);

      _antebracoDireito = gluNewQuadric();
      gluQuadricDrawStyle(_antebracoDireito, GLU_FILL);

      _bracoEsquerdo = gluNewQuadric();
      gluQuadricDrawStyle(_bracoEsquerdo, GLU_FILL);

      _antebracoEsquerdo = gluNewQuadric();
      gluQuadricDrawStyle(_antebracoEsquerdo, GLU_FILL);

      _coxaDireita = gluNewQuadric();
      gluQuadricDrawStyle(_coxaDireita, GLU_FILL);

      _canelaDireita = gluNewQuadric();
      gluQuadricDrawStyle(_canelaDireita, GLU_FILL);

      _coxaEsquerda = gluNewQuadric();
      gluQuadricDrawStyle(_coxaEsquerda, GLU_FILL);

      _canelaEsquerda = gluNewQuadric();
      gluQuadricDrawStyle(_canelaEsquerda, GLU_FILL);
    }

    void init()
    {
      defineAnguloDosBracos();
      stop();

      alocatePointers();
    }

  }
}