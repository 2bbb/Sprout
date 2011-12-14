#ifndef SPROUT_DARKROOM_MATERIALS_MATERIAL_HPP
#define SPROUT_DARKROOM_MATERIALS_MATERIAL_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/darkroom/access/access.hpp>
#include <sprout/darkroom/colors/rgb.hpp>

namespace sprout {
	namespace darkroom {
		namespace materials {
			//
			// color
			// reflection
			//
			template<typename T>
			SPROUT_CONSTEXPR auto color(
				T&& t
				) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<0>(sprout::forward<T>(t))))
				-> decltype(sprout::darkroom::access::get<0>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<0>(sprout::forward<T>(t));
			}
			template<typename T>
			SPROUT_CONSTEXPR auto reflection(
				T&& t
				) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<1>(sprout::forward<T>(t))))
				-> decltype(sprout::darkroom::access::get<1>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<1>(sprout::forward<T>(t));
			}

			//
			// calc_color
			// calc_reflection
			//
			template<typename Image, typename Unit>
			SPROUT_CONSTEXPR auto calc_color(Image&& t, Unit const& u, Unit const& v) SPROUT_NOEXCEPT
				-> decltype(sprout::forward<Image>(t).template operator()(u, v))
			{
				return sprout::forward<Image>(t).template operator()(u, v);
			}
			template<typename Image, typename Unit>
			SPROUT_CONSTEXPR auto calc_reflection(Image&& t, Unit const& u, Unit const& v) SPROUT_NOEXCEPT
				-> decltype(sprout::forward<Image>(t).template operator()(u, v))
			{
				return sprout::forward<Image>(t).template operator()(u, v);
			}

			//
			// calc_material
			//
			template<typename Material, typename Unit>
			SPROUT_CONSTEXPR auto calc_material(Material const& mat, Unit const& u, Unit const& v)
				-> decltype(sprout::tuples::make_tuple(
					sprout::darkroom::materials::calc_color(sprout::darkroom::materials::color(mat), u, v),
					sprout::darkroom::materials::calc_reflection(sprout::darkroom::materials::reflection(mat), u, v)
					))
			{
				return sprout::tuples::make_tuple(
					sprout::darkroom::materials::calc_color(sprout::darkroom::materials::color(mat), u, v),
					sprout::darkroom::materials::calc_reflection(sprout::darkroom::materials::reflection(mat), u, v)
					);
			}

			//
			// make_material_image
			//
			template<typename ColorImage, typename ReflectionImage>
			SPROUT_CONSTEXPR sprout::tuples::tuple<ColorImage, ReflectionImage>
			make_material_image(ColorImage const& col, ReflectionImage const& ref) {
				return sprout::tuples::make_tuple(col, ref);
			}

			//
			// material
			//
			typedef sprout::tuples::tuple<sprout::darkroom::colors::rgb_f, double> material;
		}	// namespace materials
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_MATERIALS_MATERIAL_HPP
