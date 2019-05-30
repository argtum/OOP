#include "pch.h"
#include "lw4/GeometricFigures/CCircle.h"
#include "lw4/GeometricFigures/CPoint.h"

TEST_CASE("The circle when created should have a perimeter, area, center and radius", "[CCircle]")
{
	GIVEN("LineSegment defined two points")
	{
		CPoint point1(1.2, 3.4);

		WHEN("Created circle of line color #123456 and fillcolor #987654")
		{
			CCircle circle("Circle", point1, 3, 123456, 987654);

			THEN("Can get type")
			{
				CHECK(circle.GetType() == "Circle");
			}
			AND_THEN("Can get center point")
			{
				CHECK(circle.GetCenter().GetX() == 1.2);
				CHECK(circle.GetCenter().GetY() == 3.4);
			}
			AND_THEN("Can get radius")
			{
				CHECK(circle.GetRadius() == 3);
			}
			AND_THEN("Can get perimeter")
			{
				CHECK(round(circle.GetPerimeter() * 100) / 100 == 18.85);
			}
			AND_THEN("Can get area")
			{
				CHECK(round(circle.GetArea() * 100) / 100 == 28.27);
			}
			AND_THEN("Can get line color")
			{
				CHECK(circle.GetOutlineColor() == 123456);
			}
			AND_THEN("Can get fill color")
			{
				CHECK(circle.GetFillColor() == 987654);
			}
		}
	}
}

TEST_CASE("CCircle - create a circle", "[CCircle]")
{
	GIVEN("Circle center point")
	{
		CPoint center(1.2, 3.4);

		WHEN("Created circle with radius 3, line color #123456 and fill color #987654")
		{
			CCircle circle("Circle", center, 3, 123456, 987654);

			THEN("Can get all parameters of segment")
			{
				CHECK(circle.ToString() == "Circle:\n\tcenter = ( 1.2 , 3.4 ), radius = 3\n\tperimeter = 18.85\n\tarea = 28.27\n\tline color = 123456\n\tfill color = 987654\n");
			}
		}
	}
}
