########################################################################################################################################
# NESalizer-SteamLink - Ported by TheCosmicSlug, Based on original emulation code by Ulf Magnusson github.com/ulfalizer/nesalizer      #
########################################################################################################################################

EXECUTABLE        = nesalizer
BUILD_DIR         = build
CONF              = release
IMGUI_DIR 	  = ./src/imgui

# Don't Echo commands executed.
q = @

# Sources (*.c *.cpp *.h)
cpp_sources = audio apu blip_buf common controller cpu input imgui/imgui \
  imgui/imgui_draw imgui/imgui_tables imgui/imgui_widgets imgui_impl_sdl imgui_impl_sdlrenderer imguifilesystem main md5   \
  mapper mapper_0 mapper_1 mapper_2 mapper_3 mapper_4 mapper_5 mapper_7 \
  mapper_9 mapper_10 mapper_11 mapper_13 mapper_28 mapper_71 mapper_232 \
  ppu rom save_states sdl_backend timing sdl_frontend test

c_sources = tables

# Objects & Dependancies
cpp_objects = $(addprefix $(BUILD_DIR)/,$(cpp_sources:=.o))
c_objects   = $(addprefix $(BUILD_DIR)/,$(c_sources:=.o))
objects     = $(c_objects) $(cpp_objects)
deps        = $(addprefix $(BUILD_DIR)/,$(c_sources:=.d) $(cpp_sources:=.d))

# SDL Path includes & linking libaries.
compile_flags := -I$(MARVELL_ROOTFS)/usr/include/SDL2 -I$(IMGUI_DIR) -DHAVE_OPENGLES2
LDLIBS :=  -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lrt -lm -lEGL -lGLESv2 -Wl,--gc-sections

# Steamlink Specific Stuff 
armv7_optimizations = -marm -mtune=cortex-a9 -mfpu=neon -mfloat-abi=hard -march=armv7-a

# Tried alot of compiler options to finally get this running without lagging - Some may not be needed, but its working // -fno-exceptions -fdata-sections
optimizations = -Ofast -pthread  -ffast-math -ffinite-math-only -funsafe-loop-optimizations \
		   -fno-math-errno -falign-functions=1 -falign-loops=1 -falign-jumps=1 \
		   -fno-unwind-tables -fno-asynchronous-unwind-tables -ftree-loop-if-convert \
		   -fno-align-jumps -fmerge-all-constants -fno-stack-protector -fomit-frame-pointer
		  
# Compiilation Warnings
warnings = -Wunused -Wuninitialized -Wdisabled-optimization -Wno-switch -Wredundant-decls -ftree-loop-distribution -Wmaybe-uninitialized -Wunsafe-loop-optimizations

# Debug Build with GDB support & no optimizations
ifneq ($(findstring debug,$(CONF)),)
    compile_flags += $(armv7_optimizations) -g3 -ggdb
	link_flags =  += $(armv7_optimizations) -g3 -ggdb
endif

# Release Build with ARMv7 optimizations to run without lagging
ifneq ($(findstring release,$(CONF)),)
    compile_flags += $(armv7_optimizations) $(optimizations) -DOPTIMIZING
    link_flags    += $(armv7_optimizations) $(optimizations)
endif 

$(BUILD_DIR)/$(EXECUTABLE): $(objects)
	@echo Linking $@
	$(q)$(CXX) $(link_flags) $^ $(LDLIBS) -o $@
$(cpp_objects): $(BUILD_DIR)/%.o: src/%.cpp
	@echo Compiling $<
	$(q)$(CXX) -c -Isrc -std=gnu++17 $(compile_flags) $(warnings) -fno-rtti  $< -o $@
$(c_objects): $(BUILD_DIR)/%.o: src/%.c
	@echo Compiling $<
	$(q)$(CC) -c -Isrc -std=c17 $(compile_flags) $(warnings) $< -o $@
$(deps): $(BUILD_DIR)/%.d: src/%.cpp
	@set -e; rm -f $@;                                                 \
	  $(CXX) -MM -Isrc $(shell sdl2-config --cflags) $< > $@.$$$$; \
	  sed 's,\($*\)\.o[ :]*,$(BUILD_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	  rm -f $@.$$$$
ifneq ($(MAKECMDGOALS),clean)
    -include $(deps)
endif
$(BUILD_DIR): ; $(q)mkdir $(BUILD_DIR)
$(objects) $(deps): | $(BUILD_DIR)
.PHONY: dist
dist: ; # Package a tar.gz containing the emulator & launcher for SteamLink -TODO-
