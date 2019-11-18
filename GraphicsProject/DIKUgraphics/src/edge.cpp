#include "edge.h"


/*
 * \class edge_rasterizer
 * A class which scanconverts an edge in a polygon. It computes the pixels which
 * are closest to the ideal edge, i.e.e either on the edge or to the right of the edge.
 */ 


/*
 * Default constructor creates an empty edge_rassterizer
 */
edge_rasterizer::edge_rasterizer() : valid(false)
{
    Trace("edge_rasterizer", "edge_rasterizer()");
}

/*
 * Destructor destroys the edge_rasterizer
 */
edge_rasterizer::~edge_rasterizer()
{
    Trace("edge_rasterizer", "~edge_rasterizer()");
}

/*
 * Initializes the edge_rasterizer with one edge
 * \param x1 - The x-coordinate of the lower edge point
 * \param y1 - The y-coorsinate of the lower edge point
 * \param x2 - The x-coordinate of the upper edge point
 * \param y2 - The y-coordinate of the upper edge point
 */
void edge_rasterizer::init(int x1, int y1, int x2, int y2)
{
    Trace("edge_rasterizer", "init(int, int, int, int)");

    std::cout << "edge_rasterizer::init(int, int, int, int): Not implemented yet!" << std::endl;
}

/*
 * Initializes the edge_rasterizer with two edges
 * \param x1 - The x-coordinate of the lower point of edge one
 * \param y1 - The y-coorsinate of the lower point of edge one
 * \param x2 - The x-coordinate of the upper point of edge one = the lower point of edge two
 * \param y2 - The y-coordinate of the upper point of edge one = the lower point of edge two
 * \param x3 - The x-coordinate of the upper point of edge two
 * \param y3 - The y-coordinate of the upper point of edge two
 */
void edge_rasterizer::init(int x1, int y1, int x2, int y2, int x3, int y3)
{
    Trace("edge_rasterizer", "init(int, int, int, int, int, int)");
    
    std::cout << "edge_rasterizer::init(int, int, int, int, int, int): Not implemented yet!" << std::endl;
}

/*
 * Checks if there are fragments/pixels on the edge ready for use
 * \return - true if there is a fragment/pixel on the edge ready for use, else it returns false
 */
bool edge_rasterizer::more_fragments() const
{
    Trace("edge_rasterizer", "more_fragments()");
    
    return this->valid;
}

/*
 * Computes the next fragment/pixel on the edge
 */
void edge_rasterizer::next_fragment()
{
    Trace("edge_rasterizer", "next_fragments()");
    
    std::cout << "edge_rasterizer::next_fragment(): Not implemented yet!" << std::endl;
}

/*
 * Returns the current x-coordinate of the current fragment/pixel on the edge
 * It is only valid to call this function if "more_fragments()" returns true,
 * else a "runtime_error" exception is thrown
 * \return - The x-coordinate of the current edge fragment/pixel
 */
int edge_rasterizer::x() const
{
    Trace("edge_rasterizer", "x()");
    
    if (!this->valid) {
        throw std::runtime_error("edge_rasterizer::x(): Invalid State");
    }
    return this->x_current;
}

/*
 * Returns the current x-coordinate of the current fragment/pixel on the edge
 * It is only valid to call this function if "more_fragments()" returns true,
 * else a "runtime_error" exception is thrown
 * \return - The y-coordinate of the current edge fragment/pixel
 */
int edge_rasterizer::y() const
{
    Trace("edge_rasterizer", "y()");
     
    if (!this->valid) {
        throw std::runtime_error("edge_rasterizer::y(): Invalid State");
    }
    return this->y_current;
}

/*
 * Initializes an edge, so it is ready to be scanconverted
 * \param x1 - The x-coordinate of the lower edge point
 * \param y1 - The y-coorsinate of the lower edge point
 * \param x2 - The x-coordinate of the upper edge point
 * \param y2 - The y-coordinate of the upper edge point
 * \return - true if slope of the edge != 0 , false if the edge is horizontal
 */
bool edge_rasterizer::init_edge(int x1, int y1, int x2, int y2)
{
    Trace("edge_rasterizer", "init_edge(int, int, int, int)");
    
    std::cout << "edge_rasterizer::init_edge(int, int, int, int): Not implemented yet!" << std::endl;
    
    return true;
}

/*
 * Computes the next fragment/pixel on the edge
 */
void edge_rasterizer::update_edge()
{
    Trace("edge_rasterizer", "update_edge()");

    std::cout << "edge_rasterizer::update_edge(): Not implemented yet!" << std::endl;
}
