#!/bin/bash
set -e

# Build sample dependencies.
pushd source/glslang
[ -d build ] || mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j`nproc`
mkdir -p ../../../x86_64/lib/glslang
cp SPIRV/libSPIRV.a ../../../x86_64/lib/glslang
cp SPIRV/libSPVRemapper.a ../../../x86_64/lib/glslang
cp glslang/libglslang.a ../../../x86_64/lib/glslang
cp glslang/OSDependent/Unix/libOSDependent.a ../../../x86_64/lib/glslang
cp OGLCompilersDLL/libOGLCompiler.a ../../../x86_64/lib/glslang
cp hlsl/libHLSL.a ../../../x86_64/lib/glslang
cp External/spirv-tools/source/libSPIRV-Tools.a ../../../x86_64/lib/spirv-tools
cp External/spirv-tools/source/opt/libSPIRV-Tools-opt.a ../../../x86_64/lib/spirv-tools
popd

# Build the samples.
pushd samples
[ -d build ] || mkdir build
cd build
cmake ..
make -j`nproc`
popd
