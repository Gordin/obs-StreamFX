// AUTOGENERATED COPYRIGHT HEADER START
// Copyright (C) 2019-2023 Michael Fabian 'Xaymar' Dirks <info@xaymar.com>
// AUTOGENERATED COPYRIGHT HEADER END

#pragma once
#include "common.hpp"
#include "gfx-blur-base.hpp"
#include "gfx/gfx-util.hpp"
#include "obs/gs/gs-effect.hpp"
#include "obs/gs/gs-rendertarget.hpp"
#include "obs/gs/gs-texture.hpp"

#include "warning-disable.hpp"
#include <mutex>
#include "warning-enable.hpp"

namespace streamfx::gfx {
	namespace blur {
		class box_data {
			streamfx::obs::gs::effect            _effect;
			std::shared_ptr<streamfx::gfx::util> _gfx_util;

			public:
			box_data();
			virtual ~box_data();

			std::shared_ptr<streamfx::gfx::util> get_gfx_util();

			streamfx::obs::gs::effect get_effect();
		};

		class box_factory : public ::streamfx::gfx::blur::ifactory {
			std::mutex                                     _data_lock;
			std::weak_ptr<::streamfx::gfx::blur::box_data> _data;

			public:
			box_factory();
			virtual ~box_factory() override;

			virtual bool is_type_supported(::streamfx::gfx::blur::type type) override;

			virtual std::shared_ptr<::streamfx::gfx::blur::base> create(::streamfx::gfx::blur::type type) override;

			virtual double_t get_min_size(::streamfx::gfx::blur::type type) override;

			virtual double_t get_step_size(::streamfx::gfx::blur::type type) override;

			virtual double_t get_max_size(::streamfx::gfx::blur::type type) override;

			virtual double_t get_min_angle(::streamfx::gfx::blur::type type) override;

			virtual double_t get_step_angle(::streamfx::gfx::blur::type type) override;

			virtual double_t get_max_angle(::streamfx::gfx::blur::type type) override;

			virtual bool is_step_scale_supported(::streamfx::gfx::blur::type type) override;

			virtual double_t get_min_step_scale_x(::streamfx::gfx::blur::type type) override;

			virtual double_t get_step_step_scale_x(::streamfx::gfx::blur::type type) override;

			virtual double_t get_max_step_scale_x(::streamfx::gfx::blur::type type) override;

			virtual double_t get_min_step_scale_y(::streamfx::gfx::blur::type type) override;

			virtual double_t get_step_step_scale_y(::streamfx::gfx::blur::type type) override;

			virtual double_t get_max_step_scale_y(::streamfx::gfx::blur::type type) override;

			std::shared_ptr<::streamfx::gfx::blur::box_data> data();

			public: // Singleton
			static ::streamfx::gfx::blur::box_factory& get();
		};

		class box : public ::streamfx::gfx::blur::base {
			protected:
			std::shared_ptr<::streamfx::gfx::blur::box_data> _data;

			double_t                                           _size;
			std::pair<double_t, double_t>                      _step_scale;
			std::shared_ptr<::streamfx::obs::gs::texture>      _input_texture;
			std::shared_ptr<::streamfx::obs::gs::rendertarget> _rendertarget;

			private:
			std::shared_ptr<::streamfx::obs::gs::rendertarget> _rendertarget2;

			public:
			box();
			virtual ~box() override;

			virtual void set_input(std::shared_ptr<::streamfx::obs::gs::texture> texture) override;

			virtual ::streamfx::gfx::blur::type get_type() override;

			virtual double_t get_size() override;
			virtual void     set_size(double_t width) override;

			virtual void     set_step_scale(double_t x, double_t y) override;
			virtual void     get_step_scale(double_t& x, double_t& y) override;
			virtual double_t get_step_scale_x() override;
			virtual double_t get_step_scale_y() override;

			virtual std::shared_ptr<::streamfx::obs::gs::texture> render() override;
			virtual std::shared_ptr<::streamfx::obs::gs::texture> get() override;
		};

		class box_directional : public ::streamfx::gfx::blur::box, public ::streamfx::gfx::blur::base_angle {
			double_t _angle;

			public:
			box_directional();

			virtual ::streamfx::gfx::blur::type get_type() override;

			virtual double_t get_angle() override;
			virtual void     set_angle(double_t angle) override;

			virtual std::shared_ptr<::streamfx::obs::gs::texture> render() override;
		};

		class box_rotational : public ::streamfx::gfx::blur::box,
							   public ::streamfx::gfx::blur::base_angle,
							   public ::streamfx::gfx::blur::base_center {
			std::pair<double_t, double_t> _center;
			double_t                      _angle;

			public:
			virtual ::streamfx::gfx::blur::type get_type() override;

			virtual void set_center(double_t x, double_t y) override;
			virtual void get_center(double_t& x, double_t& y) override;

			virtual double_t get_angle() override;
			virtual void     set_angle(double_t angle) override;

			virtual std::shared_ptr<::streamfx::obs::gs::texture> render() override;
		};

		class box_zoom : public ::streamfx::gfx::blur::box, public ::streamfx::gfx::blur::base_center {
			std::pair<double_t, double_t> _center;

			public:
			virtual ::streamfx::gfx::blur::type get_type() override;

			virtual void set_center(double_t x, double_t y) override;
			virtual void get_center(double_t& x, double_t& y) override;

			virtual std::shared_ptr<::streamfx::obs::gs::texture> render() override;
		};
	} // namespace blur
} // namespace streamfx::gfx
