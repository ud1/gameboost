project( jpeglib )
cmake_minimum_required(VERSION 2.8)

set(jpeglib_dir jpeg-8c)
include_directories( ${jpeglib_dir} )
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
#------ sources ------
set( jpeglib_source_files
	jconfig.h

	cderror.h
	jdct.h
	jerror.h
	jinclude.h
	jmemsys.h
	jmorecfg.h
	jpegint.h
	jpeglib.h
	jversion.h
	transupp.h

	jaricom.c
	jcapimin.c
	jcapistd.c
	jcarith.c
	jccoefct.c
	jccolor.c
	jcdctmgr.c
	jchuff.c
	jcinit.c
	jcmainct.c
	jcmarker.c
	jcmaster.c
	jcomapi.c
	jconfig.cfg
	jcparam.c
	jcprepct.c
	jcsample.c
	jctrans.c
	jdapimin.c
	jdapistd.c
	jdarith.c
	jdatadst.c
	jdatasrc.c
	jdcoefct.c
	jdcolor.c
	jddctmgr.c
	jdhuff.c
	jdinput.c
	jdmainct.c
	jdmarker.c
	jdmaster.c
	jdmerge.c
	jdpostct.c
	jdsample.c
	jdtrans.c
	jerror.c
	jfdctflt.c
	jfdctfst.c
	jfdctint.c
	jidctflt.c
	jidctfst.c
	jidctint.c
	jmemmgr.c
	jmemnobs.c
	jquant1.c
	jquant2.c
	jutils.c
	rdbmp.c
	rdcolmap.c
	rdgif.c
	rdppm.c
	rdrle.c
	rdswitch.c
	rdtarga.c
	transupp.c
	wrbmp.c
	wrgif.c
	wrppm.c
	wrrle.c
	wrtarga.c
)
foreach( src_file ${jpeglib_source_files} )
	list( APPEND jpeglib_SOURCES ${jpeglib_dir}/${src_file})
endforeach( src_file ${jpeg_lib_source_files} )
#------ target -----
add_library( jpeglib ${jpeglib_SOURCES} )

set_target_properties(jpeglib PROPERTIES
	DEBUG_POSTFIX "${LIB_TARGET_SUFFIX}_d"
)

install( TARGETS jpeglib DESTINATION ${STATIC_DEP_LIBS_DIR} )