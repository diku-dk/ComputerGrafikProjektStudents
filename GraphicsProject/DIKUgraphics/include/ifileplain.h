#ifndef __RASTERMAN_IFILE_PLAIN_H__
#define __RASTERMAN_IFILE_PLAIN_H__

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>

#include "traceinfo.h"


/**
 * \class InputFile
 * InputFile is a utility class which makes it easy to open, close, and read from a file.
 *
 * \sa operator>>(InputFile& file, Type& value)
 * for how to read from a file
 */
class InputFile : public std::ifstream
{
public:
    /**
     * Parameterized constructor, creates an instance of an OInputFile and opens an 
     * external file given by a filename for reading.
     * \param Filename - a string containing the name of the file to be opened.
     */
    InputFile(std::string const& Filename);

    /**
     * Destructor, closes the external file and destroys the instance of InputFile.
     */
    virtual ~InputFile();

    /**
     * Opens an external file given by the parameter. If there already exists an open file, 
     * it is closed before the new one is opened.
     * \param Filename - a string containing the name of the file to be opened.
     */
    void Open(std::string const& Filename);

    /**
     * Closes the external file if it is open.
     */
    void Close();

    /**
     * Returns the name of the external file.
     * \return the name of the currently open external file.
     */
    std::string Filename() const;

    /**
     * Has the value true if there is bad input in the file, i.e. fail() && !eof() && !bad()
     * \return fail() && !eof() && !bad()
     */
    bool bad_input();

    /**
     * Prints the status of the InputFile.
     * There are the following states:
     *
     *     good - everything is fine, and one can read from the file.
     *
     *     fail - it is not possible to read the file. 
     *            This includes everything, i.e.
     *            file does not exist,
     *            hardware error,
     *            eof,
     *            bad input.
     *
     *     bad - something hardware is wrong, so one cannot read the file.
     *
     *     eof - the end of the file has been reached.
     *
     * So, (fail && !bad && !eof) must mean bad input.
     */
    void CheckStatus();

protected:

private:
    std::string filename;
    bool open;
};

#endif
