#ifndef __BEZIERSURFACE__
#define __BEZIERSURFACE__

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <vector>

#include "glmutils.h"
#include "bezierpatch.h"


/**
 * \class BezierSurface
 * implements the geometry of the surface defned by Bezier Patches.
 */
class BezierSurface {
public:
    /**
     * Default constructor. Creates a BezierSurface which is empty.
     */
    BezierSurface();

    /**
     * Parameterized constructor. Creates a BezierSurface from a file.
     * \param Filename - the name of the file containing the bezier patches.
     */
    BezierSurface(std::string Filename);

    /**
     * Parameterized constructor. Creates a BezierSurface from its parameters.
     * \param patches - the bezier patches which makes up the surface.
     */
    BezierSurface(std::vector<BezierPatch> const& bezierpatches);

    /**
     * Copy constructor, creates a new instance of its parameter.
     * \param Src - a BezierSurface
     */
    BezierSurface(BezierSurface const& Src);

    /**
     * Destructor destroys the current instance of a BezierSurface.
     */
    virtual ~BezierSurface();

    /**
     * Assignment operator, assigns its parameter to the current instance.
     * \param Src - the BezierSurface that should be assigned to the current instance.
     * \return the current instance of the BezierSurface.
     */
    BezierSurface& operator=(BezierSurface const& Src);

    /**
     * Specifies if the surface is front facing or back facing.
     * \return true if the surface is front facing, false if it is back facing.
     */
    bool FrontFacing() const;
    
    /**
     * Specifies if the surface is front facing or back facing.
     * \param frontfacing - true if the surface is front facing.
     */
    void FrontFacing(bool frontfacing);
    
    /**
     * The current number of subdivisions.
     * \return the current number of subdivisions.
     */
    int NumberOfSubdivisions() const;

    /**
     * Specify how many times the BezierSurface should be subdivided.
     * \param subdivisionlevel - the number of subdivisions that should be done.
     * \return the previous number or subdivisions.
     */
    int NumberOfSubdivisions(int Nsubdivisions);

    /**
     * Computes the vertices of the BezierSurface.
     * \return a vector containing the vertices of the triangles that approximate the BezierSurface.
     */
    std::vector<glm::vec3> const& Vertices();

    /**
     * Computes the normals of the BezierSurface.
     * \return a vector containing the normals of the vertices of the triangles 
     * that approximate the BezierSurface.
     */
    std::vector<glm::vec3> const& Normals();

protected:

private:
    // private member functions

    /**
     * Read the patches from a file
     * \param FileNae - the name of the file containing the bezier patches.
     */
    void Read(std::string const& FileName);

    /**
     * Prints the indices of the entries of the BezierPatch.
     * \param index_11 - the number of the vertex 11.
     * \param index_12 - the number of the vertex 12.
     * \param index_13 - the number of the vertex 13.
     * \param index_14 - the number of the vertex 14.
     * \param index_21 - the number of the vertex 21.
     * \param index_22 - the number of the vertex 22.
     * \param index_23 - the number of the vertex 23.
     * \param index_24 - the number of the vertex 24.
     * \param index_31 - the number of the vertex 31.
     * \param index_32 - the number of the vertex 32.
     * \param index_33 - the number of the vertex 33.
     * \param index_34 - the number of the vertex 34.
     * \param index_41 - the number of the vertex 41.
     * \param index_42 - the number of the vertex 42.
     * \param index_43 - the number of the vertex 43.
     * \param index_44 - the number of the vertex 44.
     */
    void PrintIndexMatrix(int PatchNumber,
			  int index_11, int index_12, int index_13, int index_14,
			  int index_21, int index_22, int index_23, int index_24,
			  int index_31, int index_32, int index_33, int index_34,
			  int index_41, int index_42, int index_43, int index_44) const;
    
    /**
     * subdivides a BezierPatch
     * \param patch - the bezierpatch which should be subdivided.
     * \param level - the number of times the patch should be subdivided.
     */
    void subdivide_bezierpatch(BezierPatch const& G, int level);

    // private variables

    // The Basic Matric for Bezier Surfaces.
    static glm::mat4x4 M;

    // The Subdivision matrix DBL 
    static glm::mat4x4 DBL;

    // The Subdivision matrix DBR 
    static glm::mat4x4 DBR;

    // is the surface front facing or back facing.
    bool frontfacing;
    
    // the number of times the bezierpathces should be devided.
    int nsubdivisions;

    // the original bezierpatches.
    std::vector<BezierPatch> BezierPatches;

    // the vertices of the approximating triangles after subdivision "level" times.
    bool VerticesOK;
    std::vector<glm::vec3> vertices;

    // the normals of the approximating triangles after subdivision "level" times.
    bool NormalsOK;
    std::vector<glm::vec3> normals;
};

#endif
