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
loadCOLLADA() {
  AkResult ret;

  /* load collada */
  ret = ak_load(&doc, fname, NULL);
  if (ret != AK_OK)
    exit(-1);

  /* load collada to OpenGL through libgk */
  ctx = gkContextNew();
  ak_glLoadScene(ctx,
                 doc,
                 &doc->scene,
                 GL_STATIC_DRAW,
                 &scene);
}

void
init() {
  loadCOLLADA();

  /* get first found camera */
  ak_camFirstCamera(doc,
                    NULL, /* for now we don't need to store cam ref */
                    viewMatrix[0],
                    projMatrix[0]);
  glm_mat4_inv(viewMatrix, scene->v);

  scene->pinfo    = gkDefaultProgram();
  scene->vIsValid = 0;

  glEnable(GL_DEPTH_TEST);
  glClearColor(0.64, 0.64, 0.64, 1);

  resize();
}

void
resize() {
  do_render = true;

  glm_perspective_resize(projMatrix);
  glm_mat4_mul(projMatrix,
               scene->v,
               scene->pv);
  scene->pvIsValid = 0;

  render();
}

void
render() {
  if (!do_render)
    return;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gkRenderScene(scene);

  do_render = false;
}

void
dealloc() {
  /* free collada file */
  ak_free(doc);

  /* TODO: free libgk */
}

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

   if (!gkProgramIsValid(program)) {
     gkProgramLogInfo(program, stderr);
     exit(-1);
   }

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