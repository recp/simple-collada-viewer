//
//  assetkit_test.h
//  assetkit_render
//
//  Created by Recep Aslantas on 10/21/16.
//  Copyright © 2016 Recep Aslantas. All rights reserved.
//

#ifndef assetkit_test_h
#define assetkit_test_h

#ifdef __cplusplus
extern "C" {
#endif

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

void
init();

void
resize();

void
render();

void
dealloc();

#ifdef __cplusplus
}
#endif
#endif /* assetkit_test_h */
