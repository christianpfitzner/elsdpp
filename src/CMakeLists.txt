cmake_minimum_required(VERSION 2.8)
project( elsdpp )

find_package( OpenCV REQUIRED )

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_calib3d opencv_video opencv_features2d opencv_ml opencv_highgui opencv_objdetect opencv_contrib opencv_legacy opencv_gpu)

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
target_link_libraries(pgm2svg elsd ${ELSD_LIBS} ${OpenCV_LIBRARIES})

#install(TARGETS elsd DESTINATION lib)
#install(TARGETS pgm2svg DESTINATION bin)
