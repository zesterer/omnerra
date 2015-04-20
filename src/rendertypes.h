#ifndef RENDERTYPES_H
#define RENDERTYPES_H

#define MAX_VERTICES 2000
#define MAX_POLYGONS 2000

namespace Omnerra
{
	namespace RenderTypes
	{
		struct VertexType
		{
			float x, y, z;
		};

		struct PolygonType
		{
			int a, b, c;
		};

		struct ObjectType
		{
			VertexType vertex[MAX_VERTICES];
			PolygonType polygon[MAX_POLYGONS];
		};
	}
}

#endif
