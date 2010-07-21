include $(top_srcdir)/Makefile.common

AM_CPPFLAGS = -I$(top_srcdir)/include

asn_module_sources=	\
	Expr.c	\
	Complex-int.c	\
	IEEE-float.c	\
	Complex-float.c

asn_module_headers=	\
	Expr.h	\
	Complex-int.h	\
	IEEE-float.h	\
	Complex-float.h

asn_module_headers+=BOOLEAN.h
asn_module_sources+=BOOLEAN.c
asn_module_headers+=INTEGER.h
asn_module_headers+=NativeEnumerated.h
asn_module_sources+=INTEGER.c
asn_module_headers+=NULL.h
asn_module_sources+=NULL.c
asn_module_sources+=NativeEnumerated.c
asn_module_headers+=NativeInteger.h
asn_module_sources+=NativeInteger.c
asn_module_headers+=asn_SEQUENCE_OF.h
asn_module_sources+=asn_SEQUENCE_OF.c
asn_module_headers+=asn_SET_OF.h
asn_module_sources+=asn_SET_OF.c
asn_module_headers+=constr_CHOICE.h
asn_module_sources+=constr_CHOICE.c
asn_module_headers+=constr_SEQUENCE.h
asn_module_sources+=constr_SEQUENCE.c
asn_module_headers+=constr_SEQUENCE_OF.h
asn_module_sources+=constr_SEQUENCE_OF.c
asn_module_headers+=constr_SET_OF.h
asn_module_sources+=constr_SET_OF.c
asn_module_headers+=asn_application.h
asn_module_headers+=asn_system.h
asn_module_headers+=asn_codecs.h
asn_module_headers+=asn_internal.h
asn_module_headers+=OCTET_STRING.h
asn_module_sources+=OCTET_STRING.c
asn_module_headers+=BIT_STRING.h
asn_module_sources+=BIT_STRING.c
asn_module_sources+=asn_codecs_prim.c
asn_module_headers+=asn_codecs_prim.h
asn_module_headers+=ber_tlv_length.h
asn_module_sources+=ber_tlv_length.c
asn_module_headers+=ber_tlv_tag.h
asn_module_sources+=ber_tlv_tag.c
asn_module_headers+=ber_decoder.h
asn_module_sources+=ber_decoder.c
asn_module_headers+=der_encoder.h
asn_module_sources+=der_encoder.c
asn_module_headers+=constr_TYPE.h
asn_module_sources+=constr_TYPE.c
asn_module_headers+=constraints.h
asn_module_sources+=constraints.c
asn_module_headers+=xer_support.h
asn_module_sources+=xer_support.c
asn_module_headers+=xer_decoder.h
asn_module_sources+=xer_decoder.c
asn_module_headers+=xer_encoder.h
asn_module_sources+=xer_encoder.c
asn_module_headers+=per_support.h
asn_module_sources+=per_support.c
asn_module_headers+=per_decoder.h
asn_module_sources+=per_decoder.c
asn_module_headers+=per_encoder.h
asn_module_sources+=per_encoder.c


noinst_LTLIBRARIES=libasn1c.la
libasn1c_la_SOURCES=$(asn_module_sources)
#libasn1c_la_INCLUDES=$(asn_module_headers)

#DISTCLEANFILES = $(asn_module_sources) $(asn_module_headers) converter-sample.c
DISTCLEANFILES = converter-sample.c

regen: regenerate-from-asn1-source

regenerate-from-asn1-source:
	asn1c -fskeletons-copy -fnative-types $(top_srcdir)/protocol/vrt-ctrl-asn1-types.asn1
	./fix_asn1c_includes $(asn_module_headers) $(asn_module_sources)
	for f in $(asn_module_headers); do mv $$f $(top_srcdir)/include/vrtc/asn1c; done
