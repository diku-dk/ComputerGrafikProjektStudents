#include "glmutils.h"


/*
 * Make it look like these functions are part of the glm library
 */
namespace glm {
    /*
     * The vextor rotated pi / 2 counter-clockwize.
     * \param vec - The vector to be rotated.
     * \return The rotated vector.
     */
     glm::vec2 perp(glm::vec2 const& vec)
     {
         return glm::vec2(-vec.y, vec.x);
     }
    
    /*
     * \name 2D geometric transformations
     * Funcions which implement 2D geometric transformations and their inverses.
     */

    /*
     * Creates a 3x3 matrix which performs a 2D translation
     * \param dx - the x-component of the translation vector
     * \param dy - the y-component of the translation vector
     * \return a 3x3 matrix performing a translation
     */
    glm::mat3x3 translate(float dx, float dy)
    {
	return glm::translate(glm::mat3x3(1.0f), glm::vec2(dx, dy));
    }

    /*
     * Creates a 3x3 matrix which performs the inverse of a 2D translation
     * \param dx - the x-component of the translation vector
     * \param dy - the y-component of the translation vector
     * \return a 3x3 matrix performing the inverse translation
     */
    glm::mat3x3 invtranslate(float dx, float dy)
    {
	return glm::translate(-dx, -dy);
    }

    /*
     * Creates a 3x3 matrix which performs a 2D translation
     * \param t - a vector containing the x- and y-components of the translation
     * \return a 3x3 matrix performing a translation
     */
    glm::mat3x3 translate(glm::vec2 const& t)
    {
	return glm::translate(glm::mat3x3(1.0f), t);
    }

    /*
     * Creates a 3x3 matrix which performs the inverse of a 2D translation
     * \param t - a vector containing the x-, and y-components of the translation
     * \return a 3x3 matrix performing the inverse translation
     */
    glm::mat3x3 invtranslate(glm::vec2 const& t)
    {
	return glm::translate(-t);
    }
    
    /*
     * Creates a 3x3 matrix which performs a 2D scaling
     * \param sx - scale factor in the x-direction
     * \param sy - scale factor in the y-direction
     * \return a 3x3 matrix performing a scaling
     */
    glm::mat3x3 scale(float sx, float sy)
    {
	return glm::scale(glm::mat3x3(1.0f), glm::vec2(sx, sy));
    }

    /*
     * Creates a 3x3 matrix which performs the inverse of a 2D scaling
     * \param sx - scale factor in the x-direction
     * \param sy - scale factor in the y-direction
     * \return a 3x3 matrix performing the inverse scaling
     */
    glm::mat3x3 invscale(float sx, float sy)
    {
	if ((sx == 0.0f) || (sy == 0.0f)) {
	    throw std::runtime_error("glm::invscale(sx, sy): one scale factor eqaul to zero");
	}
	return glm::scale(1.0f / sx, 1.0f / sy);
    }

    /**
     * Creates a 3x3 matrix which performs a 2D scaling
     * \param s - a vector containint the scale factors in x- and y-direction
     * \return a 3x3 matrix performing a scaling
     */
    glm::mat3x3 scale(glm::vec2 const& s)
    {
	return glm::scale(glm::mat3x3(1.0f), s);
    }

    /*
     * Creates a 3x3 matrix which performs the inverse of a 2D scaling
     * \param s - a vector containing the scale factors in x- and y-direction
     * \return a 3x3 matrix performing the inverse scaling
     */
    glm::mat3x3 invscale(glm::vec2 const& s)
    {
	return glm::invscale(s.x, s.y);
    }

    /*
     * Creates a 3x3 matrix which performs a 2D rotation
     * \param angle - the angle to rotate about the origin
     * \return a 3x3 matrix performing a rotation
     */
    glm::mat3x3 rotate(float angle)
    {
	return glm::rotate(glm::mat3x3(1.0f), angle);
    }
  
    /*
     * Creates a 3x3 matrix which performs the inverse of a 2D rotation
     * \param angle - the angle to rotate about the origin
     * \return a 3x3 matrix performing inverse rotation
     */
    glm::mat3x3 invrotate(float angle)
    {
	return glm::rotate(-angle);
    }
    
    /*
     * Creates a 3x3 matrix which performs a 2D x-shear
     * \param shx - the shear factor
     * \return a 3x3 matrix performing a 2D x-shear
     */
    glm::mat3x3 shearX(float shx)
    {
	return glm::column(glm::mat3x3(1.0f), 1, glm::vec3(shx, 1.0f, 0.0f));
    }

    /*
     * Creates a 3x3 matrix which performs the inverse of a 2D x-shear
     * \param shx - the shear factor
     * \return a 3x3 matrix performing the inverse 2D x-shear
     */
    glm::mat3x3 invshearX(float shx)
    {
	return glm::shearX(-shx);
    }
    
    /*
     * Creates a 3x3 matrix which performs a 2D y-shear
     * \param shy - the shear factor
     * \return a 3x3 matrix performing a 2D y-shear
     */
    glm::mat3x3 shearY(float shy)
    {
	return glm::column(glm::mat3x3(1.0f), 0, glm::vec3(1.0f, shy, 0.0f));
    }

     /**
     * Creates a 3x3 matrix which performs the inverse of a 2D y-shear
     * \param shy - the shear factor
     * \return a 3x3 matrix performing the inverse 2D y-shear
     */
    glm::mat3x3 invshearY(float shy)
    {
	return glm::shearY(-shy);
    }

    /*
     * \name 3D geometric transformations
     * Functions which implements 3D geometric transformations and their inverses.
     */

    /*
     * Creates a 4x4 matrix which performs a 3D translation
     * \param dx - the x-component of the translation vector
     * \param dy - the y-component of the translation vector
     * \param dz - the z-component of the translation vector
     * \return a 4x4 matrix performing the translation
     */
    glm::mat4x4 translate(float dx, float dy, float dz)
    {
	return glm::translate(glm::mat4x4(1.0f), glm::vec3(dx, dy, dz));
    }

    /*
     * Creates a 4x4 matrix which performs the inverse of a 3D translation
     * \param dx - the x-component of the translation vector
     * \param dy - the y-component of the translation vector
     * \param dz - the z-component of the translation vector
     * \return a 4x4 matrix performing the inverse translation
     */
    glm::mat4x4 invtranslate(float dx, float dy, float dz)
    {
	return glm::translate(-dx, -dy, -dz);
    }

    /*
     * Creates a 4x4 matrix which performs a 3D translation.
     * \param t - a vector containing x, y and z components of the translation.
     * \return a 4x4 matrix performing the translation.
     */
    glm::mat4x4 translate(glm::vec3 const& t)
    {
	return glm::translate(glm::mat4x4(1.0f), t);
    }

    /*
     * Creates a 4x4 matrix which performs the inverse of a 3D translation.
     * \param t - a vector containing x, y and z components of the inverse translation.
     * \return a 4x4 matrix performing the inverse translation.
     */
    glm::mat4x4 invtranslate(glm::vec3 const& t)
    {
	return glm::translate(-t);
    }
    
    /*
     * Creates a 4x4 matrix which performs a 3D scaling
     * \param sx - scale factor in the x-direction
     * \param sy - scale factor in the y-dirextion
     * \param sz - scale factor in the z-dirextion
     * \return a 4x4 matrix performing a scaling
     */
    glm::mat4x4 scale(float sx, float sy, float sz)
    {
	return scale(glm::mat4x4(1.0f), glm::vec3(sx, sy, sz));
    }

    /*
     * Creates a 4x4 matrix which performs the inverse of a 3D scaling
     * \param sx - scale factor in the x-direction
     * \param sy - scale factor in the y-dirextion
     * \param sz - scale factor in the z-dirextion
     * \return a 4x4 matrix performing the inverse scaling
     */
    glm::mat4x4 invscale(float sx, float sy, float sz)
    {
	if ((sx == 0.0f) || (sy == 0.0f) || (sz == 0.0f)) {
	    throw std::runtime_error("glm::invscale(sx, sy, sz): one scale factor equal to zero");
	}
	return glm::scale(1.0f / sx, 1.0f / sy, 1.0f / sz);
    }

    /*
     * Creates a 4x4 matrix which performs a 3D scaling
     * \param s - a vector containing the x, y, and z components of the scaling.
     * \return a 4x4 matrix performing the scaling.
     */
    glm::mat4x4 scale(glm::vec3 const& s)
    {
	return glm::scale(s.x, s.y, s.z);
    }

    /**
     * Creates a 4x4 matrix which performs the inverse of a 3D scaling
     * \param s - a vector containing the x, y, and z components of the scaling.
     * \return a 4x4 matrix performing the inverse scaling.
     */
    glm::mat4x4 invscale(glm::vec3 const& s)
    {
	return glm::invscale(s.x, s.y, s.z);
    }
    
    /*
     * Create a 4x4 matrix which performs a 3D rotation around the x-axis
     * \param angle - the rotation angle
     * \return a 4x4 matrix performing a translation
     */
    glm::mat4x4 rotateX(float angle)
    {
	return glm::rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f));
    }

    /**
     * Create a 4x4 matrix which performs the inverse of a 3D rotation around the x-axis
     * \param angle - the rotation angle
     * \return a 4x4 matrix performing the inverse rotation
     */
    glm::mat4x4 invrotateX(float angle)
    {
	return glm::rotateX(-angle);
    }
    
    /*
     * Create a 4x4 matrix which performs a 3D rotation around the y-axis
     * \param angle - the rotation angle
     * \return a 4x4 matrix performing a translation
     */
    glm::mat4x4 rotateY(float angle)
    {
	return glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    /*
     * Create a 4x4 matrix which performs the inverse of a 3D rotation around the y-axis
     * \param angle - the rotation angle
     * \return a 4x4 matrix performing the inverse rotation
     */
    glm::mat4x4 invrotateY(float angle)
    {
	return glm::rotateY(-angle);
    }
    
    /*
     * Create a 4x4 matrix which performs a 3D rotation around the z-axis
     * \param angle - the rotation angle
     * \return a 4x4 matrix performing a translation
     */
    glm::mat4x4 rotateZ(float angle)
    {
	return glm::rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f));
    }

    /*
     * Create a 4x4 matrix which performs the inverse of a 3D rotation around the z-axis
     * \param angle - the rotation angle
     * \return a 4x4 matrix performing the rotation
     */
    glm::mat4x4 invrotateZ(float angle)
    {
	return glm::rotateZ(-angle);
    }

#if 0
    /*
     * Create a 4x4 matrix which performs a 3D rotation around an arbitrary axis
     * \param angle - the rotation angle
     * \param axis - the rotation axis
     * \return a 4x4 matrix performing a rotation
     */
    glm::mat4x4 rotate(float angle, glm::vec3 const& axis)
    {
        return glm::rotate(angle, axis);
    }
#endif
  
    /*
     * Create a 4x4 matrix which performs the inverse of a 3D rotation around an arbitrary axis
     * \param angle - the rotation angle
     * \param axis - the rotation axis
     * \return a 4x4 matrix performing the inverse rotation
     */
    glm::mat4x4 invrotate(float angle, glm::vec3 const& axis)
    {
	return glm::rotate(-angle, axis);
    }
    
    /*
     * Creates a 4x4 matrix which performs an XY-shear
     * \param sh_x - the shear factor in the x-direction
     * \param sh_y - the shear factor in the y-direction
     * \return a 4x4 matrix performing an XY shear
     */
    glm::mat4x4 shearXY(float sh_x, float sh_y)
    {
	glm::vec4 shearparam(sh_x, sh_y, 1.0f, 0.0f);
	glm::mat4x4 SHxy(glm::column(glm::mat4x4(1.0f), 2, shearparam));
	return SHxy;
    }

    /**
     * Creates a 4x4 matrix which performs the inverse of an XY-shear
     * \param sh_x - the shear factor in the x-direction
     * \param sh_y - the shear factor in the y-direction
     * \return a 4x4 matrix performing the inverse XY shear
     */
    glm::mat4x4 invshearXY(float sh_x, float sh_y)
    {
	return glm::shearXY(-sh_x, -sh_y);
    }
    
    /*
     * Creates a 4x4 matrix which performs an XY-shear
     * \param shearfactors - a vector containing the two shear factors
     * \return a 4x4 matrix performing an XY shear
     */
    glm::mat4x4 shearXY(glm::vec2 const& shearfactors)
    {
	return shearXY(shearfactors[0], shearfactors[1]);
    }

    /*
     * Creates a 4x4 matrix which performs the inverse of an XY-shear
     * \param shearfactors - a vector containing the two shear factors
     * \return a 4x4 matrix performing inverse XY shear
     */
    glm::mat4x4 invshearXY(glm::vec2 const& shearfactors)
    {
	return glm::shearXY(-shearfactors);
    }
    
    /*
     * Creates a 4x4 matrix which performs an XZ-shear
     * \param sh_x - the shear factor in the x-direction
     * \param sh_z - the shear factor in the z-direction
     * \return a 4x4 matrix performing an XZ shear
     */
    glm::mat4x4 shearXZ(float sh_x, float sh_z)
    {
	glm::vec4 shearparam(sh_x, 1.0f, sh_z, 0.0f);
	glm::mat4x4 SHxz(glm::column(glm::mat4x4(1.0f), 1, shearparam));
	return SHxz;
    }

    /*
     * Creates a 4x4 matrix which performs the inverse of an XZ-shear
     * \param sh_x - the shear factor in the x-direction
     * \param sh_z - the shear factor in the z-direction
     * \return a 4x4 matrix performing the inverse XZ shear
     */
    glm::mat4x4 invshearXZ(float sh_x, float sh_z)
    {
	return glm::shearXZ(-sh_x, -sh_z);
    }
    
    /*
     * Creates a 4x4 matrix which performs an XZ-shear
     * \param shearfactors - a vector containing the two shear factors
     * \return a 4x4 matrix performing an XZ shear
     */
    glm::mat4x4 shearXZ(glm::vec2 const& shearfactors)
    {
	return shearXZ(shearfactors[0], shearfactors[1]);
    }

    /*
     * Creates a 4x4 matrix which performs the inverse of an XZ-shear
     * \param shearfactors - a vector containing the two shear factors
     * \return a 4x4 matrix performing the inverse XZ shear
     */
    glm::mat4x4 invshearXZ(glm::vec2 const& shearfactors)
    {
	return glm::shearXZ(-shearfactors);
    }
    
    /*
     * Creates a 4x4 matrix which performs an YZ-shear
     * \param sh_y - the shear factor in the y-direction
     * \param sh_z - the shear factor in the z-direction
     * \return a 4x4 matrix performing an YZ shear
     */
    glm::mat4x4 shearYZ(float sh_y, float sh_z)
    {
	glm::vec4 shearparam(1.0f, sh_y, sh_z, 0.0f);
	glm::mat4x4 SHyz(glm::column(glm::mat4x4(1.0f), 0, shearparam));
	
	return SHyz;
    }

    /*
     * Creates a 4x4 matrix which performs the inverse of an YZ-shear
     * \param sh_y - the shear factor in the y-direction
     * \param sh_z - the shear factor in the z-direction
     * \return a 4x4 matrix performing the inverse YZ shear
     */
    glm::mat4x4 invshearYZ(float sh_y, float sh_z)
    {
	return glm::shearYZ(-sh_y, -sh_z);
    }
    
    /*
     * Creates a 4x4 matrix which performs an YZ-shear
     * \param shearfactors - a vector containing the two shear factors
     * \return a 4x4 matrix performing an YZ shear
     */
    glm::mat4x4 shearYZ(glm::vec2 const& shearfactors)
    {
	return shearYZ(shearfactors[0], shearfactors[1]);
    }

    /*
     * Creates a 4x4 matrix which performs the inverse of an YZ-shear
     * \param shearfactors - a vector containing the two shear factors
     * \return a 4x4 matrix performing the inverse YZ shear
     */
    glm::mat4x4 invshearYZ(glm::vec2 const& shearfactors)
    {
	return glm::shearYZ(-shearfactors);
    }

    /*
     * \name Utility operators
     * Utility operators for printing vectors and matrices.
     */

    /*
     * reads a glm::vec2 from an std::istream
     * \param s - a std::istream where the input should be read from.
     * \param v - a glm::vec2 which should be read.
     * \return the parameter s.
     */
    std::istream& operator>>(std::istream& s, glm::vec2& v)
    {
        s >> v.x;
        s >> v.y;
    
        if (!s.good()) {
            std::ostringstream errormessage;
            errormessage << "glm::operator>>(std::istream&, glm::vec2&): Syntax error at istream" << std::endl;
            throw std::runtime_error(errormessage.str());
        }
        return s;
    }
  
    /*
     * Prints a vec2 to std::cout
     * \param s - a std::ostream& where the output should be written.
     * \param v - a glm::vec2& which should be written.
     * \return the parameter s.
     */
    std::ostream& operator<<(std::ostream& s, glm::vec2 const& v)
    {
	s << ' ';
	for (int i = 0; i < 2; ++i) {
	    s << std::setw(10) << std::setprecision(4) << v[i] << ' ';
	}
	return s;
    }

    /**
     * reads a glm::vec3 from an std::istream
     * \param s - a std::istream where the input should be read from.
     * \param v - a glm::vec3 which should be read.
     * \return the parameter s.
     */
    std::istream& operator>>(std::istream& s, glm::vec3& v)
    {
        s >> v.x;
        s >> v.y;
        s >> v.z;
    
        if (!s.good()) {
            std::ostringstream errormessage;
            errormessage << "glm::operator>>(std::istream&, glm::vec3&): Syntax error at istream" << std::endl;
            throw std::runtime_error(errormessage.str());
        }
        return s;
    }
  
    /*
     * Prints a vec3 to std::cout
     * \param s - a std::ostream& where the output should be written.
     * \param v - a glm::vec3& which should be written.
     * \return the parameter s.
     */
    std::ostream& operator<<(std::ostream& s, glm::vec3 const& v)
    {
	s << ' ';
	for (int i = 0; i < 3; ++i) {
	    s << std::setw(10) << std::setprecision(4) << v[i] << ' ';
	}
	return s;
    }

    /**
     * reads a glm::vec4 from an std::istream
     * \param s - a std::istream where the input should be read from.
     * \param v - a glm::vec4 which should be read.
     * \return the parameter s.
     */
    std::istream& operator>>(std::istream& s, glm::vec4& v)
    {
        s >> v.x;
        s >> v.y;
        s >> v.z;
        s >> v.w;
    
        if (!s.good()) {
            std::ostringstream errormessage;
            errormessage << "glm::operator>>(std::istream&, glm::vec3&): Syntax error at istream" << std::endl;
            throw std::runtime_error(errormessage.str());
        }
        return s;
    }
  
    /*
     * Prints a vec4 to std::cout
     * \param s - a std::ostream& where the output should be written.
     * \param v - a glm::vec4& which should be written.
     * \return the parameter s.
     */
    std::ostream& operator<<(std::ostream& s, glm::vec4 const& v)
    {
	for (int i = 0; i < 4; ++i) {
	    s << std::setw(10) << std::setprecision(4) << v[i] << ' ';
	}
	return s;
    }

    /*
     * Prints a mat2x2 to std::cout
     * \param s - a std::ostream where the output should be written.
     * \param m - a glm::mat2x2 which should be written.
     * \return the parameter s.
     */
    std::ostream& operator<<(std::ostream& s, glm::mat2x2 const& m)
    {
	for (int r = 0; r < 2; ++r) {
	    s << ' ';
	    for (int c = 0; c < 2; ++c) {
		s << std::setw(10) << std::setprecision(4) << m[c][r] << ' ' << '\t';
	    }
	    s << std::endl;
	}
	return s;
    }

    /*
     * Prints a mat3x3 to std::cout
     * \param s - a std::ostream where the output should be written.
     * \param m - a glm::mat3x3 which should be written.
     * \return the parameter s.
     */
    std::ostream& operator<<(std::ostream& s, glm::mat3x3 const& m)
    {
	for (int r = 0; r < 3; ++r) {
	    s << ' ';
	    for (int c = 0; c < 3; ++c) {
		s << std::setw(10) << std::setprecision(4) << m[c][r] << ' ' << '\t';
	    }
	    s << std::endl;
	}
	return s;
    }

    /*
     * Prints a mat4x4 to std::cout
     * \param s - a std::ostream where the output should be written.
     * \param m - a glm::mat4x4 which should be written.
     * \return the parameter s.
     */
    std::ostream& operator<<(std::ostream& s, glm::mat4x4 const& m)
    {
	for (int r = 0; r < 4; ++r) {
	    s << ' ';
	    for (int c = 0; c < 4; ++c) {
		s << std::setw(10) << std::setprecision(4) << m[c][r] << ' ' << '\t';
	    }
	    s << std::endl;
	}
	return s;
    }
}
