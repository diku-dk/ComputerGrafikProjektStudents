#include "parametricsurface.h"

/**
 * \class ParametricSurface
 * An abstract class which implements implements the interface of a parametric surface.
 */

/*
 * Creates an empty parametric surface.
 */
ParametricSurface::ParametricSurface()
{
    Trace("ParametericSurface", "ParametericSurface()");
}

/*
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
ParametricSurface::ParametricSurface(float umin, float umax, int M,
                                     float vmin, float vmax, int N,
                                     bool frontfacing, bool debug)
                 : M(M), N(N), umin(umin), umax(umax), vmin(vmin), vmax(vmax),
                   frontfacing(frontfacing), debug(debug),
                   validdata(false)
{
    Trace("ParametricSurface", "ParametricSurface(float, float, int, float, float, int, bool, bool)");

    this->delta_u = (this->umax - this->umin) / M;
    this->delta_v = (this->vmax - this->vmin) / N;
    
    this->vertices.clear();
    this->normals.clear();

    this->DataHasChanged(true);
}

/*
 * Copy constructor. Makes a copy of the parameter.
 * \param newparamsurface - the parametric surface to be copied.
 */
ParametricSurface::ParametricSurface(ParametricSurface const& newparamsurface)
                 : M(newparamsurface.M), N(newparamsurface.N),
                   umin(newparamsurface.umin), umax(newparamsurface.umax),
                   delta_u(newparamsurface.delta_u),
                   vmin(newparamsurface.vmin), vmax(newparamsurface.vmax),
                   delta_v(newparamsurface.delta_v),
                   frontfacing(newparamsurface.frontfacing), 
                   debug(newparamsurface.debug),
                   validdata(false),
                   vertices(newparamsurface.vertices),
                   normals(newparamsurface.normals)
{
    Trace("ParametricSurface", "ParametricSurface(ParametricSurface const&)");

    this->DataHasChanged(true);
}

/*
 * Destroys the current instance of the parametric surface.
 */
ParametricSurface::~ParametricSurface()
{
    Trace("ParametricSurface", "~ParametricSurface");
}

/*
 * Assignment operator. Assigns the parameter to this instance of a
 * parametric surface.
 * \param newparamsurface - the parametric surface that should be 
 *                          assigned to this instance.
 */
ParametricSurface& ParametricSurface::operator=(ParametricSurface const& newparamsurface)
{
    Trace("ParametricSurface", "operator=(ParametricSurface const&)");

    if (this != &newparamsurface) {
        this->umin    = newparamsurface.umin;
        this->umax    = newparamsurface.umax;
        this->M = newparamsurface.M;
        this->delta_u = newparamsurface.delta_u;
        this->vmin    = newparamsurface.vmin;
        this->vmax    = newparamsurface.vmax;
        this->N = newparamsurface.N;
        this->delta_v = newparamsurface.delta_v;
        this->frontfacing = newparamsurface.frontfacing;
        this->debug       = newparamsurface.debug;
        this->validdata   = newparamsurface.validdata;
        this->vertices    = newparamsurface.vertices;
        this->normals     = newparamsurface.normals;
        this->DataHasChanged(true);
    }
    return *this;
}

/*
 * The left limit of the u-parameter.
 * \return the left limit of the u-parameter.
 */
float ParametricSurface::Umin() const
{
    return this->umin;
}

/*
 * Changes the left limit of the u-parameter.
 * \param newUmin - the new left limit of the u-parameter.
 */
void ParametricSurface:: Umin(float newUmin)
{
    this->umin = newUmin;
    this->DataHasChanged(true);
}

/*
 * The right limit of the u-parameter.
 * \return the right limit of the u-parameter.
 */
float ParametricSurface::Umax() const
{
    return this->umax;
}

/*
 * Changes the right limit of the u-parameter.
 * \param newUmax - the new right limit of the u-parameter.
 */
void ParametricSurface::Umax(float newUmax)
{
    this->umax = newUmax;
    this->DataHasChanged(true);
}

/*
 * The number of samples in the u-direction.
 * \return the actual number of samples in the u-samples.
 */
int ParametricSurface::Usamples() const
{
    return this->M;
}
    
/*
 * Changes the number of samples in the u-direction.
 * \param M - the new number of u-samples.
 */
 void ParametricSurface::Usamples(int M)
 {
     this->M = M;
     this->DataHasChanged(true);
 }  

/*
 * The left limit of the v-parameter.
 * \return the left limit of the v-parameter.
 */
float ParametricSurface::Vmin() const
{
    return this->vmin;
}

/*
 * Changes the left limit of the v-parameter.
 * \param newVmin - the new left limit of the v-parameter.
 */
void ParametricSurface::Vmin(float newVmin)
{
    this->vmin = newVmin;
    this->DataHasChanged(true);
}

/*
 * The right limit of the v-parameter.
 * \return the right limit of the v-parameter.
 */
float ParametricSurface::Vmax() const
{
    return this->vmax;
}

/*
 * Changes the right limit of the v-parameter.
 * \param newVmax - the new right limit of the v-parameter.
 */
void ParametricSurface::Vmax(float newVmax)
{
    this->vmax = newVmax;
    this->DataHasChanged(true);
}

/*
 * The number of samples in the v-direction.
 * \return the actual number of samples in the v-samples.
 */
int ParametricSurface::Vsamples() const
{
    return this->N;
}
    
/*
 * Changes the number of samples in the v-direction.
 * \param N - the new number of v-samples.
 */
void ParametricSurface::Vsamples(int N)
{
    this->N = N;
    this->DataHasChanged(true);
}

/*
 * Reports if the surface is front facing.
 * \return true if the surface is front facing, else false.
 */ 
bool ParametricSurface::FrontFacing() const
{
    return this->frontfacing;
}

/*
 * Defines if the surface is front facing or not.
 * \param frontfacing - true if the surface is front facing, else false.
 */
void ParametricSurface::FrontFacing(bool frontfacing)
{
    if (this->frontfacing != frontfacing) {
        this->frontfacing = frontfacing;
        this->DataHasChanged(true);
    } 
}

/*
 * Reports the debug state.
 * \return true if in debug mode, else false.
 */
bool ParametricSurface::Debug() const
{
    return this->debug;
}
    
/*
 * Cantrols which quadrilaterals should be shown.
 * It makes it easier to whatch the surface.
 * \parm debug - if false all quadrilaterals are shown, 
 *               else only every other quadrilateral are shown.
 */
void ParametricSurface::Debug(bool debug)
{
    if (this->debug != debug) {
        // change the debug mode
        this->debug = debug;
        this->DataHasChanged(true);
    }
}

/*
 * The coordinates of the vertices.
 * \return a vector containing the coordinates of the points.
 */
std::vector<glm::vec3> const& ParametricSurface::Vertices()
{
    Trace("ParametricSurface", "Vertices()");
    
    if (this->DataHasChanged()) {
        this->SampleSurface();
    }
    return this->vertices;
}

/*
 * The coordinates of the normals.
 * \return a vector containing the coordinates of the normals.
 */
std::vector<glm::vec3> const& ParametricSurface::Normals()
{
    Trace("ParametricSurface", "Normals()");
    
    if (this->DataHasChanged()) {
        this->SampleSurface();
    }
    return this->normals;
}

/*
 * Protected members
 */

/*
 * Checks if the geometric data has changed since the last upload the the graphics card.
 * \return true if the geometric data has changed, else false.
 */
bool ParametricSurface::DataHasChanged() const
{
    Trace("ParametricSurface", "DataHasChanged()");

    return !this->validdata;
}

/*
 * Informs this class of a change of the geometric which has not yet been uploaded to the graphics card.
 * \param datachanged - if true the class is informed of data is not valid.
 */
void ParametricSurface::DataHasChanged(bool datachanged)
{
    Trace("ParametricSurface", "DataHasChanged(bool)");

    this->validdata = !datachanged;
}

/*
 * Private menbers
 */

/**
 * Samples the parametric surface
 */
void ParametricSurface::SampleSurface()
{
    Trace("ParametricSurface", "SampleSurface()");

    std::cout << "ParametricSurface::SampleSurface(): Not implemented yet!" << std::endl;
    
    this->validdata = true;
}

/*
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
void ParametricSurface::CreateFrontFacingData(glm::vec3 const& V_lower_left,  glm::vec3 const& V_lower_right,
                                              glm::vec3 const& V_upper_right, glm::vec3 const& V_upper_left,
                                              std::vector<glm::vec3>& vertices,
                                              glm::vec3 const& N_lower_left,  glm::vec3 const& N_lower_right,
                                              glm::vec3 const& N_upper_right, glm::vec3 const& N_upper_left,
                                              std::vector<glm::vec3>& normals) const
{
    Trace("ParametricSurface", "CreateFrontFacingData(...)");

    // Split Quadrilaterls into Triangles.
    // Add Triangles counter clockwize starting with the diagonal
    vertices.push_back(V_lower_left);
    normals.push_back(N_lower_left);

    vertices.push_back(V_upper_right);
    normals.push_back(N_upper_right);
                
    vertices.push_back(V_upper_left);
    normals.push_back(N_upper_left);

    // Add the second Triangle counter clockwize starting with the diagonal
    vertices.push_back(V_upper_right);
    normals.push_back(N_upper_right);

    vertices.push_back(V_lower_left);
    normals.push_back(N_lower_left);
                
    vertices.push_back(V_lower_right);
    normals.push_back(N_lower_right);
}

/*
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
void ParametricSurface::CreateBackFacingData(glm::vec3 const& V_lower_left,  glm::vec3 const& V_lower_right,
                                             glm::vec3 const& V_upper_right, glm::vec3 const& V_upper_left,
                                             std::vector<glm::vec3>& vertices,
                                             glm::vec3 const& N_lower_left,  glm::vec3 const& N_lower_right,
                                             glm::vec3 const& N_upper_right, glm::vec3 const& N_upper_left,
                                             std::vector<glm::vec3>& normals) const
{
    Trace("ParametricSurface", "CreateBackFacingData(...)");

    // Split Quadrilaterals into Triangles
    // Add Triangles clockwize starting with the diagonal and negate the normals
    vertices.push_back(V_upper_right);
    normals.push_back(-N_upper_right);

    vertices.push_back(V_lower_left);
    normals.push_back(-N_lower_left);
                
    vertices.push_back(V_upper_left);
    normals.push_back(-N_upper_left);
                
    // Add the second Triangle clockwize starting with the diagonal
    vertices.push_back(V_lower_left);
    normals.push_back(-N_lower_left);

    vertices.push_back(V_upper_right);
    normals.push_back(-N_upper_right);
                
    vertices.push_back(V_lower_right);
    normals.push_back(-N_lower_right);
}
