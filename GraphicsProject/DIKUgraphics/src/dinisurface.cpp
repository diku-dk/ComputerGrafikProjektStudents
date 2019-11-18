#include "traceinfo.h"
#include "dinisurface.h"


/**
 * \class DiniSurface
 * implements the geometry of the surface defned by the Dini function which is a surface of constant negative curvature.
 */

// Public member functions

/*
 * Default constructor creates a DiniSurface with some default parameters.
 */
DiniSurface::DiniSurface()
           : ParametricSurface(0.0f, 6.0f * glm::pi<float>(), 100, 0.01f, 2.0f, 20, false, false),
             a(1.0f), b(0.2f)
{}

/*
 * Parameterized constructor creates a DiniSurface with parameters given by the arguments.
* \param a - coefficient of the Dini surface
* \param b - coefficient of the Dini surface
 */
DiniSurface::DiniSurface(float a, float b)
           : ParametricSurface(0.0f, 6.0f * glm::pi<float>(), 100, 0.01f, 2.0f, 20, false, false),
             a(a), b(b)
{}

/*
 * Copy constructor creates a copy of its argument
 */
DiniSurface::DiniSurface(DiniSurface const& Src)
           : ParametricSurface(Src)
{
    this->a = Src.a;
    this->b = Src.b;
}

/*
 * Destructor deletes the current instance of class DiniSurface.
 */
DiniSurface::~DiniSurface()
{}

/*
 * Assignment operator assigns its argument to the current instance.
 */
DiniSurface& DiniSurface::operator=(DiniSurface const& Src)
{
    if (this != &Src) {
        this->a = Src.a;
        this->b = Src.b;
    }
    return *this;
}

/*
 * Computes a vertex on the Dini reflection surface given parameters phi and theta.
 * \param u - the height angle of the view vector.
 * \param v - the azimuth angle of the view vector.
 * \return - the 3D point corresponding to the parameters phi and theta.
 */
glm::vec3 DiniSurface::Vertex(float u, float v) const
{
    glm::vec3 vertex = this->Dini(u, v);
    return vertex;
}

/*
 * Computes the normal to the Dini reflection surface given parameters phi and theta.
 * \param u - the height angle of the view vector.
 * \param v - the azimuth angle of the view vector.
 * \return - the 3D normal to the phong surface corresponding to the parameters phi and theta.
 */
glm::vec3 DiniSurface::Normal(float u, float v) const
{
    glm::vec3 Dphi   = this->dDinidphi(u, v);
    glm::vec3 Dtheta = this->dDinidtheta(u, v);
    glm::vec3 normal = glm::cross(Dphi, Dtheta );

    if (normal != glm::vec3(0.0f)) {
        normal = glm::normalize(normal);
    }
    return normal;
}

// Protected member functions

// Private member functions

/*
 * The view vector used to visualize the phong surface.
 * \param phi - the height angle of the view vector.
 * \param theta - the azimuth angle of the view vector.
 * \return - the 3D view vector.
 */
glm::vec3 DiniSurface::Dini(float phi, float theta) const
{
    glm::vec3 dini(this->a * glm::cos(phi) * glm::sin(theta),
                   this->a * glm::sin(phi) * glm::sin(theta),
                   this->a * (glm::cos(theta) + glm::log(glm::tan(0.5 * theta))) + this->b * phi);
    return dini;
}

/*
 * The partial derivative of the view vector with respect to phi.
 * \param phi - the height angle of the view vector.
 * \param theta - the azimuth angle of the view vector.
 * \return - the partial derivative wrt. phi of the 3D view vector.
 */
glm::vec3 DiniSurface::dDinidphi(float phi, float theta) const
{
    glm::vec3 Ddini_Dphi(-this->a * glm::sin(phi) * glm::sin(theta),
                         this->a * glm::cos(phi) * glm::sin(theta),
                         this->b);
    return Ddini_Dphi;
}

/*
 * The partial derivative of the view vector with respect to theta.
 * \param phi - the height angle of the view vector.
 * \param theta - the azimuth angle of the view vector.
 * \return - the partial derivative wrt. theta of the 3D view vector.
 */
glm::vec3 DiniSurface::dDinidtheta(float phi, float theta) const
{
    glm::vec3 Ddini_Dtheta(this->a * glm::cos(phi) * glm::cos(theta),
                           this->a * glm::sin(phi) * glm::cos(theta),
                           0.5f / (glm::sin(0.5f * theta) * glm::cos(0.5f * theta)) - glm::sin(theta));
    return Ddini_Dtheta;
}

