#ifndef RM_DIKUGRAFIK_PARAMETRICSURFACE_H
#define RM_DIKUGRAFIK_PARAMETRICSURFACE_H

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>

#include "glmutils.h"


/**
 * \class ParametricSurface
 * An abstract class which implements implements the interface of a parametric surface.
 */
class ParametricSurface {
public:
    /**
     * Creates an empty parametric surface.
     */
    ParametricSurface();

    /**
     * Creates a paraametric surface with the limits for the u, v parameters.
     * \param umin - the left limit for the u-parameter.
     * \param umax - the right limit for the u-parameter.
     * \param M - the number of samples in the u-direction.
     * \param vmin - the left limit for the v-parameter.
     * \param vmax - the right limit for the v-parameter.
     * \param N - the number of samples in the v-direction.
     * \param frontfacing - true if the surface is front facing, else false.
     * \param debug - true if debug mode should be on, false otherwize.
     */
    ParametricSurface(float umin, float umax, int M,
		      float vmin, float vmax, int N,
                      bool frontfacing,  bool debug);

    /**
     * Copy constructor. Makes a copy of the parameter.
     * \param newparamsurface - the parametric surface to be copied.
     */
    ParametricSurface(ParametricSurface const& newparmsurface);


    /**
     * Destroys the current instance of the parametric surface.
     */
    virtual ~ParametricSurface();

    /**
     * Assignment operator. Assigns the parameter to this instance of a parametric surface.
     * \param newparamsurface - the parametric surface that should be 
     *                          assigned to this instance.
     */
    ParametricSurface& operator=(ParametricSurface const& newparamsurface);

    /**
     * Assignment operator. Assigns the parameter to this instance of a parametric surface.
     * \param newparamsurface - the parametric surface that should be 
     *                          assigned to this instance.
     */
    ParametricSurface const& operator=(ParametricSurface const& newparmsurface) const;

    /**
     * The left limit of the u-parameter.
     * \return the left limit of the u-parameter.
     */
    float Umin() const;

    /**
     * Changes the left limit of the u-parameter.
     * \param newUmin - the new left limit of the u-parameter.
     */
    void Umin(float newUmin);

    /**
     * The right limit of the u-parameter.
     * \return the right limit of the u-parameter.
     */
    float Umax() const;

    /**
     * Changes the right limit of the u-parameter.
     * \param newUmax - the new right limit of the u-parameter.
     */
    void Umax(float newUmax);

    /**
     * The number of samples in the u-direction.
     * \return the actual number of samples in the u-samples.
     */
    int Usamples() const;
  
    /**
     * Changes the number of samples in the u-direction.
     * \param M - the new number of u-samples.
     */
    void Usamples(int M);

    /**
     * The left limit of the v-parameter.
     * \return the left limit of the v-parameter.
     */
    float Vmin() const;

    /**
     * Changes the left limit of the v-parameter.
     * \param newVmin - the new left limit of the v-parameter.
     */
    void Vmin(float newVmin);

     /**
     * The right limit of the v-parameter.
     * \return the right limit of the v-parameter.
     */
    float Vmax() const;

    /**
     * Changes the right limit of the v-parameter.
     * \param newVmax - the new right limit of the v-parameter.
     */
    void Vmax(float newVmax);

    /**
     * The number of samples in the v-direction.
     * \return the actual number of samples in the v-samples.
     */
    int Vsamples() const;
    
    /**
    * Changes the number of samples in the v-direction.
    * \param N - the new number of v-samples.
    */
    void Vsamples(int N);
    
    /**
     * Reports if the surface is front facing.
     * \return true if the surface is front facing, else false.
     */ 
    bool FrontFacing() const;

    /**
     * Defines if the surface is front facing or not.
     * \param frontfacing - true if the surface is front facing, else false.
     */
    void FrontFacing(bool frontfacing);

    /**
     * Reports the debug state.
     * \return true if in debug mode, else false.
     */
    bool Debug() const;
    
    /**
     * Cantrols which quadrilaterals should be shown.
     * It makes it easier to whatch the surface.
     * \param debug - if false all quadrilaterals are shown, 
     *                else only every other quadrilateral are shown.
     */
    void Debug(bool debug);

    /**
     * The coordinates of the vertices.
     * \return a vector containing the coordinates of the points.
     */
    std::vector<glm::vec3> const& Vertices();

    /**
     * The coordinates of the normals.
     * \return a vector containing the coordinates of the normals.
     */
    std::vector<glm::vec3> const& Normals();
      
protected:
    /**
     * Computes the coordinates of a point on the surface.
     * \param u - the first parameter of the surface.
     * \param v - the second parameter of the surface.
     * \return the 3D coordinates of the point on the surface specified by the parameters (u, v).
     */
    virtual glm::vec3 Vertex(float const u, float const v) const = 0;

    /**
     * Computes the coordinates of a normal of the surface.
     * \param u - the first parameter of the surface.
     * \param v - the second parameter of the surface.
     * \return the 3D coordinates of the normal of the surface specified by the parameters (u, v).
     */
    virtual glm::vec3 Normal(float const u, float const v) const = 0;

     /**
     * Checks if the geometric data has changed since the last upload the the graphics card.
     * \return true if the geometric data has changed, else false.
     */
    bool DataHasChanged() const;
    
    /**
     * Informs this class of a change of the geometric which has not yet been uploaded to the graphics card.
     * \param datachanged - if true the class is informed of data is not valid.
     */
    void DataHasChanged(bool datachanged);
    
private:
    /**
     * Generates the actual vertices, normals, and texture coordinates of the surface.
     */
    void SampleSurface();

    /**
     * Generates two front facing triangles from a quadrilateral using counter clockwize order, 
     * and specifying the diagonal as the first edge.
     * \param V_lower_left - the lower left vertex.
     * \param V_lower_right - the lower right vertex.
     * \param V_upper_right - the upper right vertex.
     * \param V_upper_left - the upper left vertex.
     * \param vertices - a vector containing the vertices.
     * \param N_lower_left - the lower left normal.
     * \param N_lower_right - the lower right normal.
     * \param N_upper_right - the upper right normal.
     * \param N_upper_left - the upper left normal.
     * \param normals - a vector containing the normals.
     */
    void CreateFrontFacingData(glm::vec3 const& V_lower_left,  glm::vec3 const& V_lower_right,
                               glm::vec3 const& V_upper_right, glm::vec3 const& V_upper_left,
                               std::vector<glm::vec3>& vertices,
                               glm::vec3 const& N_lower_left,  glm::vec3 const& N_lower_right,
                               glm::vec3 const& N_upper_right, glm::vec3 const& N_upper_left,
                               std::vector<glm::vec3>& normals) const;

    /**
     * Generates two back facing triangles from a quadrilateral using clockwize order, 
     * and specifying the diagonal as the first edge.
     * \param V_lower_left - the lower left vertex.
     * \param V_lower_right - the lower right vertex.
     * \param V_upper_right - the upper right vertex.
     * \param V_upper_left - the upper left vertex.
     * \param vertices - a vector containing the vertices.
     * \param N_lower_left - the lower left normal.
     * \param N_lower_right - the lower right normal.
     * \param N_upper_right - the upper right normal.
     * \param N_upper_left - the upper left normal.
     * \param normals - a vector containing the normals.
     */
    void CreateBackFacingData(glm::vec3 const& V_lower_left,  glm::vec3 const& V_lower_right,
                              glm::vec3 const& V_upper_right, glm::vec3 const& V_upper_left,
                              std::vector<glm::vec3>& vertices,
                              glm::vec3 const& N_lower_left,  glm::vec3 const& N_lower_right,
                              glm::vec3 const& N_upper_right, glm::vec3 const& N_upper_left,
                              std::vector<glm::vec3>& normals) const;

    unsigned int M;   // Number of samples of the u-parameter.
    unsigned int N;   // Number of samples of the v-parameter.

    float umin;       // lower bound of the u-parameter.
    float umax;       // upper bound of the u-parameter.
    float delta_u;
    
    float vmin;       // lower bound of the v-parameter.
    float vmax;       // upper bound of the v-parameter.
    float delta_v;

    bool frontfacing; // true if surface is front facing, else false.
    bool debug;       // true if debug mode should be turned on, else false.
    bool validdata;   // true if the data, vertices, normals, and texturecoordinates are up to date
    
    std::vector<glm::vec3> vertices;   // The computed vertices
    std::vector<glm::vec3> normals;    // The computed normals
};

#endif
