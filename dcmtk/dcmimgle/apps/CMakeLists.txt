# declare directories containing used libraries
LINK_DIRECTORIES(${dcmimgle_BINARY_DIR} ${ofstd_BINARY_DIR} ${dcmdata_BINARY_DIR} ${ZLIB_LIBDIR})

# declare executables
FOREACH(PROGRAM dcmdspfn dcod2lum dconvlum)
  ADD_EXECUTABLE(${PROGRAM} ${PROGRAM})
ENDFOREACH(PROGRAM)

# declare installation files
FOREACH(PROGRAM dcmdspfn dcod2lum dconvlum)
  INSTALL_TARGETS(${INSTALL_BINDIR} ${PROGRAM})
ENDFOREACH(PROGRAM)

# make sure executables are linked to the corresponding libraries
FOREACH(PROGRAM dcmdspfn dcod2lum dconvlum)
  TARGET_LINK_LIBRARIES(${PROGRAM} ofstd dcmimgle ${ZLIB_LIBS})
ENDFOREACH(PROGRAM)
TARGET_LINK_LIBRARIES(dcmdspfn dcmdata)
