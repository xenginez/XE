/*!
 * \file	Shape.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/07
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SHAPE_H__888F3A03_457E_43C2_9762_4007ECABA020
#define SHAPE_H__888F3A03_457E_43C2_9762_4007ECABA020

#include "PhysicsObject.h"

BEG_XE_NAMESPACE

class PHYSICS_API Shape : public XE::PhysicsObject
{
	OBJECT( Shape, PhysicsObject )

public:
	Shape();

	~Shape() override;
};

END_XE_NAMESPACE

#endif // SHAPE_H__888F3A03_457E_43C2_9762_4007ECABA020
