
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>
#include <bx/readerwriter.h>
#include <sxbCommon/utils.h>
#include "cube.h"

static const uint64_t s_ptState[]
{
	UINT64_C(0),
	BGFX_STATE_PT_TRISTRIP,
	BGFX_STATE_PT_LINES,
	BGFX_STATE_PT_LINESTRIP,
	BGFX_STATE_PT_POINTS,
};

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
	};

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorVertex::ms_decl;

static PosColorVertex s_cubeVertices[] =
{
	{-1.0f,  1.0f,  1.0f, 0xff0000ff },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff0000ff },
	{ 1.0f, -1.0f,  1.0f, 0xff0000ff },
	{-1.0f,  1.0f, -1.0f, 0xff0000ff },
	{ 1.0f,  1.0f, -1.0f, 0xff0000ff },
	{-1.0f, -1.0f, -1.0f, 0xff0000ff },
	{ 1.0f, -1.0f, -1.0f, 0xff0000ff },
};

static PosColorVertex s_coorVertices[] =
{
	{1000.0f,  0.0f,  0.0f, 0xff0000ff },
	{-1000.0f,  0.0f,  0.0f, 0xff00ff00 },
	 {0.0f,  1000.0f,  0.0f, 0xff0000ff },
	 {0.0f,  -1000.0f,  0.0f, 0xff0000ff },
	 {0.0f,  0.0f,  1000.0f, 0xff0000ff },
	 {0.0f,  0.0f,  -1000.0f, 0xff0000ff },
};

static const uint16_t s_coorList[] =
{
	0, 1,
	2, 3,
	4, 5,
};

static const uint16_t s_cubeTriList[] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

static const uint16_t s_cubeLineList[] =
{
	0, 1,
	0, 2,
	0, 4,
	1, 3,
	1, 5,
	2, 3,
	2, 6,
	3, 7,
	4, 5,
	4, 6,
	5, 7,
	6, 7,
};

static const uint16_t s_cubePoints[] =
{
	0, 1, 2, 3, 4, 5, 6, 7
};

bool Cube::init(void* nwh_)
{
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
		, 0x000000FF
		, 1.0f
		, 0
	);

	bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

	m_ready = sxb::Utils::loadProgram("vs_stencil_color_lighting.bin", "fs_stencil_color_lighting.bin", m_program);
	m_ready &= sxb::Utils::loadProgram("vs_cubes.bin", "fs_cubes.bin", m_program_cube);

	m_bunnyMesh.load("meshes/bunny.bin");

	bgfx::VertexDecl pcvDecl;
	pcvDecl.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();
	m_vbh[0] = bgfx::createVertexBuffer(bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices)), pcvDecl);
	m_vbh[1] = bgfx::createVertexBuffer(bgfx::makeRef(s_coorVertices, sizeof(s_coorVertices)), pcvDecl);

	m_ibh[0] = bgfx::createIndexBuffer(
		bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList))
	);

	m_ibh[1] = bgfx::createIndexBuffer(
		bgfx::makeRef(s_cubeLineList, sizeof(s_cubeLineList))
	);

	m_ibh[2] = bgfx::createIndexBuffer(
		bgfx::makeRef(s_cubePoints, sizeof(s_cubePoints))
	);

	m_ibh[3] = bgfx::createIndexBuffer(
		bgfx::makeRef(s_coorList, sizeof(s_coorList))
	);

	m_coordMesh.load(s_coorVertices, sizeof(s_coorVertices), pcvDecl, s_coorList, sizeof(s_coorList));

	return m_ready;
}

void Cube::update(const uint64_t & frame_)
{
	if (m_ready)
	{
		float bunnyMtx[16];
		bx::mtxSRT(bunnyMtx
			, 5.0f
			, 5.0f
			, 5.0f
			, 0.0f
			, 1.56f
			, 0.0f
			, 0.0f
			, 2.0f
			, 0.0f
		);

		bgfx::touch(0);

		bgfx::dbgTextPrintf(0, 1, 0x0f, "                                                      ");
		bgfx::dbgTextPrintf(0, 2, 0x0f, "                                                      ");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "                                                      ");
		bgfx::dbgTextPrintf(0, 4, 0x0f, "                                                      ");
		bgfx::dbgTextPrintf(0, 5, 0x0f, "                                                      ");

		bgfx::dbgTextPrintf(0, 1, 0x0f, "(%d, %d)", m_mouseX, m_mouseY);
		bgfx::dbgTextPrintf(0, 2, 0x0f, "(%d, %d)", m_deltaX, m_deltaY);
		bgfx::dbgTextPrintf(0, 3, 0x0f, "at: (%.2f, %.2f, %.2f)", m_atX, m_atY, m_atZ);
		bgfx::dbgTextPrintf(0, 4, 0x0f, "eye: (%.2f, %.2f, %.2f)", m_eyeX, m_eyeY, m_eyeZ);
		bgfx::dbgTextPrintf(0, 5, 0x0f, "key: %d", m_key);

		bgfx::dbgTextPrintf(0, 10, 0x0f, m_dbgText.c_str());

		const bx::Vec3 at = { 2.0f + m_atX, 4.0f + m_atY,  m_atZ };
		const bx::Vec3 eye = { -13.0f + m_eyeX,  m_eyeY,  m_eyeZ };

		{
			float view[16];
			bx::mtxLookAt(view, eye, at);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
			bgfx::setViewTransform(0, view, proj);
		}

		m_bunnyMesh.submit(0, m_program, bunnyMtx, BGFX_STATE_DEFAULT);

		float mtx[16];
		bx::mtxRotateXY(mtx, 0.0f, 0.0f);
		m_coordMesh.submit(0, m_program_cube, NULL, BGFX_STATE_DEFAULT | BGFX_STATE_PT_LINES);
		//sxb::Submit(0, m_program_cube, m_vbh[1], m_ibh[3], BGFX_STATE_DEFAULT | BGFX_STATE_PT_LINES);

		bgfx::frame();
	}
}