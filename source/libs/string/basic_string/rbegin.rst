.. _sprout-string-basic_string-rbegin:
###############################################################################
rbegin
###############################################################################

Interface
========================================
.. sourcecode:: c++

  reverse_iterator rbegin() SPROUT_NOEXCEPT;
  
  SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT;

Returns
========================================

| reverse iterator for the first element of reverse iteration.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = string<8>("homuhomu");
  static_assert(*input.rbegin() == 'u', "input first element of reverse iteration is u.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

