//
//  main.c
//  assetkit_render
//
//  Created by Recep Aslantas on 9/30/16.
//  Copyright © 2016 Recep Aslantas. All rights reserved.
//

#include "assetkit_test.h"

#include <assetkit.h>  /* importer               */
#include <ak-opengl.h> /* load assetkit to libgk */
#include <gk.h>        /* renderer               */
#include <cglm.h>      /* math                   */

const char *fname = "./cube_phong.dae";
GkContext  *ctx;
AkDoc      *doc;
GkModel    *model;
GkScene    *scene;
mat4        projMatrix;
mat4        viewMatrix;
bool        do_render = true; /* render only if needed */

void
load_collada() {
  AkResult ret;

  /* load COLLADA, that's it! */
  ret = ak_load(&doc, fname, NULL);
  if (ret != AK_OK)
    exit(-1);

  /* load collada to OpenGL through libgk */

  /* render context */
  ctx = gkContextNew();

  /* load whole visual scene, this returns GkScene for rendering */
  agk_loadScene(ctx,
                doc,
                &doc->scene,
                GL_STATIC_DRAW,
                &scene);
}

void
init() {
  load_collada();

  /* get first found camera and it's attribs (VIEW MATRIX, PROJ MATRIX) */
  ak_firstCamera(doc,
                 NULL, /* for now we don't need to store cam ref */
                 viewMatrix[0],
                 projMatrix[0]);

  /* cache VIEW matrix */
  glm_mat4_inv(viewMatrix, scene->v);

  /* default shaders: common materials */
  /* NOTE: every node, model can have different shaders e.g. GLSL profile  */
  /*       if nodes, models don't have program info then they use parent's */
  /*       so we provided only ONE prog info and all nodes will use this   */
  /*       also check bottom to see how to use custom shaders              */
  scene->pinfo    = gkDefaultProgram();

  /* invalidate VIEW matrix
       = force re-render + re-calculate and cache model and final matrices  */
  scene->vIsValid = 0;

  /* NOTE for node matrices: all matrices will be cached by first draw call */
  /*      so you don't need manage cache manually BUT YOU CAN INVALIDATE    */
  /*      if you invalidate matrix, then all sub-nodes' matrices will be    */
  /*      recalculated (only children and instance nodes) and cached again  */
  /*      also like prog info, nodes, models use parent matrix if they      */
  /*      don't have any transform, this saves extra space, for instance;   */
  /*      if only root node has transform then all sub-nodes, node-instances*/
  /*      will use same matrix, space=1 * sizeof(mat4) * ptrsize * refcount */

  glEnable(GL_DEPTH_TEST);
  glClearColor(0.64, 0.64, 0.64, 1);

  resize();
}

/* optional, resize projection with window */
void
resize() {
  do_render = true;

  /* fix PROJECTION matrix */
  glm_perspective_resize(projMatrix);

  /* cache VIEW and PROJECTION x VIEW matrices */
  glm_mat4_mul(projMatrix,
               scene->v,
               scene->pv);

  /* invalidate PROJECTION x VIEW
       = force re-render + re-calculate and cache model and final matrices  */
  scene->pvIsValid = 0;

  /* render manually */
  render();
}

void
render() {
  if (!do_render)
    return;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* render scene, that's it! */
  /* you can render specific Node, Model using RenderNode, RenderModel... */
  /* so you don't have to have nodes  */
  gkRenderScene(scene);

  do_render = false;
}

void
dealloc() {
  /* free collada file */
  ak_free(doc);

  /* TODO: free libgk */
}

/* OPTIONAL: */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* this shows how to load custom shaders from folder */
/*
 void
 createProg() {
   GkProgInfo *pinfo;

   program = glCreateProgram();
   gkShaderLoadFromFolder(realpath("shader", tmpPathBuf),
   &shaders);

   gkAttachShaders(program, shaders);
   glLinkProgram(program);

#ifdef DEBUG
   if (!gkProgramIsValid(program)) {
     gkProgramLogInfo(program, stderr);
     exit(-1);
   }
#endif

   glUseProgram(program);

   pinfo = (GkProgInfo *)malloc(sizeof(*pinfo));
   pinfo->mvpi = glGetUniformLocation(program, "MVP");;
   pinfo->mvi  = glGetUniformLocation(program, "MV");;
   pinfo->nmi  = glGetUniformLocation(program, "NM");;
   pinfo->nmui = glGetUniformLocation(program, "NMU");;
   pinfo->prog = program;
   pinfo->refc = 1;

   scene->pinfo = pinfo;
 }
 */
