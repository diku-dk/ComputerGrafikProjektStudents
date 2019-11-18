#include "traceinfo.h"

/*
 * Parameterized constructor, creates a TraceInfo object.
 * \param ClassName - The name of the class that the function belongs to. 
 * If it is a function that is not a member function, the empty string should be entered as the ClassName.
 * \param MemberName - Tha name og the member function.
 * \param FileName - The name of the file where the function was called.
 * \param LineNumber - The line number in the file FileNama where the function was called.
 * \param TraceLevel - Determines how verbose the output should be. Values: 0, 1, 2.
 */
TraceInfo::TraceInfo(const std::string& ClassName,
                     const std::string& MemberName,
                     const std::string& FileName,
                     const uint         LineNumber,
             const uint         TraceLevel)
         : classname(ClassName), membername(MemberName),
           filename(FileName),   linenumber(LineNumber), tracelevel(TraceLevel),
           prefix(ClassName + "::" + MemberName)
{
    for (uint i = 1; i <= indentlevel; ++i) std::clog << indentspace;
    std::clog << enter  << this->classname << "::" << this->membername;
    if (this->tracelevel == 2) {
        std::clog << " -- " << this->RemovePrefix(this->filename)  << '('  << this->linenumber << ')';
    }
    std::clog << std::endl << std::flush;
    ++indentlevel;
    for (uint j = 1; j <= indentlevel; ++j) prefix = indentspace + prefix;
}

/*
 * Destructor releases any dymically allocated storage used by class TraceInfo
 */
TraceInfo::~TraceInfo()
{
    --indentlevel;
    for (uint i = 1; i <= indentlevel; ++i) std::clog << indentspace;
    std::clog << leave << this->classname << "::" << this->membername;
    if (this->tracelevel == 2) {
        std::clog << " -- " << this->RemovePrefix(this->filename) << '('  << this->linenumber << ')';
    }
    std::clog << std::endl << std::flush;
}

/*
 * The actual Class Name
 * \return - the actual classname
 */
std::string TraceInfo::ClassName() const
{
    return this->classname;
}

/*
 * The actual Member Name
 * \return - the actual mambername
 */
std::string TraceInfo::MemberName() const
{
    return this->membername;
}

/*
 * The actual File Name
 * \return - the actual filename
 */
std::string TraceInfo::FileName() const
{
    return this->filename;
}

/*
 * The actual Line Number
 * \return - the actual linenumber
 */
uint TraceInfo::LineNumber() const
{
    return this->linenumber;
}

/*
 * \return A string containing information of the class and member function the program executes 
 * when it is called.
 */
const std::string& TraceInfo::Prefix() const
{
    return prefix;
}

/*
 * Removes the prefix of the filename, so only the last filename is left.
 * \param FullFilename - the full filename from the home directory.
 * \return the last filena in the path.
 */
std::string TraceInfo::RemovePrefix(std::string const& FullFilename) const
{
    size_t found = FullFilename.find_last_of('/');
    std::string suffix = FullFilename.substr(found + 1);

    return suffix;
}


/*
 * Initialization of static variables
 */
uint              TraceInfo::indentlevel = 0;
const std::string TraceInfo::enter       = "-->";
const std::string TraceInfo::leave       = "<--";
const std::string TraceInfo::indentspace = "   ";
