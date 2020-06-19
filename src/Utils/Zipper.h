/*!
 * \file	Zipper.h
 *
 * \author	ZhengYuanQing
 * \date	2020/06/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ZIPPER_H__AEBA8259_8E43_4DEF_B112_6C8ABB412AFC
#define ZIPPER_H__AEBA8259_8E43_4DEF_B112_6C8ABB412AFC

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Zipper
{
private:
    struct Private;

public:
    struct Entry
    {
		std::string name;
		XE::uint64 compressed_size = 0;
		XE::uint64 uncompressed_size = 0;
    };

public:
    Zipper();

	Zipper( std::iostream & buffer );

	Zipper( const std::string & zipname, const std::string & password = "" );

    ~Zipper();

public:
	bool Add( std::istream & source, const std::string & name );

public:
    XE::Array< Entry > GetEntries() const;

    bool ExtractEntiy( const std::string & name );

	void GetEntryData( const Entry & entry, std::ostream & stream );

	void GetEntryData( const std::string & entry_name, std::ostream & stream );

public:
    bool Open( std::iostream & buffer );

    bool Open( const std::string & zipname, const std::string & password = "" );

    bool IsOpen() const;

public:
    void Flush();

	void Close();

private:
    Private * _p;
};

END_XE_NAMESPACE

#endif // ZIPPER_H__AEBA8259_8E43_4DEF_B112_6C8ABB412AFC
