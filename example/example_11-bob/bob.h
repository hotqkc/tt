
#ifndef BOB_H_BED48183122980209294F0564ECA8320
#define BOB_H_BED48183122980209294F0564ECA8320

#include <stdint.h>  // int32_t

#include <bgfx/bgfx.h>
#include <bgfx/bgfx_utils.h>

#include <sxbCommon/defines.h>
#include <sxbCommon/Mesh.h>

class Bob
{
public:
	Bob()
    : m_ready(false)
    , m_sceneTime(0.0)
    , m_mountainD(0.0)
    {};
	~Bob() {}

public:
	bool init(void* nwh_);

	void update(const uint64_t & frame_ = 0);

private:
	bool m_ready;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

    sxb::Mesh m_bunnyMesh;
    sxb::Mesh m_mountainMesh;

	bgfx::ProgramHandle m_program;
    
	bgfx::UniformHandle s_texColor;
	bgfx::UniformHandle s_texStipple;
	bgfx::UniformHandle u_stipple;

	bgfx::TextureHandle m_textureStipple;
	bgfx::TextureHandle m_textureLeafs;
	bgfx::TextureHandle m_textureBark;
    double m_sceneTime;
    double m_mountainD;
    
    double m_residentMem;
    double m_virtualMem;
};

#endif // BOB_H_BED48183122980209294F0564ECA8320
