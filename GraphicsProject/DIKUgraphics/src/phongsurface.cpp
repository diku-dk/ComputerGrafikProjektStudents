#define _USE_MATH_DEFINES

#include "traceinfo.h"
#include "phongsurface.h"

/*
 * \class PhongSurface
 * implements the geometry of the surface defned by the Phong reflection function.
 */

// Public member functions

/*
 * Default constructor creates a PhongSurface with some default parameters.
 */
PhongSurface::PhongSurface()
            : N_user(glm::vec3(0.0f, 0.0f, 1.0f)), L_user(glm::vec3(-0.8f, -0.5f, 1.0f)),
              I_a(0.2f), k_a(0.0f), O_a(0.2f),
              I_d(1.0f), k_d(0.5f), O_d(1.0f),
              I_s(1.0f), k_s(0.4f), O_s(1.0f), shininess(30.0f),
              N_phi(10), N_theta(20)
          
{
    this->Initialize();
}

/*
 * Parameterized constructor creates a PhongSurface with parameters given by the arguments.
 * \param N - the surface normal.
 * \param L - the light vector.
 * \param I_a - the color of the Ambient light source.
 * \param k_a - the Ambient reflection coefficient of the surface.
 * \param O_a - the Ambient color of the surface.
 * \param I_d - the Diffuse color of the light source.
 * \param k_d - the Diffuse reflection coefficient of the surface.
 * \param O_d - the Diffuse color of the surface.
 * \param I_s - the Specular color of the light source.
 * \param k_s - the Specular reflection coeffficient of the surface.
 * \param O_s - the Specular color of the surface.
 * \param shininess - the Shininess of the surface.
 */
PhongSurface::PhongSurface(glm::vec3 const& N, glm::vec3 const& L,
              float I_a, float k_a, float O_a,
              float I_d, float k_d, float O_d,
              float I_s, float k_s, float O_s, float shininess)
            : N_user(N), L_user(L),
              I_a(I_a), k_a(k_a), O_a(O_a),
              I_d(I_d), k_d(k_d), O_d(O_d),
              I_s(I_s), k_s(k_s), O_s(O_s), shininess(shininess),
              N_phi(10), N_theta(20)
{
    this->Initialize();
}

/*
 * Copy constructor creates a copy of its argument
 */
PhongSurface::PhongSurface(PhongSurface const& Src)
{
    this->verticesOK = Src.verticesOK;
    this->vertices   = Src.vertices;

    this->normalsOK  = Src.normalsOK;
    this->normals    = Src.normals;

    this->N_user = Src.N_user;
    this->L_user = Src.L_user;
    this->N_user_dot_L_user = Src.N_user_dot_L_user;

    this->I_a = Src.I_a;
    this->k_a = Src.k_a;
    this->O_a = Src.O_a;

    this->I_d = Src.I_d;
    this->k_d = Src.k_d;
    this->O_d = Src.O_d;

    this->I_s = Src.I_s;
    this->k_s = Src.k_s;
    this->O_s = Src.O_s;
    this->shininess = Src.shininess;

    this->phi_start = Src.phi_start;
    this->phi_stop  = Src.phi_stop;
    this->N_phi     = Src.N_phi;
    this->delta_phi = Src.delta_phi;

    this->theta_start = Src.theta_start;
    this->theta_stop  = Src.theta_stop;
    this->N_theta     = Src.N_theta;
    this->delta_theta = Src.delta_theta;
}

/*
 * Destructor deletes the current instance of class PhongSurface.
 */
PhongSurface::~PhongSurface()
{}

/*
 * Assignment operator assigns its argument to the current instance.
 */
PhongSurface& PhongSurface::operator=(PhongSurface const& Src)
{
    if (this != &Src) {
        this->verticesOK = Src.verticesOK;
        this->vertices   = Src.vertices;

        this->normalsOK  = Src.normalsOK;
        this->normals    = Src.normals;

        this->N_user = Src.N_user;
        this->L_user = Src.L_user;
        this->N_user_dot_L_user = Src.N_user_dot_L_user;

        this->I_a = Src.I_a;
        this->k_a = Src.k_a;
        this->O_a = Src.O_a;

        this->I_d = Src.I_d;
        this->k_d = Src.k_d;
        this->O_d = Src.O_d;

        this->I_s = Src.I_s;
        this->k_s = Src.k_s;
        this->O_s = Src.O_s;
        this->shininess = Src.shininess;

        this->phi_start = Src.phi_start;
        this->phi_stop  = Src.phi_stop;
        this->N_phi     = Src.N_phi;
        this->delta_phi = Src.delta_phi;

        this->theta_start = Src.theta_start;
        this->theta_stop  = Src.theta_stop;
        this->N_theta     = Src.N_theta;
        this->delta_theta = Src.delta_theta;
    }
    return *this;
}

/*
 * The number of subdivisions of the height angle, i.e. the phi-interval.
 * \return - The number of samples of the phi-interval.
 */
int PhongSurface::PhiSamples() const
{
    return this->N_phi;
}

/*
 * Changes the number of subdivisions of the height angle, i.e. the phi-interval.
 * \param newPhiSamples - the new number of samples of the phi-interval.
 * \return - the old number of samples of the phi-interval.
 */
int PhongSurface::PhiSamples(int newPhiSamples)
{
    int old_N_phi = this->N_phi;
    this->N_phi = newPhiSamples;
    this->delta_phi = (this->phi_stop - this->phi_start) / float(this->N_phi);
    this->verticesOK = false;
    this->normalsOK  = false;
    return old_N_phi;
}

/*
 * The number of subdivisions of the azimuth angle, i.e. the theta-interval.
 * \return - The number of samples of the theta-interval.
 */
int PhongSurface::ThetaSamples() const
{
    return this->N_theta;
}

/*
 * Changes the number of subdivisions of the azimuth angle, i.e. the theta-interval.
 * \param newThetaSamples - the new number of samples of the theta-interval.
 * \return - the old number of samples of the theta-interval.
 */
int PhongSurface::ThetaSamples(int newThetaSamples)
{
    int old_N_theta = this->N_theta;
    this->N_theta = newThetaSamples;
    this->delta_theta = (this->theta_stop - this->theta_start) / float(this->N_theta);
    this->verticesOK = false;
    this->normalsOK  = false;
    return old_N_theta;
}

/*
 * Computes a vertex on the Phong reflection surface given parameters phi and theta.
 * \param phi - the height angle of the view vector.
 * \param theta - the azimuth angle of the view vector.
 * \return - the 3D point corresponding to the parameters phi and theta.
 */
glm::vec3 PhongSurface::Vertex(float phi, float theta) const
{
    //return this->V(phi, theta);

    glm::vec3 vertex = this->P(phi, theta) * this->V(phi, theta);
    return vertex;
}

/*
 * Computes the normal to the Phong reflection surface given parameters phi and theta.
 * \param phi - the height angle of the view vector.
 * \param theta - the azimuth angle of the view vector.
 * \return - the 3D normal to the phong surface corresponding to the parameters phi and theta.
 */
glm::vec3 PhongSurface::Normal(float phi, float theta) const
{
    glm::vec3 Dphi = this->dPdphi(phi, theta) * this->V(phi, theta)
                     + this->P(phi, theta) * this->dVdphi(phi, theta);
    glm::vec3 Dtheta = this->dPdtheta(phi, theta) * this->V(phi, theta)
                       + this->P(phi, theta) * this->dVdtheta(phi, theta);
    glm::vec3 normal = glm::cross(Dtheta, Dphi);

    if (normal != glm::vec3(0.0f)) {
    normal = glm::normalize(normal);
    }
    return normal;
}

/*
 * Computes a number of vertices on the PhongSurface, depending on PhiSamples, and ThetaSamples.
 * \return - a std::vector<glm::vec3> containing the computed the vertices.
 */
std::vector<glm::vec3> const& PhongSurface::Vertices()
{
    if (!this->verticesOK) {
        this->vertices.clear();
        for (float phi = this->phi_start; phi < this->phi_stop; phi += this->delta_phi) {
            for (float theta = this->theta_start; theta < this->theta_stop; theta += delta_theta) {
                glm::vec3 v_11 = this->Vertex(phi, theta);
                glm::vec3 v_12 = this->Vertex(phi, theta + this->delta_theta);
                glm::vec3 v_21 = this->Vertex(phi + this->delta_phi, theta);
                glm::vec3 v_22 = this->Vertex(phi + this->delta_phi, theta + this->delta_theta);

                // The first triangle
                this->vertices.push_back(v_11);
                this->vertices.push_back(v_12);
                this->vertices.push_back(v_22);
        
                // The second triangle
                this->vertices.push_back(v_11);
                this->vertices.push_back(v_22);
                this->vertices.push_back(v_21);
            }
        }
        this->verticesOK = true;
    }
    return this->vertices;
}

/*
 * Computes a number of normals to the PhongSurface, depending on PhiSamples, and ThetaSamples.
 * \return - a std::vector<glm::vec3> containing the computed the normals.
 */
std::vector<glm::vec3> const& PhongSurface::Normals()
{
    if (!this->normalsOK) {
        this->normals.clear();
        for (float phi = this->phi_start; phi < this->phi_stop; phi += this->delta_phi) {
            for (float theta = this->theta_start; theta < this->theta_stop; theta += delta_theta) {
                glm::vec3 n_11 = this->Normal(phi, theta);
                glm::vec3 n_12 = this->Normal(phi, theta + delta_theta);
                glm::vec3 n_21 = this->Normal(phi + delta_phi, theta);
                glm::vec3 n_22 = this->Normal(phi + delta_phi, theta + delta_theta);

                // The first triangle
                this->normals.push_back(n_11);
                this->normals.push_back(n_12);
                this->normals.push_back(n_22);

                // The second triangle
                this->normals.push_back(n_11);
                this->normals.push_back(n_22);
                this->normals.push_back(n_21);
            }
        }
        this->normalsOK = true;
    }
    return this->normals;
}

// Protected member functions

// Private member functions

/*
 * Initializes the private variables.
 */
void PhongSurface::Initialize()
{
    // Normalize the vectors and compute a dot product
    this->N_user = glm::normalize(this->N_user);
    this->L_user = glm::normalize(this->L_user);
    this->R_user = 2.0f * glm::dot(this->N_user, this->L_user) * this->N_user - this->L_user;
    this->R_user = glm::normalize(this->R_user);
    this->N_user_dot_L_user = glm::dot(this->N_user, this->L_user);
    
    // Define the range and steps of the height angle phi
    this->phi_start = 0.0f;
    this->phi_stop = M_PI / 2.0f;
    this->delta_phi   = (this->phi_stop - this->phi_start) / float(this->N_phi);

    // Define the range and steps of the azimuth angle theta
    this->theta_start= -M_PI;
    this->theta_stop =  M_PI;
    this->delta_theta = (this->theta_stop - this->theta_start) / float(this->N_theta);

    // Neither the Vertices nor the Normals are computed yet, so they are not OK.
    this->verticesOK = false;
    this->normalsOK  = false;
}

/*
 * The view vector used to visualize the phong surface.
 * \param phi - the height angle of the view vector.
 * \param theta - the azimuth angle of the view vector.
 * \return - the 3D view vector.
 */
glm::vec3 PhongSurface::V(float phi, float theta) const
{
    glm::vec3 view_vector(glm::cos(phi) * glm::cos(theta), glm::cos(phi) * glm::sin(theta), glm::sin(phi));
    return view_vector;
}

/*
 * The partial derivative of the view vector with respect to phi.
 * \param phi - the height angle of the view vector.
 * \param theta - the azimuth angle of the view vector.
 * \return - the partial derivative wrt. phi of the 3D view vector.
 */
glm::vec3 PhongSurface::dVdphi(float phi, float theta) const
{
    glm::vec3 Dview_vector_Dphi(-(glm::sin(phi) * glm::cos(theta)), -(glm::sin(phi) * glm::sin(theta)), glm::cos(phi));
    return Dview_vector_Dphi;
}

/*
 * The partial derivative of the view vector with respect to theta.
 * \param phi - the height angle of the view vector.
 * \param theta - the azimuth angle of the view vector.
 * \return - the partial derivative wrt. theta of the 3D view vector.
 */
glm::vec3 PhongSurface::dVdtheta(float phi, float theta) const
{
    glm::vec3 Dview_vector_Dtheta(-(glm::cos(phi) * glm::sin(theta)), glm::cos(phi) * glm::cos(theta), 0.0f);
    return Dview_vector_Dtheta;
}

/*
 * The reflected intensity defined by the Phong reflection function
 * \param phi - the height angle of the view vector.
 * \param theta - the azimuth angle of the view vector.
 * \return - the intensity value of the Phong reflection function.
 */
float PhongSurface::P(float phi, float theta) const
{
    float RdotV = glm::dot(this->R_user, this->V(phi, theta));

    float Pvalue = 0.0f;
    Pvalue += this->k_a * this->O_a * this->I_a;
    Pvalue += this->k_d * this->O_d * this->I_d * this->N_user_dot_L_user;
    Pvalue += this->k_s * this->O_s * this->I_s * glm::pow(RdotV, this->shininess);

    return Pvalue;
}

/*
 * The partial derivative of the phong reflection function with respect to phi.
 * \param phi - the height angle of the view vector.
 * \param theta - the azimuth angle of the view vector.
 * \return - the partial derivative wrt. phi of the phong reflection function.
 */
float PhongSurface::dPdphi(float phi, float theta) const
{
    float RdotV = glm::dot(this->R_user, this->V(phi, theta));
    float dPvalue_dphi = this->k_s * this->O_s * this->I_s * this->shininess
                         * glm::pow(RdotV, this->shininess - 1.0f)
                         * glm::dot(this->R_user, this->dVdphi(phi, theta));
    return dPvalue_dphi;
}
    
/*
 * The partial derivative of the phong reflection function with respect to theta.
 * \param phi - the height angle of the view vector.
 * \param theta - the azimuth angle of the view vector.
 * \return - the partial derivative wrt. theta of the phong reflection function.
 */
float PhongSurface::dPdtheta(float phi, float theta) const
{
    float RdotV = glm::dot(this->R_user, this->V(phi, theta));
    float dPvalue_dtheta = this->k_s * this->O_s * this->I_s
                           * this->shininess * glm::pow(RdotV, this->shininess - 1.0f)
                           * glm::dot(this->R_user, this->dVdtheta(phi, theta));
    return dPvalue_dtheta;
}
