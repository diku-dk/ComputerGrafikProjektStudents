#ifndef RM_KLEINBOTTLE_H
#define RM_KLEINBOTTLE_H

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>

#include "glmutils.h"
#include "parametricsurface.h"


/**
 * \class KleinTop
 * implements a surface which is the top of the surface.
 */
class KleinTop : public ParametricSurface  {
public:
    /**
     * Creates an instance of the top part of the Klein Bottle with default parameters.
     * The parameters can be changed by calling member functions of the parent class ParametricSurface.
     */
    KleinTop();

    /**
     * Creates an instance of the top part of the Klein Bottle with
     * the specified parameters.
     * \param M - the number of samples of the u-parameter.
     * \param N - the number of smaples of the v-parameter.
     * \param frontfacing - true if the surface is frontfacing, else false.
     * \param debug - true if debug mode should be initialized, else false.
     */
    KleinTop(int M, int N, bool frontfacing = true, bool debug = false);

     /**
     * Computes a point on the surface.
     * \param u - the value of the u-parameter.
     * \param v - the value of the v-parameter.
     * \return a 3D vector containing the coordinates of the point on the surface.
     */
    glm::vec3 Vertex(float u, float v) const;

    /**
     * Computes a normal to the surface.
     * \param u - the value of the u-parameter.
     * \param v - the value of the v-parameter.
     * \return a 3D vector containing the coordinates of the normal on the surface.
     */
    glm::vec3 Normal(float u, float v) const;

protected:
  
private:

};

/**
 * \class KleinBottom
 * implements a surface which is the bottom of the surface.
 */
class KleinBottom : public ParametricSurface {
public:
    /**
     * Creates an instance of the bottom part of the Klein Bottle with default parameters.
     * The parameters can be changed by calling member functions of the parent class ParametricSurface.
     */
    KleinBottom();

    /**
     * Creates an instance of the bottom part of the Klein Bottle with
     * the specified parameters.
     * \param M - the number of samples of the u-parameter.
     * \param N - the number of smaples of the v-parameter.
     * \param frontfacing - true if the surface is frontfacing, else false.
     * \param debug - true if debug mode should be initialized, else false.
     */
    KleinBottom(int M, int N, bool frontfacing = true, bool debug = false);

protected:
    /**
     * Computes a point on the surface.
     * \param u - the value of the u-parameter.
     * \param v - the value of the v-parameter.
     * \return a 3D vector containing the coordinates of the point on the surface.
     */
    glm::vec3 Vertex(float u, float v) const;

    /**
     * Computes a normal to the surface.
     * \param u - the value of the u-parameter.
     * \param v - the value of the v-parameter.
     * \return a 3D vector containing the coordinates of the normal on the surface.
     */
    glm::vec3 Normal(float u, float v) const;
    
private:

};

/**
 * \class KleinHandle
 * implements a surface which is a handle of the surface
 */
class KleinHandle : public ParametricSurface  {
public:
    /**
     * Creates an instance of the handle part of the Klein Bottle with default parameters.
     * The parameters can be changed by calling member functions of the parent class ParametricSurface.
     */
    KleinHandle();

    /**
     * Creates an instance of the handle part of the Klein Bottle with
     * the specified parameters.
     * \param M - the number of samples of the u-parameter.
     * \param N - the number of smaples of the v-parameter.
     * \param frontfacing - true if the surface is frontfacing, else false.
     * \param debug - true if debug mode should be initialized, else false.
     */
    KleinHandle(int M, int N, bool frontfacing = true, bool debug = false);

    /**
     * Computes a point on the surface.
     * \param u - the value of the u-parameter.
     * \param v - the value of the v-parameter.
     * \return a 3D vector containing the coordinates of the point on the surface.
     */
    glm::vec3 Vertex(float u, float v) const;

    /**
     * Computes a normal to the surface.
     * \param u - the value of the u-parameter.
     * \param v - the value of the v-parameter.
     * \return a 3D vector containing the coordinates of the normal on the surface.
     */
    glm::vec3 Normal(float u, float v) const;

protected:
  
private:
   
};

/**
 * \class KleinMiddle
 * implements a surface which is the middle part of the surface.
 */
class KleinMiddle : public ParametricSurface  {
public:
    /**
     * Creates an instance of the middle part of the Klein Bottle with default parameters.
     * The parameters can be changed by calling member functions of the parent class ParametricSurface.
     */
    KleinMiddle();

    /**
     * Creates an instance of the handle part of the Klein Bottle with
     * the specified parameters.
     * \param M - the number of samples of the u-parameter.
     * \param N - the number of smaples of the v-parameter.
     * \param frontfacing - true if the surface is frontfacing, else false.
     * \param debug - true if debug mode should be initialized, else false.
     */
    KleinMiddle(int M, int N, bool frontfacing = true, bool debug = false);
    
    /**
     * Computes a point on the surface.
     * \param u - the value of the u-parameter.
     * \param v - the value of the v-parameter.
     * \return a 3D vector containing the coordinates of the point on the surface.
     */
    glm::vec3 Vertex(float u, float v) const;

    /**
     * Computes a normal to the surface.
     * \param u - the value of the u-parameter.
     * \param v - the value of the v-parameter.
     * \return a 3D vector containing the coordinates of the normal on the surface.
     */
    glm::vec3 Normal(float u, float v) const;

protected:
  
private:
    
};


/**
 * \class KleinBottle
 * Implements a Klein Bottle, i.e. a surface with only one side.
 * It is composed by four simple surfaces which are implemented by the
 * classes KleinTop, KleinBottom, KleinHandle, and KleinMiddle.
 */
class KleinBottle {
public:
    /**
     * Creates an instance of a Klein Bottle with default parameters.
     */
    KleinBottle();

    /**
     * Parametrized constructor, creates an instance of the bottom part of a Klein Bottle.
     * \param M - the number of samples of the u-parameter.
     * \param N - the number of smaples of the v-parameter.
     * \param frontfacing - true if the surface is frontfacing, else false.
     * \param debug - true if debug mode should be initialized, else false.
     */
    KleinBottle(int M, int N, bool frontfacing = true, bool debug = false);

    /**
     * Copy constructor, copies the parameter to this instance.
     * \param Src - the instance to be copied.
     */
    KleinBottle(KleinBottle const& Src);

     /**
     * Destructor, destroys the current instance of a Klein Bottle.
     */
    virtual ~KleinBottle();

    /**
     * Assignment operator, assigns the parameter to this instance.
     * \param Src - the instance which should be assigned to this instance.
     * \return the current instance of the KleinBottom.
     */
    KleinBottle& operator=(KleinBottle const& Src);

    /**
     * The samples of the u-parameter.
     * \return the number of samples of the u-parameter.
     */
    int Usamples() const;

    /**
     * Changes the number of samples of the u-parameter.
     * \param M - the new number of samples of the u-parameter.
     */
    void Usamples(int M);

    /**
     * The samples of the v-parameter.
     * \return the number of samples of the v-parameter.
     */
    int Vsamples() const;

    /**
     * Changes the number of samples of the v-parameter.
     * \param N - the new number of samples of the v-parameter.
     */
    void Vsamples(int N);

    /**
     * The coordinates of vertices which define the triangles in the mesh.
     * It returns an array containing the coordinates of the triangle vertices in the mesh with the following
     * interpretation: the first 3 entries define the first triangle, the next 3 entries define the second
     * triangle etc.
     * \return An array containing the vertices of the faces in the mesh.
     */
    std::vector<glm::vec3> const& Vertices();

    /**
     * The normals of vertices which define the triangles in the mesh.
     * It returns an array containing the normals of the vertices in the mesh with the following
     * interpretation: the first 3 entries define the normals of the vertices of the first triangle, 
     * the next 3 entries define the normals of the vertices of the second triangle etc.
     * \return An array containing the normals of the vertices.
     */
    std::vector<glm::vec3> const& Normals();


protected:

private:
    int M;    // Number of samples of the u-parameter
    int N;    // Number of samples of the v-parameter

    bool validVertices;                 // False if M or N have been changed, else true.
    bool validNormals;                  // False if M or N have been changed, else true.
    
    KleinTop*    kleintop;              // The top part of the Klein Bottle
    KleinBottom* kleinbottom;           // The bottom part of the Klein Bottle
    KleinHandle* kleinhandle;           // The handle part of the Klein Bottle
    KleinMiddle* kleinmiddle;           // The middle part of the Klein Bottle

    std::vector<glm::vec3> vertices;    // The sampled vertices
    std::vector<glm::vec3> normals;     // The sampled normals
};


#endif
