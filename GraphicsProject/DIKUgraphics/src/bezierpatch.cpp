#include "bezierpatch.h"

/*
 * \class BezierRow 
 * implements the concept of a row of a geometry matrix for a parametric surface where
 * each coordinate function is a polynomial of degree 3.
 */

/*
 * Default constructor creates an empty BezierRow, i.e. all entries are the zero vector.
 */
BezierRow::BezierRow()
{
    Trace("BezierRow", "BezierRow()");

    glm::vec3 zeroes(0.0f);
    for (int i = 0; i < 4; ++i) this->controlpoints[i] = zeroes;
}

/*
 * Parameterized constructor creates a BezierRow containing the arguments as entries.
 * \param G1 - Entry one in the geometry row vector.
 * \param G2 - Entry two in the geometry row vector.
 * \param G3 - Entry three in the geometry row vector.
 * \param G4 - Entry four in the geometry row vector.
 */
BezierRow::BezierRow(glm::vec3 const& G1, glm::vec3 const& G2, glm::vec3 const& G3, glm::vec3 const& G4)
{
    Trace("BezierRow", "BezierRow(4 x glm::vec3)");

    this->controlpoints[0] = G1;
    this->controlpoints[1] = G2;
    this->controlpoints[2] = G3;
    this->controlpoints[3] = G4;
}

/*
 * Copy constructor creates a new BezierRow which is a copy of its argument.
 * \param bezierrow - The geometry row vector to be copied.
 */
BezierRow::BezierRow(BezierRow const& bezierrow)
{
    for (int i = 0; i < 4; ++i) this->controlpoints[i] = bezierrow.controlpoints[i];
}

/*
 * Destructor destroys the current instance of BezierRow.
 */
BezierRow::~BezierRow()
{}

/*
 * Assignent operator assigns its argument to the current instance of BezierRow.
 * \param bezierrow - The geometry row vector to be assigned to this instance.
 */
BezierRow& BezierRow::operator=(BezierRow const& bezierrow)
{
    if (this != &bezierrow) {
        for (int i = 0; i < 4; ++i) this->controlpoints[i] = bezierrow.controlpoints[i];
    }
    return *this;
}

/*
 * Index operator - read only - returns the i'th entry in the geometry row vector,
 * \param i - The index of the entry to be returned.
 */
glm::vec3 const& BezierRow::operator[](int i) const
{
    if ((i < 1) || (i > 4)) {
        std::stringstream errormessage;
        errormessage << "BezierRow::operator[](int): The index is = " << i << " must be in the range {1,...,4}";
        throw std::out_of_range(errormessage.str().c_str());
    }
    return this->controlpoints[i - 1];
}

/*
 * Index operator returns a reference to the i'th entry in the geometry row vector.
 * \param i - The index of the entry to which a reference is to be returned;
 */
glm::vec3& BezierRow::operator[](int i)
{
    if ((i < 1) || (i > 4)) {
        std::stringstream errormessage;
        errormessage << "BezierRow::operator[](int): The index is = " << i << " must be in the range {1,...,4}";
        throw std::out_of_range(errormessage.str().c_str());
    }
    return this->controlpoints[i - 1];
}


/*
 * \class BezierColumn
 * implements the concept of a column of a geometry matrix for a parametric surface where
 * each coordinate function is a polynomial of degree 3.
 */

/*
 * Default constructor creates an empty BezierColumn, i.e. all entries are the zero vector.
 */
BezierColumn::BezierColumn()
{
    glm::vec3 zeroes(0.0f);
    for (int i = 0; i < 4; ++i) this->controlpoints[i] = zeroes;
}

/*
 * Parameterized constructor creates a BezierColumn containing the arguments as entries.
 * \param G1 - Entry one in the geometry column vector.
 * \param G2 - Entry two in the geometry column vector.
 * \param G3 - Entry three in the geometry column vector.
 * \param G4 - Entry four in the geometry column vector.
 */
BezierColumn::BezierColumn(glm::vec3 const& G1, glm::vec3 const& G2, glm::vec3 const& G3, glm::vec3 const& G4)
{
    this->controlpoints[0] = G1;
    this->controlpoints[1] = G2;
    this->controlpoints[2] = G3;
    this->controlpoints[3] = G4;   
}

/*
 * Copy constructor creates a new BezierColumn which is a copy of its argument.
 * \param beziercolumn - The geometry column vector to be copied.
 */
BezierColumn::BezierColumn(BezierColumn const& beziercolumn)
{
    for (int i = 0; i < 4; ++i) this->controlpoints[i] = beziercolumn.controlpoints[i];
}

/*
 * Destructor destroys the current instance of BezierColumn.
 */
BezierColumn::~BezierColumn()
{}

/*
 * Assignent operator assigns its argument to the current instance of BezierColumn.
 * \param beziercolumn - The geometry column vector to be assigned to this instance.
 */
BezierColumn& BezierColumn::operator=(BezierColumn const& beziercolumn)
{
    if (this != &beziercolumn) {
        for (int i = 0; i < 4; ++i) this->controlpoints[i] = beziercolumn.controlpoints[i];
    }
    return *this;
}

/*
 * Index operator - read only - returns the i'th entry in the geometry column vector,
 * \param i - The index of the entry to be returned.
 */
glm::vec3 const& BezierColumn::operator[](int i) const
{
    if ((i < 1) || (i > 4)) {
        std::stringstream errormessage;
        errormessage << "BezierColumn::operator[](int): The index is = " << i << " must be in the range {1,...,4}";
        throw std::out_of_range(errormessage.str().c_str());
    }
    return this->controlpoints[i - 1];
}

/*
 * Index operator returns a reference to the i'th entry in the geometry column vector.
 * \param i - The index of the entry to which a reference is to be returned;
 */
glm::vec3& BezierColumn::operator[](int i)
{
    if ((i < 1) || (i > 4)) {
        std::stringstream errormessage;
        errormessage << "BezierColumn::operator[](int): The index is = " << i << " must be in the range {1,...,4}";
        throw std::out_of_range(errormessage.str().c_str());
    }
    return this->controlpoints[i - 1];
}


/*
 * \class BezierPatch
 * implements the concept of a geometry matrix for a parametric surface whare each coordinate function is a polynomial of degree 3.
 */

/*
 * Default constructor creates an empty BezierPatch, i.e. all entries are the zero vector.
 */
BezierPatch::BezierPatch()
{}

/*
 * Parameterized constructor creates a BezierPatch containing the arguments as entries.
 * \param G11 - The entry 1,1 of the geometry matrix.
 * \param G12 - The entry 1,2 of the geometry matrix.
 * \param G13 - The entry 1,3 of the geometry matrix.
 * \param G14 - The entry 1,4 of the geometry matrix.
 * \param G21 - The entry 2,1 of the geometry matrix.
 * \param G22 - The entry 2,2 of the geometry matrix.
 * \param G23 - The entry 2,3 of the geometry matrix.
 * \param G24 - The entry 2,4 of the geometry matrix.
 * \param G31 - The entry 3,1 of the geometry matrix.
 * \param G32 - The entry 3,2 of the geometry matrix.
 * \param G33 - The entry 3,3 of the geometry matrix.
 * \param G34 - The entry 3,4 of the geometry matrix.
 * \param G41 - The entry 4,1 of the geometry matrix.
 * \param G42 - The entry 4,2 of the geometry matrix.
 * \param G43 - The entry 4,3 of the geometry matrix.
 * \param G44 - The entry 4,4 of the geometry matrix.
 */
BezierPatch::BezierPatch(glm::vec3 const& G11, glm::vec3 const& G12, glm::vec3 const& G13, glm::vec3 const& G14,
             glm::vec3 const& G21, glm::vec3 const& G22, glm::vec3 const& G23, glm::vec3 const& G24,
             glm::vec3 const& G31, glm::vec3 const& G32, glm::vec3 const& G33, glm::vec3 const& G34,
             glm::vec3 const& G41, glm::vec3 const& G42, glm::vec3 const& G43, glm::vec3 const& G44)
{
    this->controlvec[0] = BezierRow(G11, G12, G13, G14);
    this->controlvec[1] = BezierRow(G21, G22, G23, G24);
    this->controlvec[2] = BezierRow(G31, G32, G33, G34);
    this->controlvec[3] = BezierRow(G41, G42, G43, G44);
}

/*
 * Copy constructor creates a new BezierPatch which is a copy of its argument.
 * \param bezierpatch - The bezierpatch to be copied.
 */
BezierPatch::BezierPatch(BezierPatch const& bezierpatch)
{
    for (int i = 0; i < 4; ++i) {
        this->controlvec[i] = bezierpatch.controlvec[i];
    }
}

/*
 * Destructor destroys the current instance of BezierPatch.
 */
BezierPatch::~BezierPatch()
{}

/*
 * Assignent operator assigns its argument to the current instance of BezierPatch.
 * \param bezierpatch - The bezierpatch to be assigned to this instance.
 */
BezierPatch& BezierPatch::operator=(BezierPatch const& bezierpatch)
{
    if (this != &bezierpatch) {
        for (int i = 0; i < 4; ++i) {
            this->controlvec[i] = bezierpatch.controlvec[i];
        }
    }
    return *this;
}

/*
 * Index operator - read only - returns the i'th entry in the geometry row vector,
 * \param i - The index of the entry to be returned.
 * Notice, the starts at 1 and ends at 4.
 * \return the i'th entry in the geometry row vector.
 */
BezierRow const& BezierPatch::operator[](int i) const
{
    if ((i < 1) || (i > 4)) {
        std::stringstream errormessage;
        errormessage << "BezierPatch::operator[](int): The index is = " << i << " must be in the range {1,...,4}";
        throw std::out_of_range(errormessage.str().c_str());
    }
    return this->controlvec[i - 1];
}

/*
 * Index operator returns a reference to the i'th entry in the geometry row vector.
 * \param i - The index of the entry to which a reference is to be returned. 
 * Notice, the starts at 1 and ends at 4.
 * \return the i'th entry in the geometry row vector.
 */
BezierRow& BezierPatch::operator[](int i)
{
    if ((i < 1) || (i > 4)) {
        std::stringstream errormessage;
        errormessage << "BezierPatch::operator[](int): The index is = " << i << " must be in the range {1,...,4}";
        throw std::out_of_range(errormessage.str().c_str());
    }
    return this->controlvec[i - 1];
}


/*
 * \file bezierpatch.h
 * \brief Utility Functions opeartors
 */

/*
 * PrintIndexMatrix prints the indices in the vertex list. It it a helper function, just for debug purposes.
 * \param PatchNumber - the index of the patch considered.
 * \param index_11 - the index of the vertex that is stored in entry 1,1 in the BezierPatch.
 * \param index_12 - the index of the vertex that is stored in entry 1,2 in the BezierPatch.
 * \param index_13 - the index of the vertex that is stored in entry 1,3 in the BezierPatch.
 * \param index_14 - the index of the vertex that is stored in entry 1,4 in the BezierPatch.
 * \param index_21 - the index of the vertex that is stored in entry 2,1 in the BezierPatch.
 * \param index_22 - the index of the vertex that is stored in entry 2,2 in the BezierPatch.
 * \param index_23 - the index of the vertex that is stored in entry 2,3 in the BezierPatch.
 * \param index_24 - the index of the vertex that is stored in entry 2,4 in the BezierPatch.
 * \param index_31 - the index of the vertex that is stored in entry 3,1 in the BezierPatch.
 * \param index_32 - the index of the vertex that is stored in entry 3,2 in the BezierPatch.
 * \param index_33 - the index of the vertex that is stored in entry 3,3 in the BezierPatch.
 * \param index_34 - the index of the vertex that is stored in entry 3,4 in the BezierPatch.
 * \param index_41 - the index of the vertex that is stored in entry 4,1 in the BezierPatch.
 * \param index_42 - the index of the vertex that is stored in entry 4,2 in the BezierPatch.
 * \param index_43 - the index of the vertex that is stored in entry 4,3 in the BezierPatch.
 * \param index_44 - the index of the vertex that is stored in entry 4,4 in the BezierPatch.
 */
void PrintIndexMatrix(int PatchNumber,
              int index_11, int index_12, int index_13, int index_14,
              int index_21, int index_22, int index_23, int index_24,
              int index_31, int index_32, int index_33, int index_34,
              int index_41, int index_42, int index_43, int index_44)
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
 * ReadBezierPatches reads 16 control points from a file into a BezierPatch, and appends the BezierPatch to the
 * the second parameter.
 * \param filename - a string in the old C-format, i.e. "myfilename".
 * \param BezierPatches - an std::vector<BezierPatch> to which the read BezierPatches are appended.
 * \return A zero is returned if the BezierPatches were read successfully, else an runtme_error exception is thrown.
 */
int ReadBezierPatches(char const* filename, std::vector<BezierPatch>& BezierPatches)
{
    std::cout << "-->ReadBezierPatches(...)" << std::endl;

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

    char   PatchName[MAX_BUFFER];
    int    PatchNumber;
    int    index_11, index_12, index_13, index_14;
    int    index_21, index_22, index_23, index_24;
    int    index_31, index_32, index_33, index_34;
    int    index_41, index_42, index_43, index_44;

    // The vertex list
    std::vector<glm::vec3> Vertices;


    std::ifstream data_file(filename);
    if (!data_file) {
        std::cerr << "Cannot open data file: " << filename << std::endl << std::flush;
        throw std::runtime_error("Error on opening file");
    }
    
    int currentState = NVERTEX;
    while (data_file.get(InputBuffer, MAX_BUFFER, '\n')) {
        std::cout << "InputBuffer: " << InputBuffer << std::endl;

        if (data_file.get(ch) && ch != '\n') {
            data_file.close();
            std::cerr << "Eof on data file: " << filename << std::endl << std::flush;
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
        //           "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
        //           &PatchNumber,
        //           &index_11, &index_12, &index_13, &index_14,
        //           &index_21, &index_22, &index_23, &index_24,
        //           &index_31, &index_32, &index_33, &index_34,
        //           &index_41, &index_42, &index_43, &index_44)
    
        switch (currentState) {
            case NVERTEX: {
                if (InputBuffer[0] != '#') {
                    if (sscanf(InputBuffer, "%d", &NumberOfVertices) != 1) {
                        std::cerr << "number of vertices not found in data file: "
                                  << filename << std::endl << std::flush;
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
                            std::cerr << "patch name not found" << std::endl << std::flush;
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
                        BPatch[1][1] = Vertices[index_11-1];
                        BPatch[1][2] = Vertices[index_12-1];
                        BPatch[1][3] = Vertices[index_13-1];
                        BPatch[1][4] = Vertices[index_14-1];

                        // Second row
                        BPatch[2][1] = Vertices[index_21-1];
                        BPatch[2][2] = Vertices[index_22-1];
                        BPatch[2][3] = Vertices[index_23-1];
                        BPatch[2][4] = Vertices[index_24-1];
            
                        // Third row
                        BPatch[3][1] = Vertices[index_31-1];
                        BPatch[3][2] = Vertices[index_32-1];
                        BPatch[3][3] = Vertices[index_33-1];
                        BPatch[3][4] = Vertices[index_34-1];
            
                        // Forth row
                        BPatch[4][1] = Vertices[index_41-1];
                        BPatch[4][2] = Vertices[index_42-1];
                        BPatch[4][3] = Vertices[index_43-1];
                        BPatch[4][4] = Vertices[index_44-1];

                        BezierPatches.push_back(BPatch);
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
    
    return 0;
}

/**
 * \brief Utility Functions
 */

/**
 * Computes the transpose of a BezierRow.
 * \param bezierrow - the BezierRow to be transposed.
 * \return a BezierColumn which is the transposed of the parameter, bezierrow.
 */
BezierColumn Transpose(BezierRow const& bezierrow)
{
    BezierColumn beziercolumn(bezierrow[1], bezierrow[2], bezierrow[3], bezierrow[4]);
    return beziercolumn;
}

/**
 * Computes the transpose of a BezierColumn.
 * \param beziercolumn - the BezierColumn to be transposed.
 * \return a BezierRow which is the transposed of the parameter, beziercolumn.
 */
BezierRow Transpose(BezierColumn const& beziercolumn)
{
    BezierRow bezierrow(beziercolumn[1], beziercolumn[2], beziercolumn[3], beziercolumn[4]);
    return bezierrow;
}


/*
 * \file bezierpatch.h
 * \brief Utility Operators
 */

/*
 * Multiplication operator, right-multiplies a BezierPatch by an ordinary matrix (a basis matrix).
 * This can be used to right-multiply a Bezier geometry matrix by an ordinary matrix (a basis matrix).
 * \param bezierpatch - The BezierPatch that should be multiplied.
 * \param matrix - The ordinary matrix to be right-multiplied (basis matrix) by the bezier patch.
 * \return The product bezierpatch * matrix which is of type BezierPatch.
 */
BezierPatch operator*(BezierPatch const& bezierpatch, glm::mat4x4 const& matrix)
{
    BezierPatch result;

    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            glm::vec4 column(glm::column(matrix, j - 1));
            result[i][j] = bezierpatch[i] * column;
        }
    }
    return result;
}

/*
 * Multiplication operator, left-multiplies a BezierPatch by an ordinary matrix (a basis matrix).
 * This can be used to left-multiply a BezierPatch by a basis matrix. 
 * \param bezierpatch - The BezierPatch that should be multimplied.
 * \param matrix - The matrix (a basis matrix) that is left-multiplied by the bezier patch.
 * \return The product matrix * bezierpatch which is of type BezierPatch.
 */
BezierPatch operator*(glm::mat4x4 const& matrix, BezierPatch const& bezierpatch)
{
    BezierPatch result;

    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            glm::vec4 row(glm::row(matrix, i - 1));

            glm::vec3 tmpres(0.0f);
            for (int k = 1; k <= 4; ++k) {
                tmpres += row[k - 1] * bezierpatch[k][j];
            }
            result[i][j] = tmpres;
        }
    }
    return result;   
}

/*
 * Multiplication operator, right-multiplies a BezierPatch by an ordinary vector (a parameter vector).
 * This can be used to right-multiply a Bezier geometry matrix by a parameter vector. 
 * \param bezierpatch - The BezierPatch that should be multimplied.
 * \param vector - The vector (a parameter vector) that is right-multiplied by the bezier patch.
 * \return The product bezierpatch * vector which is of type BezierColumn.
 */
BezierColumn operator*(BezierPatch const& bezierpatch, glm::vec4 const& vector)
{
    BezierColumn result;

    for (int i = 1; i <= 4; ++i) {
        result[i] = bezierpatch[i] * vector;
    }
    return result;
}

/*
 * Multiplication operator, left-multilpies a BezierPatch by en ordinary vector (a parameter vector).
 * This can be used to left-multiply a BezierPatch by a parameter vector. 
 * \param bezierpatch - The BezierPatch that should be multimplied.
 * \param vector - The vector (a parameter vector) that is left-multiplied by the bezier patch.
 * \return The product bezierpatch * vector which is of type BezierRow.
 */
BezierRow operator*(glm::vec4 const& vector, BezierPatch const& bezierpatch)
{
    BezierRow result;

    for (int j = 1; j <= 4; ++j) {
        glm::vec3 tmpres(0.0f);
        for (int i = 1; i <= 4; ++i) {
            tmpres += vector[i - 1] * bezierpatch[i][j];
        }
        result[j] = tmpres;
    }
    return result;
}

/*
 * Multiplication operator, right-multiplies a BezierRow by an ordinary vector (a parameter vector).
 * This can be used to right-multiply a BezierRow by a parameter vector. 
 * \param bezierrow - The BezierRow that should be multimplied.
 * \param vector - The vector (a parameter vector) that is right-multiplied by the bezierrow.
 * \return The product bezierrow * vector which is of type glm::vec3.
 */
glm::vec3 operator*(BezierRow const& bezierrow, glm::vec4 vector)
{
    glm::vec3 result(0.0f);

    for (int i = 1; i <= 4; ++i) {
        result += bezierrow[i] * vector[i - 1];
    }
    return result;
}

/*
 * Multiplication operator, right-multiplies a BezierRow by an ordinary matrix (a subdivision matrix).
 * This can be used to right-multiply a BezierRow by a subdivision matrix. 
 * \param bezierrow - The BezierRow that should be multimplied.
 * \param matrix - The matrix (a subdivision matrix) that is right-multiplied by the bezierrow.
 * \return The product bezierrow * matrix which is of type BezierRow.
 */
BezierRow operator*(BezierRow const& bezierrow, glm::mat4x4 matrix)
{
    BezierRow result;

    for (int i = 1; i <= 4; ++i) {
        glm::vec3 element(0.0f);
        for (int j = 1; j <= 4; ++j) {
            element += bezierrow[j] * matrix[i-1][j-1];
        }
        result[i] = element;
    }
    return result;
}

/*
 * Multiplication operator, left-multiplies a BezierColumn by an ordinary vector (a parameter vector).
 * This can be used to left-multiply a BezierColumn by a parameter vector. 
 * \param beziercolumn - The BezierColumn that should be multimplied.
 * \param vector - The vector (a parameter vector) that is left-multiplied by the beziercolumn.
 * \return The product beziercolumn * vector which is of type glm::vec3.
 */
glm::vec3 operator*(glm::vec4 const& vector, BezierColumn const& beziercolumn)
{
    glm::vec3 result(0.0f);

    for (int i = 1; i <= 4; ++i) {
        result += vector[i - 1] * beziercolumn[i];
    }
    return result;
}

/*
 * Multiplication operator, left-multiplies a BezierColumn by an ordinary glm::mat4x4 (a subdivision matrix).
 * This can be used to left-multiply a BezierColumn by a subdivision matrix. 
 * \param beziercolumn - The BezierColumn that should be multimplied.
 * \param matrix - The matrix (a subdivision matrix) that is left-multiplied by the beziercolumn.
 * \return The product beziercolumn * vector which is of type glm::vec3.
 */
BezierColumn operator*(glm::mat4x4 const& matrix, BezierColumn const& beziercolumn)
{
    BezierColumn result;

    for (int i = 1; i <= 4; ++i) {
        glm::vec3 element(0.0f);
        for (int j = 1; j <= 4; ++j) {
            element +=matrix[j-1][i-1] * beziercolumn[j];
        }
        result[i] = element;
    }
    return result;
}

/*
 * Insertion operator, inserts a BezierRow into an ostream.
 * \param s - The ostream which the geometryvector should be inserted into.
 * \param bezierrow - The BezierRow that should be inserted into the ostream.
 * \return The ostream which the bezierpatch has been inserted into.
 */
std::ostream& operator<<(std::ostream& s, BezierRow const& bezierrow)
{
    for (int i = 1; i < 4; ++i) {
        s << ' ' << std::setw(6) << std::setprecision(4) << bezierrow[i] << " | ";
    }
    s << std::setw(6) << std::setprecision(4) << bezierrow[4] << std::endl;
    return s;
}

/*
 * Insertion operator, inserts a BezierColumn into an ostream.
 * \param s - The ostream which the geometryvector should be inserted into.
 * \param beziercolumn - The BezierColumn that should be inserted into the ostream.
 * \return The ostream which the bezierpatch has been inserted into.
 */
std::ostream& operator<<(std::ostream& s, BezierColumn const& beziercolumn)
{
    for (int i = 1; i < 4; ++i) {
        s << ' ' << std::setw(6) << std::setprecision(4) << beziercolumn[i] << " | ";
    }
    s << std::setw(6) << std::setprecision(4) << beziercolumn[4] << std::endl;
    return s;
}

/*
 * Insertion operator, inserts a BezierPatch into an ostream.
 * \param s - The ostream which the geometryvector should be inserted into.
 * \param bezierpatch - The BezierPatch that should be inserted into the ostream.
 * \return The ostream which the bezierpatch has been inserted into.
 */
std::ostream& operator<<(std::ostream& s, BezierPatch const& bezierpatch)
{
    for (int i = 1; i <= 4; ++i) {
        s << ' ';
        for (int j = 1; j < 4; ++j) {
            s << std::setw(6) << std::setprecision(4) << bezierpatch[i][j] << " | ";
        }
        s << std::setw(6) << std::setprecision(4) << bezierpatch[i][4] << ' ' << std::endl;
    }
    return s;
}
