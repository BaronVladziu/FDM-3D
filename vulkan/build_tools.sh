#!/bin/bash
set -e

BTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BINDIR="$BTDIR"/x86_64/bin
SHAREDDIR="$BTDIR"/x86_64/shared
LIBDIR="$BTDIR"/x86_64/lib
INCLUDEDIR="$BTDIR"/x86_64/include

buildVia() {
    pushd $BTDIR/source/via
    [ -d build ] || mkdir build
    cd build
    cmake -DJSONCPP_SOURCE_DIR=./ -DJSONCPP_INCLUDE_DIR=./ ..
    make -j`nproc`
    cp via "${BINDIR}"
    popd
}

buildShaderc() {
    pushd "$BTDIR"/source/shaderc
    python2 update_shaderc_sources.py
    cd src
    [ -d build ] || mkdir build
    cd build
    cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
    sed -i -E 's:\/(.*?)build:..:g' libshaderc/shaderc_combined.ar
    make -j`nproc`
    cp glslc/glslc "${BINDIR}"
    mkdir -p "${LIBDIR}"/libshaderc
    ln -sf "$PWD"/libshaderc/libshaderc_combined.a "${LIBDIR}"/libshaderc
    mkdir -p "${INCLUDEDIR}"/libshaderc
    ln -sf "$PWD"/../libshaderc/include/shaderc/shaderc.h "${INCLUDEDIR}"/libshaderc/
    ln -sf "$PWD"/../libshaderc/include/shaderc/shaderc.hpp "${INCLUDEDIR}"/libshaderc/
    popd
}

buildSpirvTools() {
    pushd "$BTDIR"/source/spirv-tools
    cp tools/emacs/50spirv-tools.el "${SHAREDDIR}"
    [ -d build ] || mkdir build
    cd build
    cmake .. 
    make -j`nproc`
    cp tools/spirv-as "${BINDIR}"
    cp tools/spirv-cfg "${BINDIR}"
    cp tools/spirv-dis "${BINDIR}"
    cp tools/spirv-opt "${BINDIR}"
    cp tools/spirv-val "${BINDIR}"
    cp ../tools/lesspipe/spirv-lesspipe.sh "${BINDIR}"
    chmod 755 "${BINDIR}"/spirv-lesspipe.sh
    popd
}

buildSpirvCross() {
    pushd "$BTDIR"/source/spirv-cross
    make -j`nproc`
    cp spirv-cross "${BINDIR}"
    popd
}

checkPkgs() {
    if [ dpkg-query -l python2.7 git &>/dev/null ]; then
	echo "Please check that git and python2 is installed to run the build_tools script"
	exit
    fi
}

usage() {
    echo "Build tools script"
    echo "Usage: $CMDNAME [--via] [--shaderc] [--spirvtools] [--sprivcross]"
    echo ""
    echo "Omitting parameters will build every tool"
}

if [[ $# == 0 ]]; then
    buildVia
    buildShaderc
    buildSpirvTools
    buildSpirvCross
fi

# parse the arguments
while test $# -gt 0; do
    case "$1" in
	--via)
	    shift
	    buildVia
	    ;;
	--shaderc)
	    shift
	    buildShaderc
	    ;;
	--spirvtools)
	    shift
	    buildSpirvTools
	    ;;
	--spirvcross)
	    shift
	    buildSpirvCross
	    ;;
	--help|-h)
	    shift
	    usage
	    ;;
	*)
	    shift
	    echo "error: unknown option"
	    usage
	    ;;
    esac
done


