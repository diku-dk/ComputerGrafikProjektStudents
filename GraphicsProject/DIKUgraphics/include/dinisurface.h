#ifndef __DINISURFACE_H__
#define __DINISURFACE_H__

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <vector>

#include "glmutils.h"
#include "parametricsurface.h"


/**
 * \class DiniSurface
 * implements the geometry of the surface defned by the Dini function which is a surface of constant negative curvature.
 */
class DiniSurface : public ParametricSurface {
public:
    /**
     * Default constructor creates a DiniSurface with some default parameters.
     */
    DiniSurface();

    /**
     * Parameterized constructor creates a DiniSurface with parameters given by the arguments.
     * \param a - coefficient of the Dini surface
     * \param b - coefficient of the Dini surface
     */
    DiniSurface(float a, float b);

    /**
     * Copy constructor creates a copy of its argument
     */
    DiniSurface(DiniSurface const& Src);

    /**
     * Destructor deletes the current instance of class DiniSurface.
     */
    virtual ~DiniSurface();

    /**
     * Assignment operator assigns its argument to the current instance.
     */
    DiniSurface& operator=(DiniSurface const& Src);

    /**
     * Computes a vertex on the Dini reflection surface given parameters phi and theta.
     * \param u - the height angle of the view vector.
     * \param v - the azimuth angle of the view vector.
     * \return - the 3D point corresponding to the parameters phi and theta.
     */
    glm::vec3 Vertex(float u, float v) const;

    /**
     * Computes the normal to the Dini reflection surface given parameters phi and theta.
     * \param u - the height angle of the view vector.
     * \param v - the azimuth angle of the view vector.
     * \return - the 3D normal to the phong surface corresponding to the parameters phi and theta.
     */
    glm::vec3 Normal(float u, float v) const;

protected:

private:
    /**
     * Computes a point on the Dini surface
     * \param phi - the height angle of the view vector.
     * \param theta - the azimuth angle of the view vector.
     * \return the 3D point on the surface.
     */
    glm::vec3 Dini(float phi, float theta) const;

    /**
     * The partial derivative of the Dini surface with respect to phi.
     * \param phi - the height angle of the view vector.
     * \param theta - the azimuth angle of the view vector.
     * \return - the partial derivative wrt. phi of the Dini surface.
     */
    glm::vec3 dDinidphi(float phi, float theta) const;

    /**
     * The partial derivative of the Dini surface with respect to theta.
     * \param phi - the height angle of the view vector.
     * \param theta - the azimuth angle of the view vector.
     * \return - the partial derivative wrt. theta of the Dini surface.
     */
    glm::vec3 dDinidtheta(float phi, float theta) const;


    // Private Variables
    
    // The coefficients of the Dini surface
    float a;
    float b;
};

#endif
