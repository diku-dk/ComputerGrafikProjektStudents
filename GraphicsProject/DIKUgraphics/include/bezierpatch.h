#ifndef __BEZIERPATCH_H__
#define __BEZIERPATCH_H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <stdexcept>
#include <cmath>
#include <string>
#include <sstream>
#include <cstring>
#include <cctype>
#include <vector>

#include "glmutils.h"
#include "traceinfo.h"


/**
 * \class BezierRow 
 * implements the concept of a row of a geometry matrix for a parametric surface where
 * each coordinate function is a polynomial of degree 3.
 */
class BezierRow {
public:
    /**
     * Default constructor creates an empty BezierRow, i.e. all entries are the zero vector.
     */
    BezierRow();

    /**
     * Parameterized constructor creates a BezierRow containing the arguments as entries.
     * \param G1 - Entry one in the geometry row vector.
     * \param G2 - Entry two in the geometry row vector.
     * \param G3 - Entry three in the geometry row vector.
     * \param G4 - Entry four in the geometry row vector.
     */
    BezierRow(glm::vec3 const& G1, glm::vec3 const& G2, glm::vec3 const& G3, glm::vec3 const& G4);

    /**
     * Copy constructor creates a new BezierRow which is a copy of its argument.
     * \param bezierrow - The geometry row vector to be copied.
     */
    BezierRow(BezierRow const& bezierrow);

    /**
     * Destructor destroys the current instance of BezierRow.
     */
    virtual ~BezierRow();

    /**
     * Assignent operator assigns its argument to the current instance of BezierRow.
     * \param bezierrow - The geometry row vector to be assigned to this instance.
     */
    BezierRow& operator=(BezierRow const& bezierrow);

    /**
     * Index operator - read only - returns the i'th entry in the geometry row vector,
     * \param i - The index of the entry to be returned.
     * Notice, the starts at 1 and ends at 4.
     * \return the i'th entry in the geometry row vector.
     */
    glm::vec3 const& operator[](int i) const;

    /**
     * Index operator returns a reference to the i'th entry in the geometry row vector.
     * \param i - The index of the entry to which a reference is to be returned. 
     * Notice, the starts at 1 and ends at 4.
     * \return the i'th entry in the geometry row vector.
     */
    glm::vec3& operator[](int i);

protected:

private:
    /**
     * The four Control Points of a Bezier Curve
     */
    glm::vec3 controlpoints[4];
};

/**
 * \class BezierColumn
 * implements the concept of a column of a geometry matrix for a parametric surface where
 * each coordinate function is a polynomial of degree 3.
 */
class BezierColumn {
public:
    /**
     * Default constructor creates an empty BezierColumn, i.e. all entries are the zero vector.
     */
    BezierColumn();

    /**
     * Parameterized constructor creates a BezierColumn containing the arguments as entries.
     * \param G1 - Entry one in the geometry column vector.
     * \param G2 - Entry two in the geometry column vector.
     * \param G3 - Entry three in the geometry column vector.
     * \param G4 - Entry four in the geometry column vector.
     */
    BezierColumn(glm::vec3 const& G1, glm::vec3 const& G2, glm::vec3 const& G3, glm::vec3 const& G4);

    /**
     * Copy constructor creates a new BezierColumn which is a copy of its argument.
     * \param beziercolumn - The geometry column vector to be copied.
     */
    BezierColumn(BezierColumn const& beziercolumn);

    /**
     * Destructor destroys the current instance of BezierColumn.
     */
    virtual ~BezierColumn();

    /**
     * Assignent operator assigns its argument to the current instance of BezierColumn.
     * \param beziercolumn - The geometry column vector to be assigned to this instance.
     */
    BezierColumn& operator=(BezierColumn const& beziercolumn);

    /**
     * Index operator - read only - returns the i'th entry in the geometry column vector,
     * \param i - The index of the entry to be returned.
     */
    glm::vec3 const& operator[](int i) const;

    /**
     * Index operator returns a reference to the i'th entry in the geometry column vector.
     * \param i - The index of the entry to which a reference is to be returned. Notice, the starts at 1 and ends at 4.
     */
    glm::vec3& operator[](int i);

protected:

private:
    /**
     * The four Control Points of a Bezier Curve
     */
    glm::vec3 controlpoints[4];
};


/**
 * \class BezierPatch
 * implements the concept of a geometry matrix for a parametric surface whare each coordinate function is a polynomial of degree 3.
 */
class BezierPatch {
public:
    /**
     * Default constructor creates an empty BezierPatch, i.e. all entries are the zero vector.
     */
    BezierPatch();

    /**
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
    BezierPatch(glm::vec3 const& G11, glm::vec3 const& G12, glm::vec3 const& G13, glm::vec3 const& G14,
	        glm::vec3 const& G21, glm::vec3 const& G22, glm::vec3 const& G23, glm::vec3 const& G24,
	        glm::vec3 const& G31, glm::vec3 const& G32, glm::vec3 const& G33, glm::vec3 const& G34,
	        glm::vec3 const& G41, glm::vec3 const& G42, glm::vec3 const& G43, glm::vec3 const& G44);

    /**
     * Copy constructor creates a new BezierPatch which is a copy of its argument.
     * \param bezierpatch - The bezierpatch to be copied.
     */
    BezierPatch(BezierPatch const& bezierpatch);

    /**
     * Destructor destroys the current instance of BezierPatch.
     */
    virtual ~BezierPatch();

    /**
     * Assignent operator assigns its argument to the current instance of BezierPatch.
     * \param bezierpatch - The bezierpatch to be assigned to this instance.
     */
    BezierPatch& operator=(BezierPatch const& bezierpatch);

    /**
     * Index operator - read only - returns the i'th row of the geometry matrix,
     * \param i - The index of the row to be returned.
     */
    BezierRow const& operator[](int i) const;

    /**
     * Index operator returns a reference to the i'th row iof the geometry matrix.
     * \param i - The index of the row to which a reference is to be returned. Notice, the starts at 1 and ends at 4.
     */
    BezierRow& operator[](int i);

protected:

private:
    /**
     * The 16 Control Points of a Bezier Curve
     */
    BezierRow controlvec[4];
};


/**
 * \file bezierpatch.h
 * \brief Utility Functions and operators
 */

/**
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
		      int index_41, int index_42, int index_43, int index_44);

/**
 * ReadBezierPatches reads 16 control points from a file into a BezierPatch, and appends the BezierPatch to the
 * the second parameter.
 * \param filename - a string in the old C-format, i.e. "myfilename".
 * \param BezierPatches - an std::vector<BezierPatch> to which the read BezierPatches are appended.
 * \return A zero is returned if the BezierPatches were read successfully, else an runtme_error exception is thrown.
 */
int ReadBezierPatches(char const* filename, std::vector<BezierPatch>& BezierPatches);

/**
 * Computes the transpose of a BezierRow.
 * \param bezierrow - the BezierRow to be transposed.
 * \return a BezierColumn which is the transposed of the parameter, bezierrow.
 */
BezierColumn Transpose(BezierRow const& bezierrow);

/**
 * Computes the transpose of a BezierColumn.
 * \param beziercolumn - the BezierColumn to be transposed.
 * \return a BezierRow which is the transposed of the parameter, beziercolumn.
 */
BezierRow Transpose(BezierColumn const& beziercolumn);

/**
 * \brief Utility Operators
 */

/**
 * Multiplication operator, right-multiplies a BezierPatch by an ordinary matrix (a basis matrix).
 * This can be used to right-multiply a Bezier geometry matrix by an ordinary matrix (a basis matrix).
 * \param bezierpatch - The BezierPatch that should be multiplied.
 * \param matrix - The ordinary matrix to be right-multiplied (basis matrix) by the bezier patch.
 * \return The product bezierpatch * matrix which is of type BezierPatch.
 */
BezierPatch operator*(BezierPatch const& bezierpatch, glm::mat4x4 const& matrix);

/**
 * Multiplication operator, left-multiplies a BezierPatch by an ordinary matrix (a basis matrix).
 * This can be used to left-multiply a BezierPatch by a basis matrix. 
 * \param bezierpatch - The BezierPatch that should be multimplied.
 * \param matrix - The matrix (a basis matrix) that is left-multiplied by the bezier patch.
 * \return The product matrix * bezierpatch which is of type BezierPatch.
 */
BezierPatch operator*(glm::mat4x4 const& matrix, BezierPatch const& bezierpatch);

/**
 * Multiplication operator, right-multiplies a BezierPatch by an ordinary vector (a parameter vector).
 * This can be used to right-multiply a Bezier geometry matrix by a parameter vector. 
 * \param bezierpatch - The BezierPatch that should be multimplied.
 * \param vector - The vector (a parameter vector) that is right-multiplied by the bezier patch.
 * \return The product bezierpatch * vector which is of type BezierColumn.
 */
BezierColumn operator*(BezierPatch const& bezierpatch, glm::vec4 const& vector);

/**
 * Multiplication operator, left-multilpies a BezierPatch by en ordinary vector (a parameter vector).
 * This can be used to left-multiply a BezierPatch by a parameter vector. 
 * \param bezierpatch - The BezierPatch that should be multimplied.
 * \param vector - The vector (a parameter vector) that is left-multiplied by the bezier patch.
 * \return The product bezierpatch * vector which is of type BezierRow.
 */
BezierRow operator*(glm::vec4 const& vector, BezierPatch const& bezierpatch);

/**
 * Multiplication operator, right-multiplies a BezierRow by an ordinary vector (a parameter vector).
 * This can be used to right-multiply a BezierRow by a parameter vector. 
 * \param bezierrow - The BezierRow that should be multimplied.
 * \param vector - The vector (a parameter vector) that is right-multiplied by the bezierrow.
 * \return The product bezierrow * vector which is of type glm::vec3.
 */
glm::vec3 operator*(BezierRow const& bezierrow, glm::vec4 vector);

/**
 * Multiplication operator, right-multiplies a BezierRow by an ordinary matrix (a subdivision matrix).
 * This can be used to right-multiply a BezierRow by a subdivision matrix. 
 * \param bezierrow - The BezierRow that should be multimplied.
 * \param matrix - The matrix (a subdivision matrix) that is right-multiplied by the bezierrow.
 * \return The product bezierrow * matrix which is of type BezierRow.
 */
BezierRow operator*(BezierRow const& bezierrow, glm::mat4x4 matrix);

/**
 * Multiplication operator, left-multiplies a BezierColumn by an ordinary vector (a parameter vector).
 * This can be used to left-multiply a BezierColumn by a parameter vector. 
 * \param beziercolumn - The BezierColumn that should be multimplied.
 * \param vector - The vector (a parameter vector) that is left-multiplied by the beziercolumn.
 * \return The product beziercolumn * vector which is of type glm::vec3.
 */
glm::vec3 operator*(glm::vec4 const& vector, BezierColumn const& beziercolumn);

/**
 * Multiplication operator, left-multiplies a BezierColumn by an ordinary glm::mat4x4 (a subdivision matrix).
 * This can be used to left-multiply a BezierColumn by a subdivision matrix. 
 * \param beziercolumn - The BezierColumn that should be multimplied.
 * \param matrix - The matrix (a subdivision matrix) that is left-multiplied by the beziercolumn.
 * \return The product beziercolumn * vector which is of type glm::vec3.
 */
BezierColumn operator*(glm::mat4x4 const& matrix, BezierColumn const& beziercolumn);

/**
 * Insertion operator, inserts a BezierRow into an ostream.
 * \param s - The ostream which the geometryvector should be inserted into.
 * \param bezierrow - The BezierRow that should be inserted into the ostream.
 * \return The ostream which the bezierpatch has been inserted into.
 */
std::ostream& operator<<(std::ostream& s, BezierRow const& bezierrow);

/**
 * Insertion operator, inserts a BezierColumn into an ostream.
 * \param s - The ostream which the geometryvector should be inserted into.
 * \param beziercolumn - The BezierColumn that should be inserted into the ostream.
 * \return The ostream which the bezierpatch has been inserted into.
 */
std::ostream& operator<<(std::ostream& s, BezierColumn const& beziercolumn);

/**
 * Insertion operator, inserts a BezierPatch into an ostream.
 * \param s - The ostream which the geometryvector should be inserted into.
 * \param bezierpatch - The BezierPatch that should be inserted into the ostream.
 * \return The ostream which the bezierpatch has been inserted into.
 */
std::ostream& operator<<(std::ostream& s, BezierPatch const& bezierpatch);

#endif
