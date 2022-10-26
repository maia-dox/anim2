# GNU Make workspace makefile autogenerated by Premake

.NOTPARALLEL:

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  Anim_config = debug
  GLFW_config = debug
  GLAD_config = debug
endif
ifeq ($(config),release)
  Anim_config = release
  GLFW_config = release
  GLAD_config = release
endif

PROJECTS := Anim GLFW GLAD

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

Anim: GLFW GLAD
ifneq (,$(Anim_config))
	@echo "==== Building Anim ($(Anim_config)) ===="
	@${MAKE} --no-print-directory -C Anim -f Makefile config=$(Anim_config)
endif

GLFW:
ifneq (,$(GLFW_config))
	@echo "==== Building GLFW ($(GLFW_config)) ===="
	@${MAKE} --no-print-directory -C Anim/Vendor/glfw -f Makefile config=$(GLFW_config)
endif

GLAD:
ifneq (,$(GLAD_config))
	@echo "==== Building GLAD ($(GLAD_config)) ===="
	@${MAKE} --no-print-directory -C Anim/Vendor/glad -f Makefile config=$(GLAD_config)
endif

clean:
	@${MAKE} --no-print-directory -C Anim -f Makefile clean
	@${MAKE} --no-print-directory -C Anim/Vendor/glfw -f Makefile clean
	@${MAKE} --no-print-directory -C Anim/Vendor/glad -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   Anim"
	@echo "   GLFW"
	@echo "   GLAD"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"