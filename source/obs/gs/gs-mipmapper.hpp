// AUTOGENERATED COPYRIGHT HEADER START
// Copyright (C) 2019-2023 Michael Fabian 'Xaymar' Dirks <info@xaymar.com>
// AUTOGENERATED COPYRIGHT HEADER END

#pragma once
#include "common.hpp"
#include "gfx/gfx-util.hpp"
#include "gs-effect.hpp"
#include "gs-rendertarget.hpp"
#include "gs-texture.hpp"
#include "gs-vertexbuffer.hpp"

/* gs::mipmapper is an attempt at adding dynamic mip-map generation to a software
 *  which only supports static mip-maps. It is effectively an incredibly bad hack
 *  instead of a proper solution - can break any time and likely already has.
 *
 * Needless to say, dynamic mip-map generation costs a lot of GPU time, especially
 *  when things need to be synchronized. In the ideal case we would just render 
 *  straight to the mip level, but this is not possible in DirectX 11 and OpenGL.
 * 
 * So instead we render to a render target and copy from there to the actual
 *  resource. Super wasteful, but what else can we actually do?
 */

namespace streamfx::obs::gs {
	class mipmapper {
		std::unique_ptr<streamfx::obs::gs::rendertarget> _rt;
		streamfx::obs::gs::effect                        _effect;
		std::shared_ptr<streamfx::gfx::util>             _gfx_util;

		public:
		~mipmapper();
		mipmapper();

		uint32_t calculate_max_mip_level(uint32_t width, uint32_t height);

		void rebuild(std::shared_ptr<streamfx::obs::gs::texture> source,
					 std::shared_ptr<streamfx::obs::gs::texture> target);
	};
} // namespace streamfx::obs::gs
