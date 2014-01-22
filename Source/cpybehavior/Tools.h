/*===========================================================================

	Tools.h
  
    Adapts the xabsl::Engine to the target platform.
    
     author: Martin Lötzsch
===========================================================================*/

#ifndef __Tools_h_
#define __Tools_h_

#include <fstream>
#include <sys/timeb.h>

// An error handling class derived from xabsl::ErrorHandler
class MyErrorHandler : public xabsl::ErrorHandler
{
public:
  MyErrorHandler() { logfile.open("messages.log"); }

  ~MyErrorHandler() { logfile.close(); }

  virtual void printError(const char* text) 
  {logfile << "error: " << text << "\n"; logfile.flush();}
  
  virtual void printMessage(const char* text)
  {logfile << text << "\n"; logfile.flush();}

private:
  std::ofstream logfile;
}; 

// A file access class derived from xabsl::InputSource
class MyFileInputSource : public xabsl::InputSource
{
public:
  MyFileInputSource(const char* fileName) : file(0), theChar(' ') 
  { strcpy(filename,fileName); }

  ~MyFileInputSource() {if (file!=0) delete file;}

  virtual bool open() {file = new std::ifstream(filename); return(file!=0 && !file->fail());} 
  virtual void close() {if (file!=0) delete file; file = 0;}

  virtual double readValue() 
  { char buf[20]; readFromFile(buf); return atof(buf); }

  virtual bool readString(char* destination, int maxLength) 
  { readFromFile(destination); return true; } 
  
private:
  char filename[200]; // the file name
  std::ifstream* file; // the file to access
  char theChar; // the last character read

  void readFromFile(char* value)
  {
    while(!file->eof() && isWhitespace()) 
    {
      if (theChar == '/') while(!file->eof() && theChar != '\n') file->read(&theChar,1);
      file->read(&theChar,1);
    }

    while(!file->eof() && !isWhitespace())
    { *value++ = theChar; if(!file->eof()) file->read(&theChar,1); }
    *value = 0;
  }

  bool isWhitespace()
  { return theChar == ' ' || theChar == '/' || theChar == '\n' || theChar == '\r' || theChar == '\t'; }
};

// returns the current system time in milliseconds 
static unsigned getCurrentSystemTime() {
  timeb sysTime;
  ftime(&sysTime);
  return (sysTime.time * 1000 + sysTime.millitm);
}

#endif //__Tools_h_
