
#ifndef STENCIL_H_B874E9B544F90998EF3FC1D95074912E
#define STENCIL_H_B874E9B544F90998EF3FC1D95074912E


#include <stdint.h>  // int32_t

#include <bgfx/bgfx.h>
#include <bgfx/bgfx_utils.h>

#include <sxbTop/defines.h>
#include <sxbCommon/Mesh.h>

struct KnightPos
{
	int32_t m_x;
	int32_t m_y;
};

static const KnightPos knightTour[8 * 4] =
{
	{0,0}, {1,2}, {3,3}, {4,1}, {5,3}, {7,2}, {6,0}, {5,2},
	{7,3}, {6,1}, {4,0}, {3,2}, {2,0}, {0,1}, {1,3}, {2,1},
	{0,2}, {1,0}, {2,2}, {0,3}, {1,1}, {3,0}, {4,2}, {5,0},
	{7,1}, {6,3}, {5,1}, {7,0}, {6,2}, {4,3}, {3,1}, {2,3},
};

class stencil
{
public:
	stencil(): m_ready(false) {}
	~stencil()
	{
		bgfx::shutdown();
	}

public:
	bool init(void* nwh_);

	void update(const uint64_t & frame_ = 0);

private:
	bool m_ready;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	sxb::Mesh* m_bunnyMesh;

	bgfx::ProgramHandle m_program;
	bgfx::ProgramHandle m_programShadow;
};

#endif // STENCIL_H_B874E9B544F90998EF3FC1D95074912E