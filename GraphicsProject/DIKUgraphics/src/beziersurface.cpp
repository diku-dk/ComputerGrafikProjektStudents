#include "beziersurface.h"

// public member functions

/*
 * Default constructor. Creates a BezierSurface which is empty.
 */
BezierSurface::BezierSurface() : frontfacing(true), nsubdivisions(3), VerticesOK(false), NormalsOK(false)
{}

/*
 * Parameterized constructor. Creates a BezierSurface from a file.
 * \param Filename - the name of the file containing the bezier patches.
 */
BezierSurface::BezierSurface(std::string Filename) : frontfacing(true), nsubdivisions(3),
                             VerticesOK(false), NormalsOK(false)
{
    this->Read(Filename);
}

/*
 * Parameterized constructor. Creates a BezierSurface from its parameters.
 * \param patches - the bezier patches which makes up the surface.
 */
BezierSurface::BezierSurface(std::vector<BezierPatch> const& bezierpatches)
             : frontfacing(true), nsubdivisions(3), VerticesOK(false), NormalsOK(false)
{
    this->BezierPatches = bezierpatches;
}

/*
 * Copy constructor, creates a new instance of its parameter.
 * \param Src - a BezierSurface
 */
BezierSurface::BezierSurface(BezierSurface const& Src)
{
    this->frontfacing   = Src.frontfacing;
    this->nsubdivisions = Src.nsubdivisions;
    this->VerticesOK    = Src.VerticesOK;
    this->NormalsOK     = Src.NormalsOK;
    this->BezierPatches = Src.BezierPatches;
    this->vertices      = Src.vertices;
    this->normals       = Src.normals;
}

/*
 * Destructor destroys the current instance of a BezierSurface.
 */
BezierSurface::~BezierSurface()
{}

/*
 * Assignment operator, assigns its parameter to the current instance.
 * \param Src - the BezierSurface that should be assigned to the current instance.
 * \return the current instance of the BezierSurface.
 */
BezierSurface& BezierSurface::operator=(BezierSurface const& Src)
{
    if (this != &Src) {
        this->frontfacing   = Src.frontfacing;
        this->nsubdivisions = Src.nsubdivisions;
        this->VerticesOK    = Src.VerticesOK;
        this->NormalsOK     = Src.NormalsOK;
        this->BezierPatches = Src.BezierPatches;
        this->vertices      = Src.vertices;
        this->normals       = Src.normals;
    }
    return *this;
}

/*
 * Specifies if the surface is front facing or back facing.
 * \return true if the surface is front facing, false if it is back facing.
 */
bool BezierSurface::FrontFacing() const
{
    return this->frontfacing;
}
    
/*
 * Specifies if the surface is front facing or back facing.
 * \param frontfacing - true if the surface is front facing.
 */
void BezierSurface::FrontFacing(bool frontfacing)
{
    this->frontfacing = frontfacing;
}

/*
 * The current number of subdivisions.
 * \return the current number of subdivisions.
 */
int BezierSurface::NumberOfSubdivisions() const
{
    return this->nsubdivisions;
}

/*
 * Specify how many times the BezierSurface should be subdivided.
 * \param subdivisionlevel - the number of subdivisions that should be done.
 * \return the previous number of the subdivision level.
 */
int BezierSurface::NumberOfSubdivisions(int Nsubdivisions)
{
    int OldNumberOfSubdivisions = this->nsubdivisions;
    this->nsubdivisions         = Nsubdivisions;
    this->VerticesOK            = false;
    this->NormalsOK             = false;
    return OldNumberOfSubdivisions;
}

/*
 * Computes the vertices of the BezierSurface.
 * \return a vector containing the vertices of the triangles that approximate the BezierSurface.
 */
std::vector<glm::vec3> const& BezierSurface::Vertices()
{
    if (!this->VerticesOK) {
        this->vertices.clear();
        this->normals.clear();

        for (int patch = 0; patch < this->BezierPatches.size(); ++patch) {
            this->subdivide_bezierpatch(this->BezierPatches[patch], this->nsubdivisions);
        }
        this->VerticesOK = true;
        this->NormalsOK  = true;
    }
    return this->vertices;
}

/*
 * Computes the normals of the BezierSurface.
 * \return a vector containing the normals of the vertices of the triangles 
 * that approximate the BezierSurface.
 */
std::vector<glm::vec3> const& BezierSurface::Normals()
{
    if (!this->NormalsOK) {
        this->Vertices();
    }
    return this->normals;
}


// protected member functions

// private member functions

/*
 * Read the patches from a file
 * \param FileNae - the name of the file containing the bezier patches.
 */
void BezierSurface::Read(std::string const& FileName)
{
    // States
    int const NVERTEX        = 0;
    int const READ_VERTICES  = 1;
    int const PATCHNAME      = 2;
    int const SEARCH_PATCHES = 3;
    int const READ_PATCHES   = 4;

    char   ch;
    int    const MAX_BUFFER = 256;
    char   InputBuffer[MAX_BUFFER];
    
    int    NumberOfVertices;
    int    VertexNumber;
    float  x;
    float  y;
    float  z;

    float xmin =  1000.0f;
    float xmax = -1000.0f;
    float ymin =  1000.0f;
    float ymax = -1000.0f;
    float zmin =  1000.0f;
    float zmax = -1000.0f;

    char   PatchName[MAX_BUFFER];
    int    PatchNumber;
    int    index_11, index_12, index_13, index_14;
    int    index_21, index_22, index_23, index_24;
    int    index_31, index_32, index_33, index_34;
    int    index_41, index_42, index_43, index_44;

    // The vertex list
    std::vector<glm::vec3> Vertices;


    std::ifstream data_file(FileName);
    if (!data_file) {
        throw std::runtime_error("Error on opening file");
    }
    
    int currentState = NVERTEX;
    while (data_file.get(InputBuffer, MAX_BUFFER, '\n')) {
        if (data_file.get(ch) && ch != '\n') {
            data_file.close();
            throw std::runtime_error("Eof on data file");
        }

        // Now one line of data is in InputBuffer
        // Use sscanf to extract the numeric values
        //
        // Build a data structure which represents the different
        // vertices and patches
        //
        // There are several possibilities for the input lines:
        //
        // 1: a comment line, i.e. InputBuffer[0] == '#'
        // 2: a 'number of vertices line', i.e. just one number
        //    sscanf(InputBuffer, "%d", &NumberOfVertices)
        // 3: a 'vertex line', i.e. 4 numbers
        //    sscanf(InputBuffer, "%d%f%f%f", &VertexNumber, &x, &y, &z)
        // 4: a 'patch line', i.e. 17 numbers
        //    sscanf(InputBuffer,
        //           "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%s",
        //           &PatchNumber,
        //           &index_11, &index_12, &index_13, &index_14,
        //           &index_21, &index_22, &index_23, &index_24,
        //           &index_31, &index_32, &index_33, &index_34,
        //           &index_41, &index_42, &index_43, &index_44, &facing)
    
        switch (currentState) {
            case NVERTEX: {
                if (InputBuffer[0] != '#') {
                    if (sscanf(InputBuffer, "%d", &NumberOfVertices) != 1) {
                        throw std::runtime_error("Wrong number of vertices in file");
                    }
                    currentState = READ_VERTICES;
                }
                break;
            }
            case READ_VERTICES: {
                if (InputBuffer[0] != '#') {
                    if (sscanf(InputBuffer, "%d%f%f%f",
                               &VertexNumber, &x, &y, &z) != 4) {
                        throw std::runtime_error("vertex not found in data file");
                    }
                    else {
                        xmin = std::min(xmin, x);
                        xmax = std::max(xmax, x);
                        ymin = std::min(ymin, y);
                        ymax = std::max(ymax, y);
                        zmin = std::min(zmin, z);
                        zmax = std::max(zmax, z);
            
                        // insert the vertex in a data structure
                        glm::vec3 Vertex(x, y, z);
                        Vertices.push_back(Vertex);

                        if (VertexNumber == NumberOfVertices) {
                            currentState = PATCHNAME;
                        }
                    }
                }
                break;
            }
            case PATCHNAME: {
                if (InputBuffer[0] == '#') {
                    if (strlen(InputBuffer) > 2) {
                        // read the name of the patch
            
                        if (sscanf(InputBuffer, "# %s", PatchName) != 1) {
                            throw std::runtime_error("patch name not found in data file");
                        }
                        currentState = SEARCH_PATCHES;
                    }
                }
                break;
            }
            case SEARCH_PATCHES:
            case READ_PATCHES: {
                if (InputBuffer[0] == '#') {
                    if (currentState == READ_PATCHES) {
                        currentState = PATCHNAME;
                    }
                }
                else {
                    currentState = READ_PATCHES;

                    if (sscanf(InputBuffer, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
                               &PatchNumber,
                               &index_11, &index_12, &index_13, &index_14,
                               &index_21, &index_22, &index_23, &index_24,
                               &index_31, &index_32, &index_33, &index_34,
                               &index_41, &index_42, &index_43, &index_44) != 17) {
                        throw std::runtime_error("No patch found in data file");
                    }
                    else {
                        // insert patch in a data structure
                        BezierPatch BPatch;

                        // First row
                        BPatch[1][1] = Vertices[index_11 - 1];
                        BPatch[1][2] = Vertices[index_12 - 1];
                        BPatch[1][3] = Vertices[index_13 - 1];
                        BPatch[1][4] = Vertices[index_14 - 1];

                        // Second row
                        BPatch[2][1] = Vertices[index_21 - 1];
                        BPatch[2][2] = Vertices[index_22 - 1];
                        BPatch[2][3] = Vertices[index_23 - 1];
                        BPatch[2][4] = Vertices[index_24 - 1];
            
                        // Third row
                        BPatch[3][1] = Vertices[index_31 - 1];
                        BPatch[3][2] = Vertices[index_32 - 1];
                        BPatch[3][3] = Vertices[index_33 - 1];
                        BPatch[3][4] = Vertices[index_34 - 1];
            
                        // Forth row
                        BPatch[4][1] = Vertices[index_41 - 1];
                        BPatch[4][2] = Vertices[index_42 - 1];
                        BPatch[4][3] = Vertices[index_43 - 1];
                        BPatch[4][4] = Vertices[index_44 - 1];
            
                        this->BezierPatches.push_back(BPatch);
                    }
                }
                break;
            }
            default: {
                break;
            }
        }
    }
    if (!data_file.eof()) {
        throw std::runtime_error("Something strange happend on data file");
    }
    data_file.close();
}

/*
 * Prints the indices of the entries of the BezierPatch.
 * \param index_11 - the number of the vertex 11.
 * \param index_12 - the number of the vertex 12.
 * \param index_13 - the number of the vertex 13.
 * \param index_14 - the number of the vertex 14.
 * \param index_21 - the number of the vertex 21.
 * \param index_22 - the number of the vertex 22.
 * \param index_23 - the number of the vertex 23.
 * \param index_24 - the number of the vertex 24.
 * \param index_31 - the number of the vertex 31.
 * \param index_32 - the number of the vertex 32.
 * \param index_33 - the number of the vertex 33.
 * \param index_34 - the number of the vertex 34.
 * \param index_41 - the number of the vertex 41.
 * \param index_42 - the number of the vertex 42.
 * \param index_43 - the number of the vertex 43.
 * \param index_44 - the number of the vertex 44.
 */
void BezierSurface::PrintIndexMatrix(int PatchNumber,
                                     int index_11, int index_12, int index_13, int index_14,
                                     int index_21, int index_22, int index_23, int index_24,
                                     int index_31, int index_32, int index_33, int index_34,
                                     int index_41, int index_42, int index_43, int index_44) const
{
    std::cout << "patch number: " 
              << std::setw(2) << PatchNumber << std::endl << std::flush;

    std::cout << "patch indices: " << std::endl << '\t'
              << std::setw(6) << index_11 << ", " 
              << std::setw(6) << index_12 << ", " 
              << std::setw(6) << index_13 << ", " 
              << std::setw(6) << index_14 << std::endl;
            
    std::cout << '\t'
              << std::setw(6) << index_21 << ", " 
              << std::setw(6) << index_22 << ", "
              << std::setw(6) << index_23 << ", " 
              << std::setw(6) << index_24 << std::endl;
            
    std::cout << '\t'
              << std::setw(6) << index_31 << ", " 
              << std::setw(6) << index_32 << ", "
              << std::setw(6) << index_33 << ", " 
              << std::setw(6) << index_34 << std::endl;
            
    std::cout << '\t'
              << std::setw(6) << index_41 << ", " 
              << std::setw(6) << index_42 << ", "
              << std::setw(6) << index_43 << ", " 
              << std::setw(6) << index_44 << std::endl;
}

/*
 * subdivides a BezierPatch
 * \param patch - the bezierpatch which should be subdivided.
 * \param level - the number of times the patch should be subdivided.
 */
void BezierSurface::subdivide_bezierpatch(BezierPatch const& G, int level)
{
    std::cout << "BezierSurface::subdivide_bezierpatch(BezierPatch&, int): Not implemented yet!" << std::endl;
}

/*
 * Initialization of static members
 */

/*
 * Initialization of the static private member M
 */
glm::mat4x4 BezierSurface::M = glm::mat4x4(glm::vec4(-1.0f,  3.0f, -3.0f, 1.0f),
                                           glm::vec4( 3.0f, -6.0f,  3.0f, 0.0f),
                                           glm::vec4(-3.0f,  3.0f,  0.0f, 0.0f),
                                           glm::vec4( 1.0f,  0.0f,  0.0f, 0.0f));

/*
 * Initialization of the static private member DLB
 */
glm::mat4x4 BezierSurface::DBL = glm::mat4x4(glm::vec4(8.0f, 0.0f, 0.0f, 0.0f),
                                             glm::vec4(4.0f, 4.0f, 0.0f, 0.0f),
                                             glm::vec4(2.0f, 4.0f, 2.0f, 0.0f),
                                             glm::vec4(1.0f, 3.0f, 3.0f, 1.0f)) / 8.0f;

/*
 * Initialization of the static private member DRB
 */
glm::mat4x4 BezierSurface::DBR = glm::mat4x4(glm::vec4(1.0f, 3.0f, 3.0f, 1.0f),
                                             glm::vec4(0.0f, 2.0f, 4.0f, 2.0f),
                                             glm::vec4(0.0f, 0.0f, 4.0f, 4.0f),
                                             glm::vec4(0.0f, 0.0f, 0.0f, 8.0f)) / 8.0f;

