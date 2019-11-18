#ifndef __LINE_RASTERIZER_H__
#define __LINE_RASTERIZER_H__

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>

#include "traceinfo.h"
#include "glmutils.h"


/**
 * \class LineRasterizer
 * A class which scanconverts a straight line. It computes the pixels such that they are as close to the
 * the ideal line as possible.
 */ 
class LineRasterizer {
public:
    /**
     * Parameterized constructor creates an instance of a line rasterizer
     * \param x1 - the x-coordinate of the first vertex
     * \param y1 - the y-coordinate of the first vertex
     * \param x2 - the x-coordinate of the second vertex
     * \param y2 - the y-coordinate of the second vertex
     */
    LineRasterizer(int x1, int y1, int x2, int y2);

    /**
     * Destroys the current instance of the line rasterizer
     */
    virtual ~LineRasterizer();

    /**
     * Initializes the LineRasterizer with a new line
     * \param x1 - The x-coordinate of the first line end point
     * \param y1 - The y-coorsinate of the first line end point
     * \param x2 - The x-coordinate of the second line end point
     * \param y2 - The y-coordinate of the second line end point
     */
    void Init(int x1, int y1, int x2, int y2);

    /**
     * Checks if there are fragments/pixels of the line ready for use
     * \return true if there are more fragments of the line, else false is returned
     */
    bool MoreFragments() const;

    /**
     * Computes the next fragment of the line
     */
    void NextFragment();

    /**
     * Returns a vector which contains all the pixels of the line
     */
    std::vector<glm::vec3> AllFragments();

    /**
     * Returns the coordinates of the current fragment/pixel of the line.
     * It is only valid to call this function if "MoreFragments()" returns true,
     * else a "runtime_error" exception is thrown
     * \return The coordinates of the current line fragment/pixel
     */
    glm::vec3 Fragment() const;

    /**
     * Returns the current x-coordinate of the current fragment/pixel of the line
     * It is only valid to call this function if "more_fragments()" returns true,
     * else a "runtime_error" exception is thrown
     * \return The x-coordinate of the current line fragment/pixel
     */
    int x() const;

    /**
     * Returns the current y-coordinate of the current fragment/pixel of the line
     * It is only valid to call this function if "more_fragments()" returns true,
     * else a "runtime_error" exception is thrown
     * \return The y-coordinate of the current line fragment/pixel
     */
    int y() const;

private:
    /**
     * Initializes the LineRasterizer with the two vertices
     */
    void initialize_line(int x1, int y1, int x2, int y2);

    /**
     * Runs the x-dominant innerloop
     */
    void x_dominant_innerloop();

    /**
     * Runs the y-dominant innerloop
     */
    void y_dominant_innerloop();

    /**
     * Private Variables
     */

    /**
     * Screen coordinates
     */
    int  x_start;
    int  y_start;

    int  x_stop;
    int  y_stop;

    int  x_current;
    int  y_current;

    /**
     * dx = x_stop - x_start, and dy = y_stop - y_start
     */
    int  dx;
    int  dy;

    /**
     * Convenience variables. Their values are 2 * |dx| and 2 * |dy|
     */
    int  abs_2dx;
    int  abs_2dy;

    /**
     * The decision variable. Its value determines if one should step East or North-East, etc.
     */
    int  d;

    /**
     * One can step both positive or negative, i.e. left-right or right-left
     */
    int  x_step;
    int  y_step;

    /**
     * True if the straight line is scan-converted from left to right, false otherwize
     */
    bool left_right;

    bool valid;

    /**
     * A pointer to a member function which runs the inner loop of the algorithm
     * Its values can be either "x_dominant_innerloop" or "y_dominant_innerloop"
     */
    void (LineRasterizer::*innerloop)();
};

#endif
