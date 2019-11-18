#include "ifileplain.h"


/*
 * \class InputFile
 * InputFile is a utility class which makes it easy to open, close, and read from a file.
 */

/*
 * Parameterized constructor, creates an instance of an OInputFile and opens an external file given by a filename
 * for reading.
 * \param Filename - a string containing the name of the file to be opened.
 */
InputFile::InputFile(std::string const& Filename) : filename(Filename), open(false)
{
    Trace("InputFile", "InputFile(string&)");

    this->Open(this->filename);
}

/*
 * Destructor, closes the external file and destroys the instance of InputFile.
 */
InputFile::~InputFile()
{
    Trace("InputFile", "~InputFile()");

    this->Close();
}

/*
 * Opens an external file given by the parameter. If there already exists an open file,
 * it is closed before the new one is opened.
 * \param Filename - a string containing the name of the file to be opened.
 */
void InputFile::Open(std::string const& Filename)
{
    Trace("InputFile", "Open(std::string&)");

    if (this->open) {
        if (this->filename != Filename) {
            this->Close();
            this->filename = "";
        }
    }

    if (!this->open) {
        this->filename = Filename;
        this->std::ifstream::open(Filename.c_str());
        if (this->is_open())
            this->open = true;
        else {
            throw std::runtime_error(std::string("Cannot open file: ") + this->filename);
        }
    }
}

/*
 * Closes the external file if it is open.
 */
void InputFile::Close()
{
    Trace("InputFile", "Close()");

    if (this->open == false) {
        this->std::ifstream::close();
        this->open = false;
        this->filename = "";
    }
}

/*
 * Returns the name of the external file.
 * \return the name of the currently open external file.
 */
std::string InputFile::Filename() const
{
    Trace("InputFile", "Filename()");

    return this->filename;
}

/*
 * Has the value true if there is bad input in the file, i.e. fail() && !eof() && !bad()
 * \return fail() && !eof() && !bad()
 */
bool InputFile::bad_input()
{
    return this->fail() && !this->bad() && !this->eof();
}

/*
 * Prints the status of the InputFile
 */
void InputFile::CheckStatus()
{
    Trace("Inputfile", "CheckStatus()");

#if TRACE != 0
    TraceMessage("good = " << std::boolalpha << this->good() << std::endl;);
    TraceMessage("fali = " << std::boolalpha << this->fail() << std::endl;);
    TraceMessage("bad  = " << std::boolalpha << this->bad()  << std::endl;);
    TraceMessage("eof  = " << std::boolalpha << this->eof()  << std::endl;);
    bool badinput = this->fail() && !this->bad() && !this->eof();
    TraceMessage("bad input = " << std::boolalpha << badinput << std::endl;);
#else
    std::cout << "good = " << std::boolalpha << this->good() << std::endl;
    std::cout << "fali = " << std::boolalpha << this->fail() << std::endl;
    std::cout << "bad  = " << std::boolalpha << this->bad()  << std::endl;
    std::cout << "eof  = " << std::boolalpha << this->eof()  << std::endl;
    bool badinput = this->fail() && !this->bad() && !this->eof();
    std::cout << "bad input = " << std::boolalpha << badinput << std::endl;
#endif
}

