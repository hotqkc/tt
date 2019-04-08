
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>
#include <bx/readerwriter.h>
#include <sxbCommon/utils.h>
#include "stencil.h"

void mtxReflected(float* _result, const bx::Vec3& _pos, const bx::Vec3& _normal)
{
	const float nx = _normal.x;
	const float ny = _normal.y;
	const float nz = _normal.z;

	_result[0] = 1.0f - 2.0f * nx * nx;
	_result[1] = -2.0f * nx * ny;
	_result[2] = -2.0f * nx * nz;
	_result[3] = 0.0f;

	_result[4] = -2.0f * nx * ny;
	_result[5] = 1.0f - 2.0f * ny * ny;
	_result[6] = -2.0f * ny * nz;
	_result[7] = 0.0f;

	_result[8] = -2.0f * nx * nz;
	_result[9] = -2.0f * ny * nz;
	_result[10] = 1.0f - 2.0f * nz * nz;
	_result[11] = 0.0f;

	const float dot = bx::dot(_pos, _normal);

	_result[12] = 2.0f * dot * nx;
	_result[13] = 2.0f * dot * ny;
	_result[14] = 2.0f * dot * nz;
	_result[15] = 1.0f;
}

void mtxShadow(float* _result, const float* _ground, const float* _light)
{
	const float dot =
		_ground[0] * _light[0]
		+ _ground[1] * _light[1]
		+ _ground[2] * _light[2]
		+ _ground[3] * _light[3]
		;

	_result[0] = dot - _light[0] * _ground[0];
	_result[1] = 0.0f - _light[1] * _ground[0];
	_result[2] = 0.0f - _light[2] * _ground[0];
	_result[3] = 0.0f - _light[3] * _ground[0];

	_result[4] = 0.0f - _light[0] * _ground[1];
	_result[5] = dot - _light[1] * _ground[1];
	_result[6] = 0.0f - _light[2] * _ground[1];
	_result[7] = 0.0f - _light[3] * _ground[1];

	_result[8] = 0.0f - _light[0] * _ground[2];
	_result[9] = 0.0f - _light[1] * _ground[2];
	_result[10] = dot - _light[2] * _ground[2];
	_result[11] = 0.0f - _light[3] * _ground[2];

	_result[12] = 0.0f - _light[0] * _ground[3];
	_result[13] = 0.0f - _light[1] * _ground[3];
	_result[14] = 0.0f - _light[2] * _ground[3];
	_result[15] = dot - _light[3] * _ground[3];
}

bool stencil::init(void* nwh_)
{
	m_width = WNDW_WIDTH;
	m_height = WNDW_HEIGHT;
	m_debug = BGFX_DEBUG_NONE;
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

	m_ready = sxb::Utils::loadProgram("vs_stencil_color_lighting.bin", "fs_stencil_color_lighting.bin", m_program);
	m_ready &= sxb::Utils::loadProgram("vs_stencil_color.bin", "fs_stencil_color_black.bin", m_programShadow);

	m_bunnyMesh = sxb::meshLoad("meshes/bunny.bin");

	return m_ready;
}

void stencil::update(const uint64_t & frame_)
{
	if (m_ready)
	{
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

		bgfx::touch(0);

		const bx::Vec3 at = { 0.0f,  0.0f,  0.0f };
		const bx::Vec3 eye = { 10.0f,  10.0f,  -30.0f };

		{
			float view[16];
			bx::mtxLookAt(view, eye, at);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
			bgfx::setViewTransform(0, view, proj);
		}

		// Ground plane.
		float ground[4] = { 0.0f, 1.0f, 0.0f, -bx::dot(bx::Vec3{ 0.0f, 0.0f, 0.0f }, bx::Vec3{ 0.0f, 1.0f, 0.0f }) - 0.01f };
		
		float lightPosRadius[5][4];
		const float radius = (true) ? 15.0f : 25.0f;
		for (uint8_t ii = 0; ii < 5; ++ii)
		{
			lightPosRadius[ii][0] = bx::sin((((float)frame_ / 10)*1.1f + ii * 0.03f + ii * bx::kPiHalf*1.07f))*20.0f;
			lightPosRadius[ii][1] = 8.0f + (1.0f - bx::cos((((float)frame_ / 10)*1.5f + ii * 0.29f + bx::kPiHalf*1.49f)))*4.0f;
			lightPosRadius[ii][2] = bx::cos((((float)frame_ / 10)*1.3f + ii * 0.13f + ii * bx::kPiHalf*1.79f))*20.0f;
			lightPosRadius[ii][3] = radius;
		}

		float* lightPos = lightPosRadius[0];
		float pos[4];
		bx::memCopy(pos, lightPos, sizeof(float) * 3);
		pos[3] = 1.0f;

		float reflectMtx[16];
		mtxReflected(reflectMtx, { 0.0f, 0.01f, 0.0f }, { 0.0f, 1.0f, 0.0f });

		float shadowMtx[16];
		mtxShadow(shadowMtx, ground, pos);

		const uint64_t stateReflect = 0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_CULL_CW    //reflection matrix has inverted normals. using CCW instead of CW.
			| BGFX_STATE_MSAA
			;

		const uint64_t stateDrawscene = 0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_CULL_CCW
			| BGFX_STATE_MSAA
			;

		const uint64_t stateShadow = 0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE)
			| BGFX_STATE_DEPTH_TEST_EQUAL
			| BGFX_STATE_CULL_CCW
			| BGFX_STATE_MSAA
			;

		sxb::meshSubmit(m_bunnyMesh, 0, m_program, bunnyMtx, stateDrawscene);

		float mtxReflectedBunny[16]; 
		bx::mtxMul(mtxReflectedBunny, bunnyMtx, reflectMtx);
		//sxb::meshSubmit(m_bunnyMesh, 0, m_program, mtxReflectedBunny, stateDrawscene);

		float mtxShadowedBunny[16];
		bx::mtxMul(mtxShadowedBunny, bunnyMtx, shadowMtx);
		//sxb::meshSubmit(m_bunnyMesh, 0, m_programShadow, mtxShadowedBunny, stateDrawscene);

		bgfx::frame();
	}
}