#ifndef SHAPE_H
#define SHAPE_H

namespace oj
{
	class Shape3D
	{	
		double volume;

	public:
		double getVolume();
	
	protected:
		void setVolume(double volume);
	};

	class Sphere : public Shape3D
	{
		double radius;
		double pi;
	
	public:
		Sphere(double, double);
	};

	class Cone : public Shape3D
	{
		double radius;
		double height;
		double pi;

	public:
		Cone(double, double, double);
	};

	class Cuboid : public Shape3D
	{
		double length;
		double width;
		double height;
	
	public:
		Cuboid(double, double, double);
	};

	class Cube : public Cuboid
	{
	public:
		Cube(double);
	};
}


#endif
