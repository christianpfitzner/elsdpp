set(ELSD_SRCS
  elsd.c
  elsdetector.cpp
  elsdpgmfilereader.cpp
  elsdsvgwriter.cpp
  process_curve.c
  process_line.c
  valid_curve.c
  )

add_library(elsd SHARED ${ELSD_SRCS})
add_executable(pgm2svg main.cpp)
target_link_libraries(pgm2svg elsd ${ELSD_LIBS})

install(TARGETS elsd DESTINATION lib)
install(TARGETS pgm2svg DESTINATION bin)
