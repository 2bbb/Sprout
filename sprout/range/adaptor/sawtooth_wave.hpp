#ifndef SPROUT_RANGE_ADAPTOR_SAWTOOTH_WAVE_HPP
#define SPROUT_RANGE_ADAPTOR_SAWTOOTH_WAVE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/sawtooth_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// sawtooth_wave_range
		//
		template<typename Value, typename Range = void>
		class sawtooth_wave_range
			: public sprout::range::range_container<
				sprout::sawtooth_iterator<Value>
			>
			, public sprout::detail::container_nosy_static_size<Range>
			, public sprout::detail::container_nosy_fixed_size<Range>
		{
		public:
			typedef Range range_type;
			typedef sprout::range::range_container<
				sprout::sawtooth_iterator<Value>
			> base_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
			typedef typename base_type::difference_type difference_type;
		public:
			sawtooth_wave_range() = default;
			sawtooth_wave_range(sawtooth_wave_range const&) = default;
			explicit SPROUT_CONSTEXPR sawtooth_wave_range(
				range_type& range,
				value_type const& frequency = 1,
				value_type const& amplitude = 1,
				value_type const& phase = 0
				)
				: base_type(
					iterator(0, frequency, amplitude, phase),
					iterator(sprout::size(range), frequency, amplitude, phase)
					)
			{}
			SPROUT_CONSTEXPR value_type const& frequency() const {
				return base_type::begin().frequency();
			}
			SPROUT_CONSTEXPR value_type const& amplitude() const {
				return base_type::begin().amplitude();
			}
			SPROUT_CONSTEXPR value_type const& phase() const {
				return base_type::begin().phase();
			}
		};

		template<typename Value>
		class sawtooth_wave_range<Value, void>
			: public sprout::range::range_container<
				sprout::sawtooth_iterator<Value>
			>
		{
		public:
			typedef sprout::range::range_container<
				sprout::sawtooth_iterator<Value>
			> base_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
			typedef typename base_type::difference_type difference_type;
		public:
			sawtooth_wave_range() = default;
			sawtooth_wave_range(sawtooth_wave_range const&) = default;
			explicit SPROUT_CONSTEXPR sawtooth_wave_range(
				value_type const& frequency = 1,
				value_type const& amplitude = 1,
				value_type const& phase = 0
				)
				: base_type(
					iterator(0, frequency, amplitude, phase),
					iterator(-1, frequency, amplitude, phase)
					)
			{}
			SPROUT_CONSTEXPR value_type const& frequency() const {
				return base_type::begin().frequency();
			}
			SPROUT_CONSTEXPR value_type const& amplitude() const {
				return base_type::begin().amplitude();
			}
			SPROUT_CONSTEXPR value_type const& phase() const {
				return base_type::begin().phase();
			}
		};

		//
		// sawtooth_wave_forwarder
		//
		class sawtooth_wave_forwarder {
		public:
			template<typename Value>
			SPROUT_CONSTEXPR sprout::adaptors::sawtooth_wave_range<Value>
			operator()(
				Value const& frequency = 1,
				Value const& amplitude = 1,
				Value const& phase = 0
				)
			{
				return sprout::adaptors::sawtooth_wave_range<Value>(frequency, amplitude, phase);
			}
		};

		//
		// sawtooth_wave
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::sawtooth_wave_forwarder sawtooth_wave{};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Value>
		inline SPROUT_CONSTEXPR sprout::adaptors::sawtooth_wave_range<
			Value,
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::sawtooth_wave_range<Value> const& rhs) {
			return sprout::adaptors::sawtooth_wave_range<
				Value,
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs),
				rhs.frequency(),
				rhs.amplitude(),
				rhs.phase()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Value, typename Range>
	struct container_construct_traits<sprout::adaptors::sawtooth_wave_range<Value, Range> > {
	public:
		typedef typename sprout::container_construct_traits<Range>::copied_type copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type deep_copy(Cont&& cont) {
			return sprout::range::fixed::copy(sprout::forward<Cont>(cont), sprout::pit<copied_type>());
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
			return sprout::make<copied_type>(sprout::forward<Args>(args)...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type remake(
			Cont&& cont,
			typename sprout::container_traits<sprout::adaptors::sawtooth_wave_range<Value, Range> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_SAWTOOTH_WAVE_HPP
