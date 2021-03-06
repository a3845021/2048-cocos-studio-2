APP_STL := gnustl_static

APP_CPPFLAGS := -frtti \
-DCC_ENABLE_CHIPMUNK_INTEGRATION=0 \
-std=c++11 \
-fsigned-char \
-Wno-extern-c-compat \
-DCC_USE_3D_PHYSICS=0 \
-DCC_ENABLE_BULLET_INTEGRATION=0 \
-DCC_ENABLE_BOX2D_INTEGRATION=0 \
-DCC_USE_NAVMESH=0 \
-DCC_USE_TIFF=0 \
-DCC_USE_WEBP=0
APP_LDFLAGS := -latomic

APP_CPPFLAGS += -DNDEBUG
APP_OPTIM := release

APP_PLATFORM := android-22
