include_directories("${PROJECT_BINARY_DIR}"
		    "${PROJECT_SOURCE_DIR}/inc"
		    )
add_library(foo imgconf.c imgproc.c paint.c)

