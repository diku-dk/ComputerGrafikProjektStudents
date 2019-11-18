#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/integer.hpp>

#include "edge.h"

/**
 * \class triangle_rasterizer
 * A class which scanconverts a triangle. It computes the pixels such that they are inside the triangle.
 */ 
class triangle_rasterizer {
public:
    /**
     * Parameterized constructor creates an instance of a triangle rasterizer
     * \param x1 - the x-coordinate of the first vertex
     * \param y1 - the y-coordinate of the first vertex
     * \param x2 - the x-coordinate of the second vertex
     * \param y2 - the y-coordinate of the second vertex
     * \param x3 - the x-coordinate of the third vertex
     * \param y3 - the y-coordinate of the third vertex
     */
    triangle_rasterizer(int x1, int y1, int x2, int y2, int x3, int y3);

    /**
     * Destroys the current instance of the triangle rasterizer
     */
    virtual ~triangle_rasterizer();

    /**
     * Returns a vector which contains alle the pixels inside the triangle
     */
    std::vector<glm::vec3> all_pixels();

    /**
     * Checks if there are fragments/pixels inside the triangle ready for use
     * \return true if there are more fragments in the triangle, else false is returned
     */
    bool more_fragments() const;

    /**
     * Computes the next fragment inside the triangle
     */
    void next_fragment();

    /**
     * Returns the current x-coordinate of the current fragment/pixel inside the triangle
     * It is only valid to call this function if "more_fragments()" returns true,
     * else a "runtime_error" exception is thrown
     * \return The x-coordinate of the current triangle fragment/pixel
     */
    int x() const;

    /**
     * Returns the current y-coordinate of the current fragment/pixel inside the triangle
     * It is only valid to call this function if "more_fragments()" returns true,
     * else a "runtime_error" exception is thrown
     * \return The y-coordinate of the current triangle fragment/pixel
     */
    int y() const;

private:
    /**
     * Initializes the TriangleRasterizer with the three vertices
     * \param x1 - the x-coordinate of the first vertex
     * \param y1 - the y-coordinate of the first vertex
     * \param x2 - the x-coordinate of the second vertex
     * \param y2 - the y-coordinate of the second vertex
     * \param x3 - the x-coordinate of the third vertex
     * \param y3 - the y-coordinate of the third vertex
     */
    void initialize_triangle(int x1, int y1, int x2, int y2, int x3, int y3);

    /**
     * Computes the index of the lower left vertex in the array ivertex
     * \return the index in the vertex table of the lower left vertex
     */
    int LowerLeft();

    /**
     * Computes the index of the upper left vertex in the array ivertex
     * \return the index in the vertex table of the upper left vertex
     */
    int UpperLeft();

    /**
     * Stores the three vertices of the triangle
     */
    glm::ivec2 ivertex[3];

    // Indices into the vertex table
    int lower_left;
    int upper_left;
    int the_other;

    /**
     * An edge_rasterizer which scan-converts the left edge
     */
    edge_rasterizer leftedge;

    /**
     * An edge_rasterizer which scan-converts the right edge
     */
    edge_rasterizer rightedge;

    // Screen coordinates
    int       x_start;
    int       y_start;

    int       x_stop;
    int       y_stop;

    int       x_current;
    int       y_current;

    bool valid;
};

#endif
