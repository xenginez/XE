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

	Zipper( std::ostream & stream );

    ~Zipper();

public:
	bool AddEntiy( const XE::String & name, std::istream & source );

public:
    bool Open( std::ostream & stream );

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

	Unzipper( std::istream & stream );

	~Unzipper();

public:
	void GetEntries( XE::Array< XE::String > & entries ) const;

	bool ExtractEntiy( const XE::String & name );

	bool GetEntryData( const XE::String & name, std::ostream & stream );

public:
	bool Open( std::istream & stream );

	bool IsOpen() const;

public:
	void Close();

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // ZIPPER_H__AEBA8259_8E43_4DEF_B112_6C8ABB412AFC
