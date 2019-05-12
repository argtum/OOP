#pragma once
#include "pch.h"
#include "CPoint.h"
#include "ISolidShape.h"
class CRectangle : public ISolidShape
{
public:
	CRectangle(const std::string& type, const CPoint& leftTop, const CPoint& rightBottom, const double width, const double height, const uint32_t lineColor, const uint32_t fillColor);
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	double GetArea() const override;
	uint32_t GetFillColor() const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
	std::string GetType() const;

private:
	void AppendProperties(std::ostream& strm) const override;

	std::string m_type;
	CPoint m_leftTopVertex;
	CPoint m_rightBottomVertex;
	double m_width;
	double m_height;
	uint32_t m_lineColor;
	uint32_t m_fillColor;
};