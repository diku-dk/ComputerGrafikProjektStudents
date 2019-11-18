#ifndef __RASTERMAN_TRACEINFO_H__
#define __RASTERMAN_TRACEINFO_H__

#include <iostream>
#include <iomanip>
#include <string>
typedef unsigned int uint;


/**
 * \class TraceInfo
 * Makes it possible to make a trace of function calls in a program. The class TraceInfo is not supposed to be used
 * directly in everyday programming.
 *
 * There are a number of convenience macros which use the the class TraceInfo, and these macros 
 * make the TraceInfo easier to use. \n
 * If the compiler directive TRACE is defined a computational trace will be genereted. \n
 * There are several levels of output according to the compiler flags \n
 * \b Example: \n
 * \code
 *     c++ -DTRACE=N ...
 * \endcode
 * where \b N is one of {0, 1, 2}
 * \indent -DTRACE=0 - No output at all
 * \indent -DTRACE=1 - Output 'ClassName::MemberName'
 * \indent -DTRACE=2 - Output 'ClassName::MemberName --- FileName(linenumber)'
 *
 * \sa Trace(...), TraceMessage(...), CondTraceMessage(...)
 */
//  * \sa Trace(ClassName, MemberName), TraceMessage(Statement), CondTraceMessage(Condition, TrueStatement, FalseStatement)
class TraceInfo {
public:
    /**
     * Parameterized constructor, creates a TraceInfo object.
     * \param ClassName - The name of the class that the function belongs to. 
     * If it is a function that is not a member function, the empty string should be entered as the ClassName.
     * \param MemberName - Tha name og the member function.
     * \param FileName - The name of the file where the function was called.
     * \param LineNumber - The line number in the file FileNama where the function was called.
     * \param TraceLevel - Determines how verbose the output should be. Values: 0, 1, 2.
     */
    TraceInfo(const std::string& ClassName, const std::string& MemberName,
	      const std::string& FileName,  const uint LineNumber = 0, const uint TraceLevel = 0);

    /**
     * Destructor releases any dymically allocated storage used by class TraceInfo
     */
    virtual ~TraceInfo();

    /**
     * The actual Class Name
     * \return - the actual classname
     */
    std::string ClassName() const;

    /**
     * The actual Member Name
     * \return - the actual mambername
     */
    std::string MemberName() const;

    /**
     * The actual File Name
     * \return - the actual filename
     */
    std::string FileName() const;

    /**
     * The actual Line Number
     * \return - the actual linenumber
     */
    uint LineNumber() const;

    /**
     * \return A string containing information of the class and member function the program executes 
     * when it is called.
     */
     const std::string& Prefix() const;

    /**
     * Removes the prefix of the filename, so only the last filename is left.
     * \param FullFilename - the full filename from the home directory.
     * \return the last filename in the path.
     */
    std::string RemovePrefix(std::string const& FullFilename) const;

private:
    /**
     * Private variables
     */
    const std::string  classname;
    const std::string  membername; 
    const std::string  filename;
    const uint         linenumber;
    const uint         tracelevel;
    std::string        prefix;

    /**
     * Static private variables
     */
    static uint              indentlevel;
    static const std::string enter;
    static const std::string leave;
    static const std::string indentspace;
};

/**
 * \file traceinfo.h
 */

/**
 * Convenience Macros which makes it easier to use the class TraceInfo.
 *
 * The output from the macros (in the their most verbatim form) has the form:
 \verbatim
    ClassName::MemberName -- FileName(LineNumber)
\endverbatim
 *
 * where
\verbatim
    ClassName  - is the name of the class where it was called
    MemberName - is the name of the member function where it was called
    FileName   - is the name of the file from where it was called
    LineNumber - is the line number in the file where it was called
\endverbatim
 */
 
/**
 * If the compiler flag TRACE is not defined, the macro is empty.
 * Else it instantiates class TraceInfo with arguments telling the ClassName and MemberFunction.
 * The FileName and LineNumber is supplied automatically.
 * \param ClassName - The name of the class that contains the member function.
 * \param MemberName - The name of the member function executing.
 *
 * \b Example
 * \code
 * // file: MyClass.cpp
 * // compiler flag: -DTRACE=2
 *
 * void ClassName::MemberName(int)
 * {
 *     Trace("ClassName", "MemberName(int)");
 *
 *     ...
 *
 * }
 * \endcode
 *
 * \b Output
 * \code
 * -->ClassName::MemberName(int) -- MyClass.cpp(6)
 *
 *    ...
 *
 * <--ClassName::MemberName(int) -- MyClass.cpp(6)
 * \endcode
 */
#if TRACE == 0
#define Trace(ClassName, MemberName)
#elif TRACE > 0
#define Trace(ClassName, MemberName)                                     \
TraceInfo TRACEINFO(std::string(ClassName), std::string(MemberName),     \
                    std::string(__FILE__), __LINE__, TRACE);
#endif

/**
 * If the compiler flag TRACE is not defined, the macro is empty.
 * Else it writes its parameter to std::clog.
 * \param Statement - The parameter is written to std::clog.
 *
 * \b Example
 * \code
 * // file: MyClass.cpp
 * // compiler flag: -DTRACE=2
 *
 * void ClassName::MemberName()
 * {
 *     Trace("ClassName", "MembeNname()");
 *
 *     ...
 *
 *     int N = 10;
 *     TraceMessage("N = " << N << std::endl;);
 *
 *     ...
 *
 * }
 * \endcode
 *
 * \b Output
 * \code
 * -->ClassName::MemberName() -- MyClass(6)
 *
 *    ...
 *
 *    ClassName::MemberName() -- MyClass.cpp(11): N = 10
 *
 *    ...
 *
 * <--ClassName::MemberName() -- MyClass(6)
 * \endcode
 */
#if TRACE == 0
#define TraceMessage(Statement)
#elif TRACE == 1
#define TraceMessage(Statement)                                                         \
    std::clog << TRACEINFO.Prefix()                                                     \
              << ": " << Statement;
#elif TRACE >= 2
#define TraceMessage(Statement)                                                         \
    std::clog << TRACEINFO.Prefix()                                                     \
              << " -- " << TRACEINFO.RemovePrefix(__FILE__) << '(' << __LINE__ << ")" \
              << ": " << Statement;
#endif

/**
 * If the compiler flag TRACE is not defined, the macro is empty.
 * Else it writes one of its parameters to std::clog.
 * \param Condition - A boolean expression that determines which parameter is written to std::clog.
 * \param TrueStatement - An expression written to std::clog if the parameter Condition is true.
 * \param FalseStatement - An expression written to std::clog if the parameter Condition is false.
 *
 * \b Example
 * \code
 * // file: MyClass.cpp
 * // compiler flag: -DTRACE=2
 *
 * void ClassName::MemberName()
 * {
 *     Trace("ClassName", "MemberName()");
 *
 *     ...
 *
 *     int N = 10;
 *     CondTraceMessage(N > 0, "N > 0" << std::endl;, "N <= 0" << std::endl;);
 *
 *     ...
 * }
 * \endcode
 *
 * \b Output
 * \code
 * -->ClassName::MemberName() -- MyClass.cpp(6)
 *
 *    ...
 *
 *    ClassName::MemberName() -- MyClass.cpp(11): N > 0
 *
 *    ...
 *
 * <--ClassName::MemberName() -- MyClass.cpp(6)
 * \endcode
 */

#if TRACE == 0
#define CondTraceMessage(Condition, TrueStatement, FalseStatement)
#elif TRACE == 1
#define CondTraceMessage(Condition, TrueStatement, FalseStatement)                          \
    if (Condition) {                                                                        \
        std::clog << TRACEINFO.Prefix() << ": " << TrueStatement;	                    \
    }                                                                                       \
    else {                                                                                  \
        std::clog << TRACEINFO.Prefix() << ": " << FalseStatement;	                    \
    }
#elif TRACE >= 2
#define CondTraceMessage(Condition, TrueStatement, FalseStatement)                          \
    if (Condition) {                                                                        \
        std::clog << TRACEINFO.Prefix()                                                     \
                  << " -- " << TRACEINFO.RemovePrefix(__FILE__) << '(' << __LINE__ << ")"   \
                  << ": " << TrueStatement;				                    \
    }                                                                                       \
    else {                                                                                  \
        std::clog << TRACEINFO.Prefix()                                                     \
		  << " -- " << TRACEINFO.RemovePrefix(__FILE__) << '(' << __LINE__ << ")"   \
                  << ": " << FalseStatement;				                    \
    }
#endif

#endif
