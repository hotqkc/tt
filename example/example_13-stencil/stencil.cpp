
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>
#include <bx/readerwriter.h>
#include <sxbCommon/utils.h>
#include "stencil.h"

bool stencil::init(void* nwh_)
{
    m_ready = true;
	m_width = WNDW_WIDTH;
	m_height = WNDW_HEIGHT;
	m_debug = BGFX_DEBUG_TEXT;
	m_reset = BGFX_RESET_VSYNC;

	bgfx::PlatformData pd;
	pd.nwh = nwh_;
	bgfx::setPlatformData(pd);

	bgfx::Init bgfxInit;
	bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
	bgfxInit.resolution.width = m_width;
	bgfxInit.resolution.height = m_height;
	bgfxInit.resolution.reset = m_reset;
	bgfx::init(bgfxInit);

	bgfx::setDebug(m_debug);

	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		, 0x443355FF
		, 1.0f
		, 0
	);

	bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));
    
    m_clearValues = ClearValues(0x30303000, 1.0f, 0);
    
    bgfx::VertexDecl pcvDecl;
    pcvDecl
    .begin()
    .add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
    .add(bgfx::Attrib::Normal,    4, bgfx::AttribType::Uint8, true, true)
    .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
    .end();

    m_ready &= sxb::Utils::loadProgram("vs_stencil_texture_lighting.bin", "fs_stencil_texture_lighting.bin", m_programTextureLighting);
    m_ready &= sxb::Utils::loadProgram("vs_stencil_color_lighting.bin", "fs_stencil_color_lighting.bin", m_programColorLighting);
    m_ready &= sxb::Utils::loadProgram("vs_stencil_color_texture.bin", "fs_stencil_color_texture.bin", m_programColorTexture);
    m_ready &= sxb::Utils::loadProgram("vs_stencil_color.bin", "fs_stencil_color_black.bin", m_programColorBlack);
    m_ready &= sxb::Utils::loadProgram("vs_stencil_texture.bin", "fs_stencil_texture.bin", m_programTexture);

    m_ready &= sxb::Utils::loadTexture("textures/figure-rgba.dds", m_figureTex);
    m_ready &= sxb::Utils::loadTexture("textures/flare.dds", m_flareTex);
    m_ready &= sxb::Utils::loadTexture("textures/fieldstone-rgba.dds", m_fieldstoneTex);

    m_bunnyMesh.load("meshes/bunny.bin");
    m_columnMesh.load("meshes/column.bin");
    m_cubeMesh.load(s_cubeVertices, BX_COUNTOF(s_cubeVertices), pcvDecl, s_cubeIndices, BX_COUNTOF(s_cubeIndices) );
    m_hplaneMesh.load(s_hplaneVertices, BX_COUNTOF(s_hplaneVertices), pcvDecl, s_planeIndices, BX_COUNTOF(s_planeIndices) );
    m_vplaneMesh.load(s_vplaneVertices, BX_COUNTOF(s_vplaneVertices), pcvDecl, s_planeIndices, BX_COUNTOF(s_planeIndices) );

	return m_ready;
}

void stencil::update(const uint64_t & frame_)
{
	if (m_ready)
	{
        // Floor position.
        float floorMtx[16];
        bx::mtxSRT(floorMtx
                   , 20.0f  //scaleX
                   , 20.0f  //scaleY
                   , 20.0f  //scaleZ
                   , 0.0f   //rotX
                   , 0.0f   //rotY
                   , 0.0f   //rotZ
                   , 0.0f   //translateX
                   , 0.0f   //translateY
                   , 0.0f   //translateZ
                   );
        
        // Bunny position.
        float bunnyMtx[16];
        bx::mtxSRT(bunnyMtx
                   , 5.0f
                   , 5.0f
                   , 5.0f
                   , 0.0f
                   , 1.56f - ((float)frame_ / 30)
                   , 0.0f
                   , 0.0f
                   , 2.0f
                   , 0.0f
                   );
        
        // Columns position.
        const float dist = 14.0f;
        const float columnPositions[4][3] =
        {
            {  dist, 0.0f,  dist },
            { -dist, 0.0f,  dist },
            {  dist, 0.0f, -dist },
            { -dist, 0.0f, -dist },
        };
        
        float columnMtx[4][16];
        for (uint8_t ii = 0; ii < 4; ++ii)
        {
            bx::mtxSRT(columnMtx[ii]
                       , 1.0f
                       , 1.0f
                       , 1.0f
                       , 0.0f
                       , 0.0f
                       , 0.0f
                       , columnPositions[ii][0]
                       , columnPositions[ii][1]
                       , columnPositions[ii][2]
                       );
        }
        
        const uint8_t numCubes = 9;
        float cubeMtx[numCubes][16];
        for (uint16_t ii = 0; ii < numCubes; ++ii)
        {
            bx::mtxSRT(cubeMtx[ii]
                       , 1.0f
                       , 1.0f
                       , 1.0f
                       , 0.0f
                       , 0.0f
                       , 0.0f
                       , bx::sin(ii * 2.0f + 13.0f - ((float)frame_ / 30)) * 13.0f
                       , 4.0f
                       , bx::cos(ii * 2.0f + 13.0f - ((float)frame_ / 30)) * 13.0f
                       );
        }
        
        // Make sure at the beginning everything gets cleared.
        clearView(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, m_clearValues);
        bgfx::touch(0);
        s_viewMask |= 1;
        sxb::Utils::getMem(m_residentMem, m_virtualMem);
        
        bgfx::dbgTextPrintf(0, 5, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 7, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 5, 0x0f, "%d", frame_);
        bgfx::dbgTextPrintf(0, 7, 0x0f, "mem(resident,virtual): (%.3fm, %.3fm)", m_residentMem, m_virtualMem);

		const bx::Vec3 at = { 0.0f,  0.0f,  0.0f };
		const bx::Vec3 eye = { 10.0f,  10.0f,  -30.0f };

		{
			float view[16];
			bx::mtxLookAt(view, eye, at);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
			bgfx::setViewTransform(0, view, proj);
		}
        
        // Floor.
//        m_hplaneMesh.submit(RENDER_VIEWID_RANGE1_PASS_0
//                            , floorMtx
//                            , m_programColorBlack
//                            , s_renderStates[RenderState::StencilReflection_CraftStencil]
//                            );

		m_bunnyMesh.submit(0, m_programColorLighting, bunnyMtx, BGFX_STATE_DEFAULT);

		bgfx::frame();
	}
}
