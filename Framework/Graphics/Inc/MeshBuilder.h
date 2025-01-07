#pragma once
#include "MeshTypes.h"

namespace ENgines::Graphics
{
	class MeshBuilder
	{
	public:
		static MeshPC CreateCubePC(float size);
		static MeshPX CreateCubePX(float size);

		static MeshPX CreateSkyboxPX(float size);
		static MeshPX CreateSkySpherePX(int slices, int rings, float radius);
		static MeshPC CreateRectPC(float width, float length, float height);

		static MeshPC CreatePlanePC(int numRows, int numCols, float spacing);
		static MeshPX CreatePlanePX(int numRows, int numCols, float spacing);
		static Mesh CreateGroundPlane(int numRows, int numCols, float spacing);
		static MeshPC CreateCylinderPC(int slices, int rings);

		static MeshPC CreateSpherePC(int slices, int rings, float radius);
		static MeshPX CreateSpherePX(int slices, int rings, float radius);
		static Mesh CreateSphere(int slices, int rings, float radius);

		static MeshPX CreateScreenQuad();

		static MeshPX CreateSpriteQuad(float width, float height);
	};
}