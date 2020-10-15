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
    Zipper();

	Zipper( const std::string & zipname );

    ~Zipper();

public:
	bool Add( std::istream & source, const std::string & name, const std::string & password = "" );

public:
    bool Open( const std::string & zipname );

    bool IsOpen() const;

public:
	void Close();

private:
    Private * _p;
};

class XE_API Unzipper
{
	struct Private;

public:
	Unzipper();

	Unzipper( const std::string & zipname );

	~Unzipper();

public:
	bool GetEntries( XE::Array< std::string > & entries ) const;

	bool ExtractEntiy( const std::string & name );

	bool GetEntryData( const std::string & name, std::ostream & stream, const std::string & password = "" );

public:
	bool Open( const std::string & zipname );

	bool IsOpen() const;

public:
	void Close();

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // ZIPPER_H__AEBA8259_8E43_4DEF_B112_6C8ABB412AFC
