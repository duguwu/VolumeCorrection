# Install script for directory: C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/dev/vcpkg/packages/gsl_x64-windows")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/dev/vcpkg/buildtrees/gsl/x64-windows-rel/gsl.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/dev/vcpkg/buildtrees/gsl/x64-windows-rel/gsl.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/dev/vcpkg/buildtrees/gsl/x64-windows-rel/gsl.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gsl" TYPE FILE FILES
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/blas/gsl_blas.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/blas/gsl_blas_types.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_block.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_block_char.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_block_complex_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_block_complex_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_block_complex_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_block_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_block_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_block_int.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_block_long.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_block_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_block_short.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_block_uchar.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_block_uint.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_block_ulong.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_block_ushort.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/block/gsl_check_range.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/bspline/gsl_bspline.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/bst/gsl_bst.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/bst/gsl_bst_avl.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/bst/gsl_bst_rb.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/bst/gsl_bst_types.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/cblas/gsl_cblas.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/cdf/gsl_cdf.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/cheb/gsl_chebyshev.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/combination/gsl_combination.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/complex/gsl_complex.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/complex/gsl_complex_math.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/const/gsl_const.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/const/gsl_const_cgs.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/const/gsl_const_cgsm.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/const/gsl_const_mks.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/const/gsl_const_mksa.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/const/gsl_const_num.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/deriv/gsl_deriv.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/dht/gsl_dht.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/diff/gsl_diff.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/eigen/gsl_eigen.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/err/gsl_errno.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/err/gsl_message.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/fft/gsl_dft_complex.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/fft/gsl_dft_complex_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/fft/gsl_fft.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/fft/gsl_fft_complex.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/fft/gsl_fft_complex_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/fft/gsl_fft_halfcomplex.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/fft/gsl_fft_halfcomplex_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/fft/gsl_fft_real.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/fft/gsl_fft_real_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/filter/gsl_filter.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/fit/gsl_fit.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/gsl_inline.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/gsl_machine.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/gsl_math.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/gsl_minmax.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/gsl_mode.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/gsl_nan.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/gsl_pow_int.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/gsl_precision.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/gsl_types.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/gsl_version.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/histogram/gsl_histogram.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/histogram/gsl_histogram2d.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/ieee-utils/gsl_ieee_utils.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/integration/gsl_integration.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/interpolation/gsl_interp.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/interpolation/gsl_interp2d.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/interpolation/gsl_spline.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/interpolation/gsl_spline2d.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/linalg/gsl_linalg.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/matrix/gsl_matrix.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/matrix/gsl_matrix_char.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/matrix/gsl_matrix_complex_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/matrix/gsl_matrix_complex_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/matrix/gsl_matrix_complex_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/matrix/gsl_matrix_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/matrix/gsl_matrix_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/matrix/gsl_matrix_int.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/matrix/gsl_matrix_long.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/matrix/gsl_matrix_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/matrix/gsl_matrix_short.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/matrix/gsl_matrix_uchar.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/matrix/gsl_matrix_uint.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/matrix/gsl_matrix_ulong.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/matrix/gsl_matrix_ushort.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/min/gsl_min.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/monte/gsl_monte.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/monte/gsl_monte_miser.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/monte/gsl_monte_plain.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/monte/gsl_monte_vegas.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/movstat/gsl_movstat.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/multifit/gsl_multifit.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/multifit/gsl_multifit_nlin.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/multifit_nlinear/gsl_multifit_nlinear.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/multilarge/gsl_multilarge.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/multilarge_nlinear/gsl_multilarge_nlinear.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/multimin/gsl_multimin.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/multiroots/gsl_multiroots.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/multiset/gsl_multiset.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/ntuple/gsl_ntuple.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/ode-initval/gsl_odeiv.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/ode-initval2/gsl_odeiv2.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permutation.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_char.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_complex_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_complex_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_complex_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_int.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_long.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_matrix.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_matrix_char.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_matrix_complex_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_matrix_complex_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_matrix_complex_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_matrix_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_matrix_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_matrix_int.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_matrix_long.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_matrix_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_matrix_short.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_matrix_uchar.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_matrix_uint.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_matrix_ulong.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_matrix_ushort.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_short.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_uchar.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_uint.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_ulong.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_ushort.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_vector.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_vector_char.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_vector_complex_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_vector_complex_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_vector_complex_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_vector_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_vector_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_vector_int.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_vector_long.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_vector_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_vector_short.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_vector_uchar.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_vector_uint.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_vector_ulong.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/permutation/gsl_permute_vector_ushort.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/poly/gsl_poly.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/qrng/gsl_qrng.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/randist/gsl_randist.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/rng/gsl_rng.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/roots/gsl_roots.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/rstat/gsl_rstat.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/siman/gsl_siman.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_heapsort.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_char.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_int.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_long.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_short.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_uchar.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_uint.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_ulong.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_ushort.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_vector.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_vector_char.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_vector_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_vector_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_vector_int.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_vector_long.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_vector_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_vector_short.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_vector_uchar.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_vector_uint.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_vector_ulong.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sort/gsl_sort_vector_ushort.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spblas/gsl_spblas.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_airy.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_bessel.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_clausen.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_coulomb.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_coupling.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_dawson.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_debye.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_dilog.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_elementary.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_ellint.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_elljac.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_erf.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_exp.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_expint.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_fermi_dirac.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_gamma.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_gegenbauer.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_hermite.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_hyperg.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_laguerre.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_lambert.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_legendre.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_log.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_mathieu.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_pow_int.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_psi.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_result.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_sincos_pi.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_synchrotron.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_transport.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_trig.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_sf_zeta.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/specfunc/gsl_specfunc.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/splinalg/gsl_splinalg.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spmatrix/gsl_spmatrix.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spmatrix/gsl_spmatrix_char.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spmatrix/gsl_spmatrix_complex_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spmatrix/gsl_spmatrix_complex_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spmatrix/gsl_spmatrix_complex_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spmatrix/gsl_spmatrix_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spmatrix/gsl_spmatrix_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spmatrix/gsl_spmatrix_int.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spmatrix/gsl_spmatrix_long.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spmatrix/gsl_spmatrix_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spmatrix/gsl_spmatrix_short.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spmatrix/gsl_spmatrix_uchar.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spmatrix/gsl_spmatrix_uint.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spmatrix/gsl_spmatrix_ulong.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/spmatrix/gsl_spmatrix_ushort.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/statistics/gsl_statistics.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/statistics/gsl_statistics_char.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/statistics/gsl_statistics_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/statistics/gsl_statistics_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/statistics/gsl_statistics_int.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/statistics/gsl_statistics_long.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/statistics/gsl_statistics_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/statistics/gsl_statistics_short.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/statistics/gsl_statistics_uchar.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/statistics/gsl_statistics_uint.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/statistics/gsl_statistics_ulong.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/statistics/gsl_statistics_ushort.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sum/gsl_sum.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/sys/gsl_sys.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/test/gsl_test.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector_char.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector_complex.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector_complex_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector_complex_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector_complex_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector_float.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector_int.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector_long.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector_long_double.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector_short.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector_uchar.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector_uint.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector_ulong.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/vector/gsl_vector_ushort.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/wavelet/gsl_wavelet.h"
    "C:/dev/vcpkg/buildtrees/gsl/src/gsl-2-40b499007f.clean/wavelet/gsl_wavelet2d.h"
    "C:/dev/vcpkg/buildtrees/gsl/x64-windows-rel/gsl_types.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/dev/vcpkg/buildtrees/gsl/x64-windows-rel/gslcblas.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/dev/vcpkg/buildtrees/gsl/x64-windows-rel/gslcblas.dll")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/dev/vcpkg/buildtrees/gsl/x64-windows-rel/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
