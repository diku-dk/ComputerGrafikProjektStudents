#ifndef __RASTERMAN_CAMERA_H__
#define __RASTERMAN_CAMERA_H__

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <string>
#include <cctype>


#include "traceinfo.h"
#include "glmutils.h"


/**
 * \class Camera
 * A class which implements a virtual camera
 */ 
class Camera {
public:
    /**
     * Default constructor, creates a camera with default values of the defining parameters.
     */
    Camera();

    /** 
     * Parameterized constructor, creates a camere with the parameteres given.
     * \param vrp - a vector which specifies the View Reference Point in world coordinates.
     * \param vpn - a vector which specifies the View Plane Normal in world coordinates.
     * \param vup - a vector which specifies the View Up vector in world coordinates.
     * \param prp - a vector which specifies the Projection Reference Point in eye coordinates.
     * \param lower_left_window - a vector which specifies the lower left corner of the window in eye coordinates.
     * \param upper_right_window - a vector which specifies the upper right corner of the window in eye coordinates.
     * \param front_plane - the z-coordinate of the front clipping plane, relative to vrp, i.e. in eye coordinates.
     * \param back_plane - the z-coordinate of the back clipping plane, relative to vrp, i.e. in eye coordinates.
     * \param x_viewport - the x-coordinate of the viewport on the screen.
     * \param y_viewport - the y-coordinate of the viewport on the screen.
     * \param viewport_width - the width of the viewport on the screen.
     * \param viewport_height - the height of the viewport on the screen.
     */
    Camera(glm::vec3 const& vrp, glm::vec3  const& vpn, glm::vec3  const& vup, glm::vec3  const& prp,
	   glm::vec2  const& lower_left_window, glm::vec2  const& upper_right_window,
	   float front_plane, float back_plane,
	   float x_viewport     = -1.0f, float y_viewport      = -1.0f,
	   float viewport_width =  2.0f, float viewport_height =  2.0f);
 
    /**
     * Copy constructor, creates a copy of its parameter.
     * \param camera - the camera object which shuld be copied.
     */
   Camera(Camera const& camera);

    /**
     * Destructor, cleans up the camere and destroys the object.
     */
    virtual ~Camera();

    /**
     * Assignment operator, assigns its parameter to the current instance of class Camera
     * \param camera - the new value of class Camera.
     */
    Camera& operator=(Camera const& camera);

    /**
     * \return the current ViewOrientation matrix.
     */
    glm::mat4x4 ViewOrientation() const;

    /**
     * \return the inverse of the current ViewOrientation matrix.
     */
    glm::mat4x4 InvViewOrientation() const;

    /**
     * \return the current ViewProjection matrix.
     */
    glm::mat4x4 ViewProjection() const;

    /**
     * \return the inverse of the current ViewProjection matrix.
     */
    glm::mat4x4 InvViewProjection() const;

    /**
     * \return the current WindowViewport matrix.
     */
    glm::mat4x4 WindowViewport() const;

    /**
     * \return the inverse of the current WindowViewport matrix.
     */
    glm::mat4x4 InvWindowViewport() const;

    /**
     * \return the current transformation matrix = WindowViewport() * ViewProjection() * ViewOrientation().
     */
    glm::mat4x4 CurrentTransformationMatrix();

    /**
     * \return the inverse of the current transformation 
     * matrix = InvViewOrientation() * InvViewProjection() * InvWindowViewport().
     */
    glm::mat4x4 InvCurrentTransformationMatrix();

    /**
     * \return the current value of the View Reference Point.
     */
    glm::vec3 const& VRP() const;

    /**
     * Changes the value of the View Reference Point.
     * \param vrp - the new View Reference Point
     */
    void VRP(glm::vec3 const& vrp);

    /**
     * \return the current value of the View Plane Normal.
     */
    glm::vec3 const& VPN() const;

    /**
     * Changes the value of the View Plane Normal.
     * \param vpn - the new View Plane Normal.
     */
    void VPN(glm::vec3 const& vpn);

    /**
     * \return the current value of the View Up vector.
     */
    glm::vec3 const& VUP() const;

    /**
     * Changes the value of the View Up vector.
     * \param vup - the new View Up vector.
     */
    void VUP(glm::vec3 const& vup);

    /**
     * \return the current value of the Projection Reference Point.
     */
    glm::vec3 const& PRP() const;

    /**
     * Changes the value of the Projection Reference Point.
     * \param prp - the new Projection Reference Point.
     */
    void PRP(glm::vec3 const& prp);

    /**
     * \return the lower left corner of the current camera window.
     */
    glm::vec2 const& WinLowerLeft() const;

    /**
     * Changes the lower left corner of the camera window.
     * \param lower_left_window - the new value of the lower left corner of the window.
     */
    void WinLowerLeft(glm::vec2 const& lower_left_window);

    /**
     * \return the upper right corner of the current camera window.
     */
    glm::vec2 const& WinUpperRight() const;

    /**
     * Changes the upper right corner of the camera window.
     * \param upper_right_window - the new value of the upper right corner of the window.
     */
    void WinUpperRight(glm::vec2 const& upper_right_window);

    /**
     * \return the value of the z-coordinate of the Back Clipping Plane.
     */
    float FrontClippingPlane() const;

    /**
     * Changes the z-value of the Front Clipping Plane.
     * \param front_plane - the new value of the z-coordinate of the Front Clipping Plane.
     */
    void FrontClippingPlane(float const front_plane);

    /**
     * \return the value of the z-coordinate of the Back Clipping Plane.
     */
    float BackClippingPlane() const;

    /**
     * Changes the z-value of the Back Clipping Plane.
     * \param back_plane - the new value of the z-coordinate of the Back Clipping Plane.
     */
    void BackClippingPlane(float const back_plane);

    /**
     * \return - the value of the x-coordinate of the viewport on the screen
     */
    float XPosition() const;

    /**
     * Changes the x-coordinate of the viewport on the screen
     * \param new_x_position - the new x-coordinate of the viewport
     */
    void XPosition(float new_x_position);

    /**
     * \return - the value of the y-coordinate of the viewport on the screen
     */
    float YPosition() const;

    /**
     * Changes the y-coordinate of the viewport on the screen
     * \param new_y_position - the new y-coordinate of the viewport
     */
    void YPosition(float new_y_position);

    /**
     * \return - the value of the Viewport width on the screen.
     */
    float ViewportWidth() const;

    /**
     * Changes the Viewport width on the screen.
     * \param new_viewport_width - the new value of the Viewport width
     */
    void ViewportWidth(int new_viewport_width);

    /**
     * \return - the value of the Viewport height on the screen.
     */
    float ViewportHeight() const;

    /**
     * Changes the Viewport height on the screen.
     * \param new_viewport_height - the new value of the Viewport height
     */
    void ViewportHeight(int new_viewport_height);

protected:

private:
    /**
     * Compute the View Orientation Matrix
     * \param vrp - the View Reference Point.
     * \param vpn - the View Plane Normal.
     * \param vup - the View Up vector.
     * \return - the computed ViewOrientation matrix.
     */
    void ComputeViewOrientation(glm::vec3& vrp, glm::vec3& vpn, glm::vec3& vup);

    /**
     * Compute the Projection Orientation Matrix.
     * \param prp - the Projection Reference Point.
     * \param lower_left_window - the lower left corner of the window.
     * \param upper_right_window - the upper right corner of the window.
     * \param front_clipping_plane - the z-coordinate of the front clipping plane.
     * \param back_clipping_plane - the z-coordinate of the back clipping plane.
     * \return - the computed ViewProjection matrix.
     */
    void ComputeViewProjection(glm::vec3& prp, 
			       glm::vec2& lower_left_window, glm::vec2& upper_right_window,
			       float front_clipping_plane, float back_clipping_plane);

    /**
     * Computes the Window Viewport Matrix.
     * \param x_viewport - the x-coordinate of the viewport.
     * \param y_viewport - the y-coordinate of the viewport.
     * \param viewport_width - the width of the screen viewport.
     * \param viewport_height - the height of the screen viewport.
     * \return - the computed ViewportViewport matrix.
     */
    void ComputeWindowViewport(float x_viewport, float y_viewport, float viewport_width, float viewport_height);
 
    // The View Orientation Matrix
    glm::mat4x4 vieworientationmatrix;
    glm::mat4x4 invvieworientationmatrix;
    
    
    // The View Projection Matrix
    glm::mat4x4 viewprojectionmatrix;
    glm::mat4x4 invviewprojectionmatrix;

    // The Window Viewport Matrix
    glm::mat4x4 windowviewportmatrix;
    glm::mat4x4 invwindowviewportmatrix;

    // The Current Transformation Matrix;
    glm::mat4x4 currenttransformationmatrix;
    glm::mat4x4 invcurrenttransformationmatrix;

    // The View Reference Point
    glm::vec3 vrp;

    // The View Plane Normal
    glm::vec3 vpn;

    // The View Up vector
    glm::vec3 vup;

    // The Projection Reference Point
    glm::vec3 prp;

    // The lower left corner of the window
    glm::vec2 lower_left_window;

    // The upper right corner of the window
    glm::vec2 upper_right_window;

    // The front clipping plane
    float front_plane;

    // The back clipping plane
    float back_plane;

    // The x-coordinate of the viewport
    float x_viewport;

    // The y-coordinate of the viewport
    float y_viewport;

    // Viewport width
    float viewport_width;

    // Viewport height
    float viewport_height;
};

#endif
