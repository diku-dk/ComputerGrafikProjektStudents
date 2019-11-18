#ifndef __PHONGSURFACE_H__
#define __PHONGSURFACE_H__

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <vector>

#include "glmutils.h"


/**
 * \class PhongSurface
 * implements the geometry of the surface defned by the Phong reflection function.
 */
class PhongSurface {
public:
    /**
     * Default constructor creates a PhongSurface with some default parameters.
     */
    PhongSurface();

    /**
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
    PhongSurface(glm::vec3 const& N, glm::vec3 const& L,
		 float I_a, float k_a, float O_a,
		 float I_d, float k_d, float O_d,
		 float I_s, float k_s, float O_s, float shininess);

    /**
     * Copy constructor creates a copy of its argument
     */
    PhongSurface(PhongSurface const& Src);

    /**
     * Destructor deletes the current instance of class PhongSurface.
     */
    virtual ~PhongSurface();

    /**
     * Assignment operator assigns its argument to the current instance.
     */
    PhongSurface& operator=(PhongSurface const& Src);

    /**
     * The number of subdivisions of the height angle, i.e. the phi-interval.
     * \return - The number of samples of the phi-interval.
     */
    int PhiSamples() const;

    /**
     * Changes the number of subdivisions of the height angle, i.e. the phi-interval.
     * \param newPhiSamples - the new number of samples of the phi-interval.
     * \return - the old number of samples of the phi-interval.
     */
    int PhiSamples(int newPhiSamples);

    /**
     * The number of subdivisions of the azimuth angle, i.e. the theta-interval.
     * \return - The number of samples of the theta-interval.
     */
    int ThetaSamples() const;

    /**
     * Changes the number of subdivisions of the azimuth angle, i.e. the theta-interval.
     * \param newThetaSamples - the new number of samples of the theta-interval.
     * \return - the old number of samples of the theta-interval.
     */
    int ThetaSamples(int newThetaSamples);


    /**
     * Computes a vertex on the Phong reflection surface given parameters phi and theta.
     * \param phi - the height angle of the view vector.
     * \param theta - the azimuth angle of the view vector.
     * \return - the 3D point corresponding to the parameters phi and theta.
     */
    glm::vec3 Vertex(float phi, float theta) const;

    /**
     * Computes the normal to the Phong reflection surface given parameters phi and theta.
     * \param phi - the height angle of the view vector.
     * \param theta - the azimuth angle of the view vector.
     * \return - the 3D normal to the phong surface corresponding to the parameters phi and theta.
     */
    glm::vec3 Normal(float phi, float theta) const;

    /**
     * Computes a number of vertices on the PhongSurface, depending on PhiSamples, and ThetaSamples.
     * \return - a std::vector<glm::vec3> containing the computed the vertices.
     */
    std::vector<glm::vec3> const& Vertices();

    /**
     * Computes a number of normals to the PhongSurface, depending on PhiSamples, and ThetaSamples.
     * \return - a std::vector<glm::vec3> containing the computed the normals.
     */
    std::vector<glm::vec3> const& Normals();

protected:

private:
    /**
     * Initializes the private variables.
     */
    void Initialize();

    /**
     * The view vector used to visualize the phong surface.
     * \param phi - the height angle of the view vector.
     * \param theta - the azimuth angle of the view vector.
     * \return - the 3D view vector.
     */
    glm::vec3 V(float phi, float theta) const;

    /**
     * The partial derivative of the view vector with respect to phi.
     * \param phi - the height angle of the view vector.
     * \param theta - the azimuth angle of the view vector.
     * \return - the partial derivative wrt. phi of the 3D view vector.
     */
    glm::vec3 dVdphi(float phi, float theta) const;

    /**
     * The partial derivative of the view vector with respect to theta.
     * \param phi - the height angle of the view vector.
     * \param theta - the azimuth angle of the view vector.
     * \return - the partial derivative wrt. theta of the 3D view vector.
     */
    glm::vec3 dVdtheta(float phi, float theta) const;

    /**
     * The reflected intensity defined by the Phong reflection function
     * \param phi - the height angle of the view vector.
     * \param theta - the azimuth angle of the view vector.
     */
    float P(float phi, float theta) const;

    /**
     * The partial derivative of the phong reflection function with respect to phi.
     * \param phi - the height angle of the view vector.
     * \param theta - the azimuth angle of the view vector.
     * \return - the partial derivative wrt. phi of the phong reflection function.
     */
    float dPdphi(float phi, float theta) const;
    
    /**
     * The partial derivative of the phong reflection function with respect to theta.
     * \param phi - the height angle of the view vector.
     * \param theta - the azimuth angle of the view vector.
     * \return - the partial derivative wrt. theta of the phong reflection function.
     */
    float dPdtheta(float phi, float theta) const;


    // Private Variables

    // The vertices of the phong surface
    bool verticesOK;
    std::vector<glm::vec3> vertices;

    // The normals of the phong surface
    bool normalsOK;
    std::vector<glm::vec3> normals;

    // The normal vector supplied by the user
    glm::vec3 N_user;

    // The light vector supplied by the user
    glm::vec3 L_user;

    // The reflection vector defined by N_user and L_user
    glm::vec3 R_user;

    // The dot product of N_user and L_user

    float N_user_dot_L_user;

    // Ambient material parameters
    float I_a;
    float k_a;
    float O_a;

    // Diffuse material parameters
    float I_d;
    float k_d;
    float O_d;
    
    // Specular material parameters
    float I_s;
    float k_s;
    float O_s;
    float shininess;

    // The number of samples of the height angle phi
    float phi_start;

    // The stop value of the height angle phi.
    float phi_stop;

    // The number of samples of the height angle, i.e. the phi-angle.
    int N_phi;

    // The spacing between the samples of the height angle, i.e. the phi-interval
    float delta_phi;

    // The start value of the azimuth angle theta.
    float theta_start;

    // The stop value of the azimuth angle theta.
    float theta_stop;

    // The number of samples of the azimuth angle, i.e. the theta-angle.
    int N_theta;

    // The spacing between the samples of the azimuth angle, i.e. the theta-interval
    float delta_theta;
};

#endif
