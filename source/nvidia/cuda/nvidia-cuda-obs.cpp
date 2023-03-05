// AUTOGENERATED COPYRIGHT HEADER START
// Copyright (C) 2021-2023 Michael Fabian 'Xaymar' Dirks <info@xaymar.com>
// AUTOGENERATED COPYRIGHT HEADER END

#include "nvidia-cuda-obs.hpp"
#include "obs/gs/gs-helper.hpp"
#include "util/util-logging.hpp"

#ifdef _DEBUG
#define ST_PREFIX "<%s> "
#define D_LOG_ERROR(x, ...) P_LOG_ERROR(ST_PREFIX##x, __FUNCTION_SIG__, __VA_ARGS__)
#define D_LOG_WARNING(x, ...) P_LOG_WARN(ST_PREFIX##x, __FUNCTION_SIG__, __VA_ARGS__)
#define D_LOG_INFO(x, ...) P_LOG_INFO(ST_PREFIX##x, __FUNCTION_SIG__, __VA_ARGS__)
#define D_LOG_DEBUG(x, ...) P_LOG_DEBUG(ST_PREFIX##x, __FUNCTION_SIG__, __VA_ARGS__)
#else
#define ST_PREFIX "<nvidia::cuda::obs> "
#define D_LOG_ERROR(...) P_LOG_ERROR(ST_PREFIX __VA_ARGS__)
#define D_LOG_WARNING(...) P_LOG_WARN(ST_PREFIX __VA_ARGS__)
#define D_LOG_INFO(...) P_LOG_INFO(ST_PREFIX __VA_ARGS__)
#define D_LOG_DEBUG(...) P_LOG_DEBUG(ST_PREFIX __VA_ARGS__)
#endif

streamfx::nvidia::cuda::obs::~obs()
{
	D_LOG_DEBUG("Finalizing... (Addr: 0x%" PRIuPTR ")", this);

	auto gctx = streamfx::obs::gs::context{};
	{
		auto stack = _context->enter();
		_stream->synchronize();
		_context->synchronize();
		_stream.reset();
	}
	_context.reset();
	_cuda.reset();
}

streamfx::nvidia::cuda::obs::obs() : _cuda(::streamfx::nvidia::cuda::cuda::get()), _context()
{
	D_LOG_DEBUG("Initializating... (Addr: 0x%" PRIuPTR ")", this);

	auto gctx = streamfx::obs::gs::context{};

	// Create Context
#ifdef WIN32
	if (gs_get_device_type() == GS_DEVICE_DIRECT3D_11) {
		_context =
			std::make_shared<::streamfx::nvidia::cuda::context>(reinterpret_cast<ID3D11Device*>(gs_get_device_obj()));
	}
#endif
	if (gs_get_device_type() == GS_DEVICE_OPENGL) {
		throw std::runtime_error("Not yet implemented.");
	}

	// Create Stream
	auto stack = _context->enter();
	_stream    = std::make_shared<::streamfx::nvidia::cuda::stream>();
}

std::shared_ptr<streamfx::nvidia::cuda::obs> streamfx::nvidia::cuda::obs::get()
{
	static std::weak_ptr<streamfx::nvidia::cuda::obs> instance;
	static std::mutex                                 lock;

	std::unique_lock<std::mutex> ul(lock);
	if (instance.expired()) {
		std::shared_ptr<streamfx::nvidia::cuda::obs> hard_instance;
		hard_instance = std::make_shared<streamfx::nvidia::cuda::obs>();
		instance      = hard_instance;
		return hard_instance;
	}
	return instance.lock();
}

std::shared_ptr<streamfx::nvidia::cuda::cuda> streamfx::nvidia::cuda::obs::get_cuda()
{
	return _cuda;
}

std::shared_ptr<streamfx::nvidia::cuda::context> streamfx::nvidia::cuda::obs::get_context()
{
	return _context;
}

std::shared_ptr<streamfx::nvidia::cuda::stream> streamfx::nvidia::cuda::obs::get_stream()
{
	return _stream;
}
