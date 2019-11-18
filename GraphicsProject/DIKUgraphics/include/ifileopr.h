#ifndef __RASTERMAN_IFILE_OPR_H__
#define __RASTERMAN_IFILE_OPR_H__

/**
 * \file
 */

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <sstream>

#include "traceinfo.h"
#include "ifileplain.h"

/**
 * Utility template operator which makes it easy to read from a file.
 * \param infile - the file to be read.
 * \param value - the value read.
 * \return a reference to the InputFile read from.
 */
template <typename Type>
InputFile& operator>>(InputFile& infile, Type& value);


#include "ifileopr.impl"

#endif
