#define _CRT_SECURE_NO_WARNINGS

#include "MeshLoader.h"
#include "SignedDistance.h"
#include "Visualize.h"
#include <boost/gil/extension/io/pnm.hpp>

using namespace std;
using namespace MeshSdf;

// NOTE: argv[1] should contain path to mesh in obj format.
int main(int argc, char* argv[])
{
	if (argc <= 1) return -1;

	auto mesh = LoadObj(argv[1]);

	SignedDistance df{ mesh };
	//UnsignedDistance df{ mesh.verts, mesh.tris };

	auto boundBox = Scale(BoundingBox(mesh), 1.3f);
	auto aspectRatio = (boundBox.ymax - boundBox.ymin) / (boundBox.xmax - boundBox.xmin);
	auto const ImWidth = 1500;
	auto const ImHeight = static_cast<int>(aspectRatio * ImWidth);
	auto const DepthPercent = 0.5f;
	auto imgSlice = ColorCodedSlice(df, ImHeight, ImWidth, boundBox, DepthPercent);

	write_view("sdf_slice.ppm", const_view(imgSlice), boost::gil::pnm_tag{});
}
