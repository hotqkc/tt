
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>

#include <string>

#include <sxbCommon/utils.h>

#import <mach/mach.h>

#include "cube.h"

inline bool getMem(double &residentMem_, double &virtualMem_)
{
    task_basic_info_data_t taskInfo;
    mach_msg_type_number_t infoCount = TASK_BASIC_INFO_COUNT;
    kern_return_t kernReturn = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&taskInfo, &infoCount);
    residentMem_ = taskInfo.resident_size / 1024.0 / 1024.0;
    virtualMem_ = taskInfo.virtual_size / 1024.0 / 1024.0;
    
    return kernReturn == KERN_SUCCESS;
}

bool Cube::init(void *nwh_, const char *runtimePrefix_)
{
    std::string vsStr = runtimePrefix_; vsStr += "/vs_cubes.bin";
    std::string fsStr = runtimePrefix_; fsStr += "/fs_cubes.bin";
    bgfx::PlatformData pd;
    pd.nwh = nwh_;
    bgfx::setPlatformData(pd);
    
    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
    bgfxInit.resolution.width = WNDW_WIDTH;
    bgfxInit.resolution.height = WNDW_HEIGHT;
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
    bgfx::init(bgfxInit);
    
    bgfx::setDebug(BGFX_DEBUG_TEXT);
    
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, WNDW_WIDTH, WNDW_HEIGHT);
    
    bgfx::VertexDecl pcvDecl;
    pcvDecl.begin()
    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
    .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
    .end();
    m_vbh = bgfx::createVertexBuffer(bgfx::makeRef(cubeVertices, sizeof(cubeVertices)), pcvDecl);
    m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(cubeTriList, sizeof(cubeTriList)));
    
    bgfx::ShaderHandle vsh, fsh;
    
    m_ready = sxb::Utils::loadProgram_FullPath(vsStr.c_str(), fsStr.c_str(), m_program);
    

    
    return m_ready;
}

void Cube::update(const uint64_t & frame_)
{
	if (m_ready)
	{
		bgfx::touch(0);
        getMem(m_residentMem, m_virtualMem);
        
        bgfx::dbgTextPrintf(0, 5, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 7, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 5, 0x0f, "%d", frame_);
        bgfx::dbgTextPrintf(0, 7, 0x0f, "mem(resident,virtual): (%.3fm, %.3fm)", m_residentMem, m_virtualMem);

		const bx::Vec3 at = { 0.0f, 0.0f,  0.0f };
		const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };
		float view[16];
		bx::mtxLookAt(view, eye, at);

		float proj[16];
		bx::mtxProj(proj, 60.0f, float(WNDW_WIDTH) / float(WNDW_HEIGHT), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
		bgfx::setViewTransform(0, view, proj);
		bgfx::setVertexBuffer(0, m_vbh);
		bgfx::setIndexBuffer(m_ibh);

		float mtx[16];
		bx::mtxRotateXY(mtx, frame_ * 0.01f, frame_ * 0.01f);
		bgfx::setTransform(mtx);

		bgfx::submit(0, m_program);
		bgfx::frame();
	}
}
