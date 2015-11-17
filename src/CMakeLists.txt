set(ELSD_SRCS
  valid_curve.c
  process_curve.c
  process_line.c
  elsd.c
  elsdetector.cpp
  svgwriter.cpp
  )

add_library(elsd SHARED ${ELSD_SRCS})
add_executable(pgm2svg main.cpp)
target_link_libraries(pgm2svg elsd ${ELSD_LIBS})

install(TARGETS elsd DESTINATION lib)
install(TARGETS pgm2svg DESTINATION bin)
