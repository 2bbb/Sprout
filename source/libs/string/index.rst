.. _sprout-string:

###############################################################################
Sprout.String
###############################################################################

.. toctree::
    :hidden:

    char_traits/index
    basic_string/index
    string
    wstring
    u16string
    u32string
    basic_string/swap-global
    basic_string/operator-plus
    basic_string/operator-equal_to
    basic_string/operator-not_equal_to
    basic_string/operator-less
    basic_string/operator-greater
    basic_string/operator-less_equal
    basic_string/operator-greater_equal
    basic_string/operator-left_shift
    basic_string/operator-right_shift
    string_to_int
    stoi
    stol
    stoul
    stoll
    stoull
    stoimax
    stoumax
    from_string-inttype
    string_to_float
    stof
    stod
    stold
    from_string-floattype
    int_to_string
    to_string_of-inttype
    to_string-inttype
    to_wstring-inttype
    to_u16string-inttype
    to_u32string-inttype
    float_to_string
    float_to_string_exp
    to_string_of-floattype
    to_string-floattype
    to_wstring-floattype
    to_u16string-floattype
    to_u32string-floattype
    to_string
    string_from_c_str
    make_string
    shrink
    stretch
    basic_string/std-tuple_size
    basic_string/std-tuple_element
    basic_string/tuple_get
    basic_string/std-hash
    basic_string/hash_value

Description
========================================

Character traits
----------------------------------------

.. csv-table::
    :header: class
    :widths: 4, 8

    :doc:`char_traits <./char_traits/index>`, ""

String classes
----------------------------------------

.. csv-table::
    :header: class
    :widths: 4, 8

    :doc:`basic_string <./basic_string/index>`, ""

basic_string aliases
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. csv-table::
    :header: alias
    :widths: 4, 8

    :doc:`string <./string>`, ""
    :doc:`wstring <./wstring>`, ""
    :doc:`u16string <./u16string>`, ""
    :doc:`u32string <./u32string>`, ""

Non-member functions
----------------------------------------

specialized algorithms
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. csv-table::
    :header: function
    :widths: 4, 8

    :doc:`swap <./basic_string/swap-global>`, ""

concatenations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. csv-table::
    :header: function
    :widths: 4, 8

    :doc:`operator+ <./basic_string/operator-plus>`, ""

comparisons
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. csv-table::
    :header: function
    :widths: 4, 8

    :doc:`operator== <./basic_string/operator-equal_to>`, ""
    :doc:`operator!= <./basic_string/operator-not_equal_to>`, ""
    :doc:`operator\< <./basic_string/operator-less>`, ""
    :doc:`operator\> <./basic_string/operator-greater>`, ""
    :doc:`operator\<= <./basic_string/operator-less_equal>`, ""
    :doc:`operator\>= <./basic_string/operator-greater_equal>`, ""

inserters and extractors
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. csv-table::
    :header: function
    :widths: 4, 8

    :doc:`operator\<\< <./basic_string/operator-left_shift>`, ""
    :doc:`operator\>\> <./basic_string/operator-right_shift>`, ""

numeric conversions (string to numeric)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. csv-table::
    :header: function
    :widths: 4, 8

    :doc:`string_to_int <./string_to_int>`, ""
    :doc:`stoi <./stoi>`, ""
    :doc:`stol <./stol>`, ""
    :doc:`stoul <./stoul>`, ""
    :doc:`stoll <./stoll>`, ""
    :doc:`stoull <./stoull>`, ""
    :doc:`stoimax <./stoimax>`, ""
    :doc:`stoumax <./stoumax>`, ""
    :doc:`from_string \<IntType\> <./from_string-inttype>`, ""
    :doc:`string_to_float <./string_to_float>`, ""
    :doc:`stof <./stof>`, ""
    :doc:`stod <./stod>`, ""
    :doc:`stold <./stold>`, ""
    :doc:`from_string \<FloatType\> <./from_string-floattype>`, ""

numeric conversions (numeric to string)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. csv-table::
    :header: function
    :widths: 4, 8

    :doc:`int_to_string <./int_to_string>`, ""
    :doc:`to_string_of \<IntType\> <./to_string_of-inttype>`, ""
    :doc:`to_string \<IntType\> <./to_string-inttype>`, ""
    :doc:`to_wstring \<IntType\> <./to_wstring-inttype>`, ""
    :doc:`to_u16string \<IntType\> <./to_u16string-inttype>`, ""
    :doc:`to_u32string \<IntType\> <./to_u32string-inttype>`, ""
    :doc:`float_to_string <./float_to_string>`, ""
    :doc:`float_to_string_exp <./float_to_string_exp>`, ""
    :doc:`to_string_of \<FloatType\> <./to_string_of-floattype>`, ""
    :doc:`to_string \<FloatType\> <./to_string-floattype>`, ""
    :doc:`to_wstring \<FloatType\> <./to_wstring-floattype>`, ""
    :doc:`to_u16string \<FloatType\> <./to_u16string-floattype>`, ""
    :doc:`to_u32string \<FloatType\> <./to_u32string-floattype>`, ""

string generators
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. csv-table::
    :header: function
    :widths: 4, 8

    :doc:`to_string <./to_string>`, ""
    :doc:`string_from_c_str <./string_from_c_str>`, ""
    :doc:`make_string <./make_string>`, ""
    :doc:`shrink <./shrink>`, ""
    :doc:`stretch <./stretch>`, ""

Tuple interface
----------------------------------------

.. csv-table::
    :header: matafunction
    :widths: 4, 8

    :doc:`std::tuple_size <./basic_string/std-tuple_size>`, ""
    :doc:`std::tuple_element <./basic_string/std-tuple_element>`, ""

.. csv-table::
    :header: function
    :widths: 4, 8

    :doc:`tuple_get <./basic_string/tuple_get>`, ""

Hash support
----------------------------------------

.. csv-table::
    :header: class
    :widths: 4, 8

    :doc:`std::hash <./basic_string/std-hash>`, ""

.. csv-table::
    :header: function
    :widths: 4, 8

    :doc:`hash_value <./basic_string/hash_value>`, ""

Header
========================================

``sprout/string.hpp``

