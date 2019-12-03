#ifndef __GLM_UTILS_H__
#define __GLM_UTILS_H__

/**
 * \file glmutils.h
 */

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <string>
#include <cctype>

// Danger: Use the experimental packages
#define GLM_ENABLE_EXPERIMENTAL

// Use radians by default
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/integer.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include "traceinfo.h"

/**
 * \namespace glm
 *
 * \brief
 * This library expands the OpenGL glm mathematical library with a number of utility functions. \n
 * There are also operators to write vectors and matrices to an ostream.
 *
 * A set of utility functions which makes an alternative interface to the geometic transformations in the glm library.
 * The intent is to make it easier to do the ordinary 2D and 3D geometric transformations and the inverses.
 *
 * \author Knud Henriksen, kaiip@diku.dk, Department of Computer Science, University of Copenhagen, Denmark.
 */
namespace glm {
    /**
     * The vextor rotated pi / 2 counter-clockwize.
     * \param vec - The vector to be rotated.
     * \return The rotated vector.
     */
     glm::vec2 perp(glm::vec2 const& vec);

    /**
     * \name 2D geometric transformations
     * Funcions which implement 2D geometric transformations and their inverses.
     */
    
    /**
     * Creates a 3x3 matrix which performs a 2D translation
     * \param dx - the x-component of the translation vector
     * \param dy - the y-component of the translation vector
     * \return a 3x3 matrix performing the translation
     */
    glm::mat3x3 translate(float dx, float dy);

    /**
     * Creates a 3x3 matrix which performs the inverse of a 2D translation
     * \param dx - the x-component of the translation vector
     * \param dy - the y-component of the translation vector
     * \return a 3x3 matrix performing the inverse translation
     */
    glm::mat3x3 invtranslate(float dx, float dy);
    
    /**
     * Creates a 3x3 matrix which performs a 2D translation
     * \param t - a vector containing the x-, and y-components of the translation
     * \return a 3x3 matrix performing the translation
     */
    glm::mat3x3 translate(glm::vec2 const& t);

    /**
     * Creates a 3x3 matrix which performs the inverse of a 2D translation
     * \param t - a vector containing the x-, and y-components of the translation
     * \return a 3x3 matrix performing the inverse translation
     */
    glm::mat3x3 invtranslate(glm::vec2 const& t);
    
    /**
     * Creates a 3x3 matrix which performs a 2D scaling
     * \param sx - scale factor in the x-direction
     * \param sy - scale factor in the y-direction
     * \return a 3x3 matrix performing a scaling
     */
    glm::mat3x3 scale(float sx, float sy);

    /**
     * Creates a 3x3 matrix which performs the inverse of a 2D scaling
     * \param sx - scale factor in the x-direction
     * \param sy - scale factor in the y-direction
     * \return a 3x3 matrix performing the inverse scaling
     */
    glm::mat3x3 invscale(float sx, float sy);
    
    /**
     * Creates a 3x3 matrix which performs a 2D scaling
     * \param s - a vector containing the scale factors in x- and y-direction
     * \return a 3x3 matrix performing a scaling
     */
    glm::mat3x3 scale(glm::vec2 const& s);

    /**
     * Creates a 3x3 matrix which performs the inverse of a 2D scaling
     * \param s - a vector containing the scale factors in the x- and y-direction
     * \return a 3x3 matrix performing the inverse scaling
     */
    glm::mat3x3 invscale(glm::vec2 const& s);
    
    /**
     * Creates a 3x3 matrix which performs a 2D rotation
     * \param angle - the angle to rotate about the origin
     * \return a 3x3 matrix performing a rotation
     */
    glm::mat3x3 rotate(float angle);

    /**
     * Creates a 3x3 matrix which performs the inverse of a 2D rotation
     * \param angle - the angle to rotate about the origin
     * \return a 3x3 matrix performing inverse rotation
     */
    glm::mat3x3 invrotate(float angle);

    /**
     * Creates a 3x3 matrix which performs a 2D x-shear
     * \param shx - the shear factor
     * \return a 3x3 matrix performing a 2D x-shear
     */
    glm::mat3x3 shearX(float shx);

    /**
     * Creates a 3x3 matrix which performs the inverse of a 2D x-shear
     * \param shx - the shear factor
     * \return a 3x3 matrix performing the inverse 2D x-shear
     */
    glm::mat3x3 invshearX(float shx);
    
    /**
     * Creates a 3x3 matrix which performs a 2D y-shear
     * \param shy - the shear factor
     * \return a 3x3 matrix performing a 2D y-shear
     */
    glm::mat3x3 shearY(float shy);

    /**
     * Creates a 3x3 matrix which performs the inverse of a 2D y-shear
     * \param shy - the shear factor
     * \return a 3x3 matrix performing the inverse 2D y-shear
     */
    glm::mat3x3 invshearY(float shy);

    
    /**
     * \name 3D geometric transformations
     * Functions which implements 3D geometric transformations and their inverses.
     */
    
    /**
     * Creates a 4x4 matrix which performs a 3D translation.
     * \param dx - the x-component of the translation vector
     * \param dy - the y-component of the translation vector
     * \param dz - the z-component of the translation vector
     * \return a 4x4 matrix performing the translation
     */
    glm::mat4x4 translate(float dx, float dy, float dz);

    /**
     * Creates a 4x4 matrix which performs the inverse of a 3D translation
     * \param dx - the x-component of the translation vector
     * \param dy - the y-component of the translation vector
     * \param dz - the z-component of the translation vector
     * \return a 4x4 matrix performing the inverse translation
     */
    glm::mat4x4 invtranslate(float dx, float dy, float dz);

    /**
     * Creates a 4x4 matrix which performs a 3D translation.
     * \param t - a vector containing x, y and z components of the translation.
     * \return a 4x4 matrix performing the translation.
     */
    glm::mat4x4 translate(glm::vec3 const& t);

    /**
     * Creates a 4x4 matrix which performs the inverse of a 3D translation.
     * \param t - a vector containing x, y and z components of the inverse translation.
     * \return a 4x4 matrix performing the inverse translation.
     */
    glm::mat4x4 invtranslate(glm::vec3 const& t);
    
    /**
     * Creates a 4x4 matrix which performs a 3D scaling
     * \param sx - scale factor in the x-direction
     * \param sy - scale factor in the y-dirextion
     * \param sz - scale factor in the z-dirextion
     * \return a 4x4 matrix performing the scaling
     */
    glm::mat4x4 scale(float sx, float sy, float sz);

    /**
     * Creates a 4x4 matrix which performs the inverse of a 3D scaling
     * \param sx - scale factor in the x-direction
     * \param sy - scale factor in the y-dirextion
     * \param sz - scale factor in the z-dirextion
     * \return a 4x4 matrix performing the inverse scaling
     */
    glm::mat4x4 invscale(float sx, float sy, float sz);

    /**
     * Creates a 4x4 matrix which performs a 3D scaling
     * \param s - a vector containing the x, y, and z components of the scaling.
     * \return a 4x4 matrix performing the scaling.
     */
    glm::mat4x4 scale(glm::vec3 const& s);

    /**
     * Creates a 4x4 matrix which performs the inverse of a 3D scaling
     * \param s - a vector containing the x, y, and z components of the scaling.
     * \return a 4x4 matrix performing the inverse scaling.
     */
    glm::mat4x4 invscale(glm::vec3 const& s);
    
    /**
     * Create a 4x4 matrix which performs a 3D rotation around the x-axis
     * \param angle - the rotation angle
     * \return a 4x4 matrix performing the rotation
     */
    glm::mat4x4 rotateX(float angle);

    /**
     * Create a 4x4 matrix which performs the inverse of a 3D rotation around the x-axis
     * \param angle - the rotation angle
     * \return a 4x4 matrix performing the inverse rotation
     */
    glm::mat4x4 invrotateX(float angle);

    /**
     * Create a 4x4 matrix which performs a 3D rotation around the y-axis
     * \param angle - the rotation angle
     * \return a 4x4 matrix performing the rotation
     */
    glm::mat4x4 rotateY(float angle);

    /**
     * Create a 4x4 matrix which performs the inverse of a 3D rotation around the y-axis
     * \param angle - the rotation angle
     * \return a 4x4 matrix performing the inverse rotation
     */
    glm::mat4x4 invrotateY(float angle);

    /**
     * Create a 4x4 matrix which performs a 3D rotation around the z-axis
     * \param angle - the rotation angle
     * \return a 4x4 matrix performing the rotation
     */
    glm::mat4x4 rotateZ(float angle);
    
    /**
     * Create a 4x4 matrix which performs the inverse of a 3D rotation around the z-axis
     * \param angle - the rotation angle
     * \return a 4x4 matrix performing the inverse rotation
     */
    glm::mat4x4 invrotateZ(float angle);

#if 0
    /**
     * Create a 4x4 matrix which performs a 3D rotation around an arbitrary axis
     * \param angle - the rotation angle
     * \param axis - the rotation axis
     * \return a 4x4 matrix performing a rotation
     */
    glm::mat4x4 rotate(float angle, glm::vec3 const& axis);
#endif
  
    /**
     * Create a 4x4 matrix which performs the inverse of a 3D rotation around an arbitrary axis
     * \param angle - the rotation angle
     * \param axis - the rotation axis
     * \return a 4x4 matrix performing the inverse rotation
     */
    glm::mat4x4 invrotate(float angle, glm::vec3 const& axis);
    
    /**
     * Creates a 4x4 matrix which performs an XY-shear
     * \param sh_x - the shear factor in the x-direction
     * \param sh_y - the shear factor in the y-direction
     * \return a 4x4 matrix performing an XY shear
     */
    glm::mat4x4 shearXY(float sh_x, float sh_y);

    /**
     * Creates a 4x4 matrix which performs the inverse of an XY-shear
     * \param sh_x - the shear factor in the x-direction
     * \param sh_y - the shear factor in the y-direction
     * \return a 4x4 matrix performing the inverse XY shear
     */
    glm::mat4x4 invshearXY(float sh_x, float sh_y);

    /**
     * Creates a 4x4 matrix which performs an XY-shear
     * \param shearfactors - a vector containing the two shear factors
     * \return a 4x4 matrix performing an XY shear
     */
    glm::mat4x4 shearXY(glm::vec2 const& shearfactors);

    /**
     * Creates a 4x4 matrix which performs the inverse of an XY-shear
     * \param shearfactors - a vector containing the two shear factors
     * \return a 4x4 matrix performing inverse XY shear
     */
    glm::mat4x4 invshearXY(glm::vec2 const& shearfactors);

    /**
     * Creates a 4x4 matrix which performs an XZ-shear
     * \param sh_x - the shear factor in the x-direction
     * \param sh_z - the shear factor in the z-direction
     * \return a 4x4 matrix performing an XZ shear
     */
    glm::mat4x4 shearXZ(float sh_x, float sh_z);

    /**
     * Creates a 4x4 matrix which performs the inverse of an XZ-shear
     * \param sh_x - the shear factor in the x-direction
     * \param sh_z - the shear factor in the z-direction
     * \return a 4x4 matrix performing the inverse XZ shear
     */
    glm::mat4x4 invshearXZ(float sh_x, float sh_z);

    /**
     * Creates a 4x4 matrix which performs an XZ-shear
     * \param shearfactors - a vector containing the two shear factors
     * \return a 4x4 matrix performing an XZ shear
     */
    glm::mat4x4 shearXZ(glm::vec2 const& shearfactors);

    /**
     * Creates a 4x4 matrix which performs the inverse of an XZ-shear
     * \param shearfactors - a vector containing the two shear factors
     * \return a 4x4 matrix performing the inverse XZ shear
     */
    glm::mat4x4 invshearXZ(glm::vec2 const& shearfactors);

    /**
     * Creates a 4x4 matrix which performs an YZ-shear
     * \param sh_y - the shear factor in the y-direction
     * \param sh_z - the shear factor in the z-direction
     * \return a 4x4 matrix performing an YZ shear
     */
    glm::mat4x4 shearYZ(float sh_y, float sh_z);

    /**
     * Creates a 4x4 matrix which performs the inverse of an YZ-shear
     * \param sh_y - the shear factor in the y-direction
     * \param sh_z - the shear factor in the z-direction
     * \return a 4x4 matrix performing the inverse YZ shear
     */
    glm::mat4x4 invshearYZ(float sh_y, float sh_z);

    /**
     * Creates a 4x4 matrix which performs an XZ-shear
     * \param shearfactors - a vector containing the two shear factors
     * \return a 4x4 matrix performing an YZ shear
     */
    glm::mat4x4 shearYZ(glm::vec2 const& shearfactors);

    /**
     * Creates a 4x4 matrix which performs the inverse of an YZ-shear
     * \param shearfactors - a vector containing the two shear factors
     * \return a 4x4 matrix performing the inverse YZ shear
     */
    glm::mat4x4 invshearYZ(glm::vec2 const& shearfactors);

    /**
     * \name Utility operators
     * Utility operators for printing vectors and matrices.
     */

    /**
     * reads a glm::vec2 from an std::istream
     * \param s - a std::istream where the input should be read from.
     * \param v - a glm::vec2 which should be read.
     * \return the parameter s.
     */
    std::istream& operator>>(std::istream& s, glm::vec2& v);
  
    /**
     * writes a glm::vec2 to an std::ostream
     * \param s - a std::ostream where the output should be written.
     * \param v - a glm::vec2 which should be written.
     * \return the parameter s.
     */
    std::ostream& operator<<(std::ostream& s, glm::vec2 const& v);

    /**
     * reads a glm::vec3 from an std::istream
     * \param s - a std::istream where the input should be read from.
     * \param v - a glm::vec3 which should be read.
     * \return the parameter s.
     */
    std::istream& operator>>(std::istream& s, glm::vec3& v);
  
    /**
     * writes a glm::vec3 to an std::ostream
     * \param s - a std::ostream where the output should be written.
     * \param v - a glm::vec3 which should be written.
     * \return the parameter s.
     */
    std::ostream& operator<<(std::ostream& s, glm::vec3 const& v);

    /**
     * reads a glm::vec4 from an std::istream
     * \param s - a std::istream where the input should be read from.
     * \param v - a glm::vec4 which should be read.
     * \return the parameter s.
     */
    std::istream& operator>>(std::istream& s, glm::vec4& v);
  
    /**
     * writes a glm::vec4 to a std::ostream
     * \param s - a std::ostream& where the output should be written.
     * \param v - a glm::vec4& which should be written.
     * \return the parameter s.
     */
    std::ostream& operator<<(std::ostream& s, glm::vec4 const& v);

    /**
     * writes a glm::mat2x2 to a std::ostream
     * \param s - a std::ostream where the output should be written.
     * \param m - a glm::mat2x2 which should be written.
     * \return the parameter s.
     */
    std::ostream& operator<<(std::ostream& s, glm::mat2x2 const& m);

    /**
     * writes a glm::mat3x3 to a std::ostream
     * \param s - a std::ostream where the output should be written.
     * \param m - a glm::mat3x3 which should be written.
     * \return the parameter s.
     */
    std::ostream& operator<<(std::ostream& s, glm::mat3x3 const& m);

    /**
     * writes a glm::mat4x4 to a std::ostream
     * \param s - a std::ostream where the output should be written.
     * \param m - a glm::mat4x4 which should be written.
     * \return the parameter s.
     */
    std::ostream& operator<<(std::ostream& s, glm::mat4x4 const& m);
}

#endif
