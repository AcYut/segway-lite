XABSL_DIR = ../../../Xabsl

XSLT = xsltproc --xinclude
DOT = dot
DOTML_DIR = ../../../util/dotml-1.2
XABSL_COMPILER_DIR = $(XABSL_DIR)/compiler
XABSL_XSL_DIR = $(XABSL_DIR)/xsl

XABSL_OUTPUT_DIR = ../../../
INTERMEDIATE_CODE = intermediate-code.dat
DEBUG_SYMBOLS = debug-symbols.dat
DOC_OUTPUT_DIR = ../../xabsl-doc
XABSL_TEMP_DIR = .
XML_OUTPUT_DIR = ../../xabsl-xml
XABSL_COMPILER_OPTIONS =

SOURCES = $(shell find . -name "*.xabsl")

AGENTS_FILE          = agents.xabsl

include $(XABSL_DIR)/XabslMakefile
