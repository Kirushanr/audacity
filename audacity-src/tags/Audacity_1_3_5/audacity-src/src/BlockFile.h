/**********************************************************************

  Audacity: A Digital Audio Editor

  BlockFile.h

  Joshua Haberman
  Dominic Mazzoni

**********************************************************************/

#ifndef __AUDACITY_BLOCKFILE__
#define __AUDACITY_BLOCKFILE__

#include <wx/string.h>
#include <wx/ffile.h>
#include <wx/filename.h>

#include "WaveTrack.h"

#include "xml/XMLTagHandler.h"
#include "xml/XMLWriter.h"

class wxFFile;

class SummaryInfo {
 public:
   SummaryInfo(sampleCount samples);

   int            fields; /* Usually 3 for Min, Max, RMS */
   sampleFormat   format;
   int            bytesPerFrame;
   sampleCount    frames64K;
   int            offset64K;
   sampleCount    frames256;
   int            offset256;
   int            totalSummaryBytes;
};



class BlockFile {
 public:

   // Constructor / Destructor

   /// Construct a BlockFile.
   BlockFile(wxFileName fileName, sampleCount samples);
   virtual ~BlockFile();

   static void Deinit();

   // Reading

   /// Retrieves audio data from this BlockFile
   virtual int ReadData(samplePtr data, sampleFormat format,
                        sampleCount start, sampleCount len) = 0;

   // Other Properties
   
   // Write cache to disk, if it has any
   virtual bool GetNeedWriteCacheToDisk() { return false; }
   virtual void WriteCacheToDisk() { /* no cache by default */ }

   // Fill read cache of block file, if it has any
   virtual bool GetNeedFillCache() { return false; }
   virtual void FillCache() { /* no cache by default */ }

   /// Stores a representation of this file in XML
   virtual void SaveXML(XMLWriter &xmlFile) = 0;

   /// Gets the filename of the disk file associated with this BlockFile
   virtual wxFileName GetFileName();
   virtual sampleCount GetLength() { return mLen; }

   /// Locks this BlockFile, to prevent it from being moved
   virtual void Lock();
   /// Unlock this BlockFile, allowing it to be moved
   virtual void Unlock();
   /// Returns TRUE if this BlockFile is locked
   virtual bool IsLocked();

   /// Gets extreme values for the specified region
   virtual void GetMinMax(sampleCount start, sampleCount len,
                          float *outMin, float *outMax, float *outRMS);
   /// Gets extreme values for the entire block
   virtual void GetMinMax(float *outMin, float *outMax, float *outRMS);
   /// Returns the 256 byte summary data block
   virtual bool Read256(float *buffer, sampleCount start, sampleCount len);
   /// Returns the 64K summary data block
   virtual bool Read64K(float *buffer, sampleCount start, sampleCount len);

   /// Returns TRUE if this block references another disk file
   virtual bool IsAlias() { return false; }
   /// Create a new BlockFile identical to this, using the given filename
   virtual BlockFile *Copy(wxFileName newFileName) = 0;

   virtual wxLongLong GetSpaceUsage() = 0;

   /// if the on-disk state disappeared, either recover it (if it was
   //summary only), write out a placeholder of silence data (missing
   //.au) or mark the blockfile to deal some other way without spewing
   //errors.
   virtual void Recover() = 0;
   /// if we've detected an on-disk problem, the user opted to
   //continue and the error persists, don't keep reporting it.  The
   //Object implements this functionality internally, but we want to
   //be able to tell the logging to shut up from outside too.
   void SilenceLog() { mSilentLog = TRUE; }


 private:

   friend class DirManager;

   virtual void Ref();
   virtual bool Deref();

 protected:
   /// Calculate summary data for the given sample data
   virtual void *CalcSummary(samplePtr buffer, sampleCount len,
                             sampleFormat format);
   /// Read the summary section of the file.  Derived classes implement.
   virtual bool ReadSummary(void *data) = 0;

   /// Byte-swap the summary data, in case it was saved by a system
   /// on a different platform
   virtual void FixSummary(void *data);

 private:
   int mLockCount;
   int mRefCount;

   static char *fullSummary;

 protected:
   wxFileName mFileName;
   sampleCount mLen;
   SummaryInfo mSummaryInfo;
   float mMin, mMax, mRMS;
   bool mSilentLog;
};

/// A BlockFile that refers to data in an existing file

/// An AliasBlockFile references an existing disk file for its storage
/// instead of copying the data.  It still writes a file to disk, but
/// only stores summary data in it.
///
/// This is a common base class for all alias block files.  It handles
/// reading and writing summary data, leaving very little for derived
/// classes to need to implement.
class AliasBlockFile : public BlockFile
{
 public:

   // Constructor / Destructor

   /// Constructs an AliasBlockFile
   AliasBlockFile(wxFileName baseFileName,
                  wxFileName aliasedFileName, sampleCount aliasStart,
                  sampleCount aliasLen, int aliasChannel);
   AliasBlockFile(wxFileName existingSummaryFile,
                  wxFileName aliasedFileName, sampleCount aliasStart,
                  sampleCount aliasLen, int aliasChannel,
                  float min, float max, float RMS);
   virtual ~AliasBlockFile();

   // Reading

   /// Retrieves audio data from the aliased file.
   virtual int ReadData(samplePtr data, sampleFormat format,
                        sampleCount start, sampleCount len) = 0;

   virtual wxLongLong GetSpaceUsage();

   /// as SilentLog (which would affect Summary data access), but
   // applying to Alias file access
   void SilenceAliasLog() { mSilentAliasLog = TRUE; }


   //
   // These methods are for advanced use only!
   //

   /// Gets the name of the aliased file.
   wxFileName GetAliasedFile();
   /// Modifies the name of the aliased file.
   void ChangeAliasedFile(wxFileName newAliasedFile);
   /// Returns TRUE if this is an AliasBlockFile
   bool IsAlias() { return true; }

 protected:
   /// Write the summary to disk, using the derived ReadData() to get the data
   virtual void WriteSummary();
   /// Read the summary into a buffer
   virtual bool ReadSummary(void *data);

   wxFileName  mAliasedFileName;
   sampleCount mAliasStart;
   int         mAliasChannel;
   bool        mSilentAliasLog;
};

#endif


// Indentation settings for Vim and Emacs and unique identifier for Arch, a
// version control system. Please do not modify past this point.
//
// Local Variables:
// c-basic-offset: 3
// indent-tabs-mode: nil
// End:
//
// vim: et sts=3 sw=3
// arch-tag: ebcc7075-5983-4092-a316-1f2e2b0bcbc3


