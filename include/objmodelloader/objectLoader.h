/*
 * last modification: (Sharif Uddin) Mar, 2015
 * Changes to class structure and implemented as objectLoader to assist main program.
 *
 * Copyright (c) 2005-2007 David HENRY
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;

class ObjectLoader {

  // Vectors
  typedef float vec3_t[3];
  typedef float vec4_t[4];

  // Vertex
  struct obj_vertex_t {
    vec4_t xyzw;
  };

  // Texture coordinates
  struct obj_texCoord_t {
    vec3_t uvw;
  };

  // Normal vector
  struct obj_normal_t {
    vec3_t ijk;
  };

  // Polygon
  struct obj_face_t {
    GLenum type;        /* primitive type */
    int num_elems;      /* number of vertices */

    int *vert_indices;  /* vertex indices */
    int *uvw_indices;   /* texture coordinate indices */
    int *norm_indices;  /* normal vector indices */
  };

  // OBJ model structure
  struct obj_model_t {
    int num_verts;                     /* number of vertices */
    int num_texCoords;                 /* number of texture coords. */
    int num_normals;                   /* number of normal vectors */
    int num_faces;                     /* number of polygons */

    int has_texCoords;                 /* has texture coordinates? */
    int has_normals;                   /* has normal vectors? */

    struct obj_vertex_t *vertices;     /* vertex list */
    struct obj_texCoord_t *texCoords;  /* tex. coord. list */
    struct obj_normal_t *normals;      /* normal vector list */
    struct obj_face_t *faces;          /* model's polygons */
  };




  public:
    ObjectLoader();
    void loadObject(const char* filename);
    void renderObject(unsigned int index);

  private:
    void freeModel(struct obj_model_t *mdl);
    int mallocModel(struct obj_model_t *mdl);

    int firstPass(FILE *fp, struct obj_model_t *mdl);
    int secondPass(FILE *fp, struct obj_model_t *mdl);

    int readOBJModel(const char* filename, struct obj_model_t *mdl);
    void renderOBJModel(struct obj_model_t *mdl);

    void cleanup();

  private:
    // an OBJ model
    vector<obj_model_t> object_array;
    struct obj_model_t objfile_1;
    struct obj_model_t objfile_2;

};

#endif
