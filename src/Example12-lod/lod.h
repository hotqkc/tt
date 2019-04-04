
#ifndef LOD_H_DC8C8E2F5FF1CD11F91286184C879E21
#define LOD_H_DC8C8E2F5FF1CD11F91286184C879E21

#include <stdint.h>  // int32_t

#include <sxbTop/defines.h>

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

class lod
{
public:
	lod() {};
	~lod() {};

public:
	void init(void* nwh_);

	void update(const uint64_t & frame_);

};

#endif // LOD_H_DC8C8E2F5FF1CD11F91286184C879E21