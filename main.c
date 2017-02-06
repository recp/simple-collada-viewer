//
//  main.c
//  assetkit_render
//
//  Created by Recep Aslantas on 9/30/16.
//  Copyright © 2016 Recep Aslantas. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>

#include <GLFW/glfw3.h>
#include "assetkit_test.h"

void (glfw_resized)(GLFWwindow* window,int w,int h) {
  resize();
}

void
glfw_errCallback(int err, const char *desc) {
  printf("GLFW %s", desc);
}

int
main(int argc, const char * argv[]) {
  glfwSetErrorCallback(glfw_errCallback);

  if (!glfwInit()) {
    printf("GLFW err: glfwInit");
    return -1;
  }


  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_SAMPLES, 4);
  GLFWwindow *window = glfwCreateWindow(800, // vidmod->width,
                                        600, // vidmod->height,
                                        "Ogl1",
                                        NULL, // monitor,
                                        NULL);
  if (!window) {
    printf("GLFW " "window");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetWindowSizeCallback(window, glfw_resized);

  init();

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glfwSwapBuffers(window);

    render();
    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      dealloc();
      glfwSetWindowShouldClose(window, 1);
    }
  }

//  glfwTerminate();
  return 0;
}
