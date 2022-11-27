#pragma once

#include "VIBuffer.h"

class CTriangle : public CVIBuffer
{
public:
	explicit CTriangle();
	virtual ~CTriangle();
public:
	virtual HRESULT Initalize() override;
};

