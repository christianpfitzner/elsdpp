#ELSD - Ellipse and Line Segment Detector
#
#  Copyright (c) 2012 viorica patraucean (vpatrauc@gmail.com)
#  
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Affero General Public License as
#  published by the Free Software Foundation, either version 3 of the
#  License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU Affero General Public License for more details.
#
#  You should have received a copy of the GNU Affero General Public License
#  along with this program. If not, see <http://www.gnu.org/licenses/>.
cmake_minimum_required (VERSION 2.8.11)
project (elsdpp)

# add_definitions(-std=c++11 -fPIC)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -fPIC")

set(ELSD_SRCS
  src/valid_curve.c
  src/process_curve.c
  src/process_line.c
  src/write_svg.c
  src/elsd.c
  src/elsdetector.cpp
  src/svgwriter.cpp
  )
set(ELSD_INC
  include/elsdetector.hpp
  include/svgwriter.hpp
  )

include_directories(include)

find_library(LAPACK_LIB NAMES lapack)
find_library(BLAS_LIB NAMES blas)
find_library(MATH_LIB NAMES m)

set(ELSD_LIBS
    ${LAPACK_LIB}
    ${BLAS_LIB}
    ${MATH_LIB}
    )

add_library(elsd SHARED ${ELSD_SRCS})
add_executable(pgm2svg src/main.c)
target_link_libraries(pgm2svg elsd ${ELSD_LIBS})


install(TARGETS elsd DESTINATION lib)
install(TARGETS pgm2svg DESTINATION bin)
install(FILES ${ELSD_INC} DESTINATION include)
