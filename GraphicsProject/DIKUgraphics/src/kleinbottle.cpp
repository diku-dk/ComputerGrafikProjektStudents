#include "kleinbottle.h"


/*
 * \class KleinTop
 * implements a surface which is the top of the surface.
 */
KleinTop::KleinTop()
        : ParametricSurface(0.0f, 2.0f * glm::pi<float>(), 20, 0.0f, glm::pi<float>(), 20, true, false)
{}

/*
 * Creates an instance of the top part of the Klein Bottle with
 * the specified parameters.
 * \param M - the number of samples of the u-parameter.
 * \param N - the number of smaples of the v-parameter.
 * \param frontfacing - true if the surface is frontfacing, else false.
 * \param debug - true if debug mode should be initialized, else false.
 */
KleinTop::KleinTop(int M, int N, bool frontfacing, bool debug)
        :  ParametricSurface(0.0f, 2.0f * glm::pi<float>(), M, 0.0f, glm::pi<float>(), N, frontfacing, debug)
{}
    
/*
 * Computes a point on the surface.
 * \param u - the value of the u-parameter.
 * \param v - the value of the v-parameter.
 * \return a 3D vector containing the coordinates of the point on the surface.
 */
glm::vec3 KleinTop::Vertex(float u, float v)  const
{
    return glm::vec3(2.0f + (2.0f + glm::cos(u)) * glm::cos(v),
                     glm::sin(u),
                     3.0f * glm::pi<float>() + (2.0f + glm::cos(u)) * glm::sin(v));
}

/*
 * Computes a normal to the surface.
 * \param u - the value of the u-parameter.
 * \param v - the value of the v-parameter.
 * \return a 3D vector containing the coordinates of the normal on the surface.
 */
glm::vec3 KleinTop::Normal(float u, float v) const
{
    return glm::vec3((2.0f + glm::cos(u)) * glm::cos(u) * glm::cos(v),
                     (2.0f + glm::cos(u)) * glm::sin(u),
                     (2.0f + glm::cos(u)) * glm::cos(u) * glm::sin(v));
}


/*
 * \class KleinBottom
 * implements a surface which is the bottom of the surface.
 */

 /*
  * Creates an instance of the bottom part of the Klein Bottle with default parameters.
  * The parameters can be changed by calling member functions of the parent class ParametricSurface.
  */
KleinBottom::KleinBottom()
           : ParametricSurface(0.0f, 2.0f * glm::pi<float>(), 20, 0.0f, glm::pi<float>(), 20, true, false)
{}

/*
 * Creates an instance of the bottom part of the Klein Bottle with
 * the specified parameters.
 * \param M - the number of samples of the u-parameter.
 * \param N - the number of smaples of the v-parameter.
 * \param frontfacing - true if the surface is frontfacing, else false.
 * \param debug - true if debug mode should be initialized, else false.
 */
KleinBottom::KleinBottom(int M, int N, bool frontfacing, bool debug)
           : ParametricSurface(0.0f, 2.0f * glm::pi<float>(), M, 0.0f, glm::pi<float>(), N, frontfacing, debug)
{}

/*
 * Computes a point on the surface.
 * \param u - the value of the u-parameter.
 * \param v - the value of the v-parameter.
 * \return a 3D vector containing the coordinates of the point on the surface.
 */
glm::vec3 KleinBottom::Vertex(float u, float v)  const
{
    return glm::vec3((2.5f + 1.5f * glm::cos(v)) * glm::cos(u),
             (2.5f + 1.5f * glm::cos(v)) * glm::sin(u),
             -2.5f * glm::sin(v));
}

/*
 * Computes a normal to the surface.
 * \param u - the value of the u-parameter.
 * \param v - the value of the v-parameter.
 * \return a 3D vector containing the coordinates of the normal on the surface.
 */
glm::vec3 KleinBottom::Normal(float u, float v) const
{
    return glm::vec3((-6.25f - 3.75f * glm::cos(v)) * glm::cos(v) * glm::cos(u),
                     (-6.25f - 3.75f * glm::cos(v)) * glm::cos(v) * glm::sin(u),
                     ( 3.75f + 2.25f * glm::cos(v)) * glm::sin(v));
}


/*
 * \class KleinHandle
 * implements a surface which is a handle of the surface
 */

/*
 * Creates an instance of the handle part of the Klein Bottle with default parameters.
 * The parameters can be changed by calling member functions of the parent class ParametricSurface.
 */
KleinHandle::KleinHandle()
           : ParametricSurface(0.0f, 2.0f * glm::pi<float>(), 20, 0.0f, glm::pi<float>(), 20, true, false)
{}

/*
 * Creates an instance of the handle part of the Klein Bottle with
 * the specified parameters.
 * \param M - the number of samples of the u-parameter.
 * \param N - the number of smaples of the v-parameter.
 * \param frontfacing - true if the surface is frontfacing, else false.
 * \param debug - true if debug mode should be initialized, else false.
 */
KleinHandle::KleinHandle(int M, int N, bool frontfacing, bool debug)
           : ParametricSurface(0.0f, 2.0f * glm::pi<float>(), M, 0.0f, glm::pi<float>(), N, frontfacing, debug)
{}

/*
 * Computes a point on the surface.
 * \param u - the value of the u-parameter.
 * \param v - the value of the v-parameter.
 * \return a 3D vector containing the coordinates of the point on the surface.
 */
glm::vec3 KleinHandle::Vertex(float u, float v)  const
{
    return glm::vec3(2.0f - 2.0f * glm::cos(v) + glm::sin(u),
                     glm::cos(u),
                     3.0f * v);
}

/*
 * Computes a normal to the surface.
 * \param u - the value of the u-parameter.
 * \param v - the value of the v-parameter.
 * \return a 3D vector containing the coordinates of the normal on the surface.
 */
glm::vec3 KleinHandle::Normal(float u, float v) const
{
    return glm::vec3(-3.0f * glm::sin(u),
                     -3.0f * glm::cos(u),
                     2.0f * glm::sin(u) * glm::sin(v));
}

/*
 * \class KleinMiddle
 * implements a surface which is the middle part of the surface.
 */

/*
 * Creates an instance of the middle part of the Klein Bottle with default parameters.
 * The parameters can be changed by calling member functions of the parent class ParametricSurface.
 */
KleinMiddle::KleinMiddle()
           : ParametricSurface(0.0f, 2.0f * glm::pi<float>(), 20, 0.0f, glm::pi<float>(), 20, true, false)
{}

/*
 * Creates an instance of the handle part of the Klein Bottle with
 * the specified parameters.
 * \param M - the number of samples of the u-parameter.
 * \param N - the number of smaples of the v-parameter.
 * \param frontfacing - true if the surface is frontfacing, else false.
 * \param debug - true if debug mode should be initialized, else false.
 */
KleinMiddle::KleinMiddle(int M, int N, bool frontfacing, bool debug)
           : ParametricSurface(0.0f, 2.0f * glm::pi<float>(), M, 0.0f, glm::pi<float>(), N, frontfacing, debug)
{}

/*
 * Computes a point on the surface.
 * \param u - the value of the u-parameter.
 * \param v - the value of the v-parameter.
 * \return a 3D vector containing the coordinates of the point on the surface.
 */
glm::vec3 KleinMiddle::Vertex(float u, float v)  const
{
    return glm::vec3((2.5f + 1.5f * glm::cos(v)) * glm::cos(u),
                     (2.5f + 1.5f * glm::cos(v)) * glm::sin(u),
                     3.0f * v);
}

/*
 * Computes a normal to the surface.
 * \param u - the value of the u-parameter.
 * \param v - the value of the v-parameter.
 * \return a 3D vector containing the coordinates of the normal on the surface.
 */
glm::vec3 KleinMiddle::Normal(float u, float v) const
{
    return glm::vec3((7.5f + 4.5f * glm::cos(v)) * glm::cos(u),
                     (7.5f + 4.5f * glm::cos(v)) * glm::sin(u),
                     (3.75f + 2.25f * glm::cos(v)) * glm::sin(v));
}

/*
 * \class KleinBottle
 * Implements a Klein Bottle, i.e. a surface with only one side.
 * It is composed by four simple surfaces which are implemented by the
 * classes KleinTop, KleinBottom, KleinHandle, and KleinMiddle.
 */

/*
 * Creates an instance of a Klein Bottle with default parameters.
 */
KleinBottle::KleinBottle()
           : M(20), N(20), validVertices(false), validNormals(false),
             kleintop(new KleinTop()), kleinbottom(new KleinBottom()),
             kleinhandle(new KleinHandle()), kleinmiddle(new KleinMiddle())
{
    Trace("KleinBottle", "KleniBottle()");
}

/*
 * Parametrized constructor, creates an instance of the bottom part of a Klein Bottle.
 * \param M - the number of samples of the u-parameter.
 * \param N - the number of smaples of the v-parameter.
 * \param frontfacing - true if the surface is frontfacing, else false.
 * \param debug - true if debug mode should be initialized, else false.
 */
KleinBottle::KleinBottle(int M, int N, bool frontfacing, bool debug)
           : M(M), N(N), validVertices(false), validNormals(false),
             kleintop(new KleinTop(M, N, frontfacing, debug)),
             kleinbottom(new KleinBottom(M, N, frontfacing, debug)),
             kleinhandle(new KleinHandle(M, N, frontfacing, debug)),
             kleinmiddle(new KleinMiddle(M, N, frontfacing, debug))
{
    Trace("KleinBottle", "KleinBottle(int, int, bool, bool)");

    this->kleinbottom->FrontFacing(false);
}

/*
 * Copy constructor, copies the parameter to this instance.
 * \param Src - the instance to be copied.
 */
KleinBottle::KleinBottle(KleinBottle const& Src)
           : M(Src.M), N(Src.N), validVertices(Src.validVertices), validNormals(Src.validNormals),
             kleintop(Src.kleintop), kleinbottom(Src.kleinbottom), kleinhandle(Src.kleinhandle), kleinmiddle(Src.kleinmiddle),
             vertices(Src.vertices), normals(Src.normals)
{
    Trace("KleinBottle", "KleinBottle(KleinBottle const&)");
}

/*
 * Destructor, destroys the current instance of a Klein Bottle.
 */
KleinBottle::~KleinBottle()
{
    Trace("KleinBottle", "~KleinBottle()");

    delete kleintop;
    delete kleinbottom;
    delete kleinhandle;
    delete kleinmiddle;
}

/*
 * Assignment operator, assigns the parameter to this instance.
 * \param Src - the instance which should be assigned to this instance.
 * \return the current instance of the KleinBottom.
 */
KleinBottle& KleinBottle::operator=(KleinBottle const& Src)
{
    Trace("KleinBottle", "operator=(KleinBottle const&)");

    if (this != &Src) {
        this->M = Src.M;
        this->N = Src.N;
        this->validVertices = Src.validVertices;
        this->validNormals  = Src.validNormals;
        this->kleintop      = Src.kleintop;
        this->kleinbottom   = Src.kleinbottom;
        this->kleinhandle   = Src.kleinhandle;
        this->kleinmiddle   = Src.kleinmiddle;
        this->vertices           = Src.vertices;
        this->normals            = Src.normals;
    }
    return *this;
}

/*
 * The samples of the u-parameter.
 * \return the number of samples of the u-parameter.
 */
int KleinBottle::Usamples() const
{
    Trace("KleinBottle", "Usamples()");

    return this->M;
}

/*
 * Changes the number of samples of the u-parameter.
 * \param M - the new number of samples of the u-parameter.
 */
void KleinBottle::Usamples(int M)
{
    Trace("KleinBottle", "Usamples(int)");

    this->kleintop->ParametricSurface::Usamples(M);
    this->kleinbottom->ParametricSurface::Usamples(M);
    this->kleinhandle->ParametricSurface::Usamples(M);
    this->kleinmiddle->ParametricSurface::Usamples(M);
    
    this->validVertices = false;
    this->validNormals  = false;
}

/*
 * The samples of the v-parameter.
 * \return the number of samples of the v-parameter.
 */
int KleinBottle::Vsamples() const
{
    Trace("KleinBottle", "Usamples()");

    return this->N;
}

/*
 * Changes the number of samples of the v-parameter.
 * \param N - the new number of samples of the v-parameter.
 */
void KleinBottle::Vsamples(int N)
{
    Trace("KleinBottle", "Vsamples(int)");

    this->kleintop->ParametricSurface::Vsamples(N);
    this->kleinbottom->ParametricSurface::Usamples(N);
    this->kleinhandle->ParametricSurface::Usamples(N);
    this->kleinmiddle->ParametricSurface::Usamples(N);
    
    this->validVertices = false;
    this->validNormals  = false;
}

/*
 * The coordinates of vertices which define the triangles in the mesh.
 * It returns an array containing the coordinates of the triangle vertices in the mesh with the following
 * interpretation: the first 3 entries define the first triangle, the next 3 entries define the second
 * triangle etc.
 * \return An array containing the vertices of the faces in the mesh.
 */
std::vector<glm::vec3> const& KleinBottle::Vertices()
{
    Trace("KleinBottle", "Vertices()");

    if (!this->validVertices) {
        this->vertices.insert(vertices.end(), this->kleintop->Vertices().begin(),    this->kleintop->Vertices().end());
        this->vertices.insert(vertices.end(), this->kleinbottom->Vertices().begin(), this->kleinbottom->Vertices().end());
        this->vertices.insert(vertices.end(), this->kleinhandle->Vertices().begin(), this->kleinhandle->Vertices().end());
        this->vertices.insert(vertices.end(), this->kleinmiddle->Vertices().begin(), this->kleinmiddle->Vertices().end());
    }
    return vertices;
}

/*
 * The normals of vertices which define the triangles in the mesh.
 * It returns an array containing the normals of the vertices in the mesh with the following
 * interpretation: the first 3 entries define the normals of the vertices of the first triangle, 
 * the next 3 entries define the normals of the vertices of the second triangle etc.
 * \return An array containing the normals of the vertices.
 */
std::vector<glm::vec3> const& KleinBottle::Normals()
{
    Trace("KleinBottle", "Normals()");

    if (!this->validNormals) {
        this->normals.insert(this->normals.end(),  this->kleintop->Normals().begin(),    this->kleintop->Normals().end());
        this->vertices.insert(this->normals.end(), this->kleinbottom->Normals().begin(), this->kleinbottom->Normals().end());
        this->vertices.insert(this->normals.end(), this->kleinhandle->Normals().begin(), this->kleinhandle->Normals().end());
        this->vertices.insert(this->normals.end(), this->kleinmiddle->Normals().begin(), this->kleinmiddle->Normals().end());
    }
    return normals;
}

