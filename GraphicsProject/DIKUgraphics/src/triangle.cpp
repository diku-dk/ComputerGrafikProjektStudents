#include "triangle.h"

/*
 * \class triangle_rasterizer
 * A class which scanconverts a triangle. It computes the pixels such that they are inside the triangle.
 */ 
triangle_rasterizer::triangle_rasterizer(int x1, int y1, int x2, int y2, int x3, int y3) : valid(false)
{
    this->initialize_triangle(x1, y1, x2, y2, x3, y3);
}

/*
 * Destroys the current instance of the triangle rasterizer
 */
triangle_rasterizer::~triangle_rasterizer()
{}

/*
 * Returns a vector which contains alle the pixels inside the triangle
 */
std::vector<glm::vec3> triangle_rasterizer::all_pixels()
{
    std::vector<glm::vec3> points;

    std::cout << "triangle_rasterizer::all_pixels(): Not implemented yet!" << std::endl;
    
    return points;
}

/*
 * Checks if there are fragments/pixels inside the triangle ready for use
 * \return true if there are more fragments in the triangle, else false is returned
 */
bool triangle_rasterizer::more_fragments() const
{
    return this->valid;
}

/*
 * Computes the next fragment inside the triangle
 */
void triangle_rasterizer::next_fragment()
{
    std::cout << "triangle_rasterizer::next_fragment(): Not implemented yet!" << std::endl;
}

/*
 * Returns the current x-coordinate of the current fragment/pixel inside the triangle
 * It is only valid to call this function if "more_fragments()" returns true,
 * else a "runtime_error" exception is thrown
 * \return The x-coordinate of the current triangle fragment/pixel
 */
int triangle_rasterizer::x() const
{
    if (!this->valid) {
        throw std::runtime_error("triangle_rasterizer::x(): Invalid State/Not Initialized");
    }
    return this->x_current;
}

/*
 * Returns the current y-coordinate of the current fragment/pixel inside the triangle
 * It is only valid to call this function if "more_fragments()" returns true,
 * else a "runtime_error" exception is thrown
 * \return The y-coordinate of the current triangle fragment/pixel
 */
int triangle_rasterizer::y() const
{
    if (!this->valid) {
        throw std::runtime_error("triangle_rasterizer::y(): Invalid State/Not Initialized");
    }
    return this->y_current;
}

/*
 * Initializes the TriangleRasterizer with the three vertices
 * \param x1 - the x-coordinate of the first vertex
 * \param y1 - the y-coordinate of the first vertex
 * \param x2 - the x-coordinate of the second vertex
 * \param y2 - the y-coordinate of the second vertex
 * \param x3 - the x-coordinate of the third vertex
 * \param y3 - the y-coordinate of the third vertex
 */
void triangle_rasterizer::initialize_triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    std::cout << "triangle_rasterizer::initialize_triangle(int, int, int, int, int, int): Not implemented yet!" << std::endl;
}

/*
 * Computes the index of the lower left vertex in the array ivertex
 * \return the index in the vertex table of the lower left vertex
 */
int triangle_rasterizer::LowerLeft()
{
    int ll = 0;

    std::cout << "triangle_rasterizer::LowerLeft(): Not implemented yet!" << std::endl;
    
    return ll;
}

/*
 * Computes the index of the upper left vertex in the array ivertex
 * \return the index in the vertex table of the upper left vertex
 */
int triangle_rasterizer::UpperLeft()
{
    int ul = 0;

     std::cout << "triangle_rasterizer::UpperLeft(): Not implemented yet!" << std::endl;
    
    return ul;
}
