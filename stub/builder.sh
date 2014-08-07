#!/bin/bash
# auto compile and deploy sdk
#

CURDIR=`dirname $0`
pushd "$CURDIR/.."
SDK_HOME=$(pwd)
popd

# if use fixed sdkhome modify here!
# SDK_HOME=$HOME/devhome/sdk

echo "SDK_HOME=$SDK_HOME"

# extend dir base by SDK_HOME
# infomation dir. record install filelist etc.
INFO_DIR=$SDK_HOME/info

# dynamic link library dir. store .dylib or .so
[ ! -d "$INFO_DIR" ] && mkdir -p "$INFO_DIR"
OSNAME=$(uname)
if [ "$OSNAME" == "Darwin" ]; then
    DYLIB=dylib
    DYEXT=dylib
else
    DYLIB=dylib
    DYEXT=so
fi
DYLIB_DIR=$SDK_HOME/${DYLIB}
[ ! -d "$DYLIB_DIR" ] && mkdir -p "$DYLIB_DIR"

# image tmp dir
BUILD_DIR=$HOME/tmp/build
IMG_DIR=$HOME/tmp/dist

# sdk env file
SDK_ENV=$SDK_HOME/sdk.env


# *******************************************************
# function 
# *******************************************************
function automake()
{
    tarfile=`basename $1`
    name=${tarfile%.tar.*}
    infofile=$INFO_DIR/$name.lst
    if [ -f "$infofile" ]; then
        return
    fi
    
    [ -n "$2" -a ! -d "$2" ] && mkdir -p "$2"
    echo "$1" | grep ".tar.bz2" && tar -jxvf "$1" -C "$2"
    echo "$1" | grep ".tar.gz" && tar -zxvf "$1" -C "$2"
    dst="$2"/$name
    
    if [ -d "$dst" ]; then
      pushd "$dst"
        ./configure CPPFLAGS="-fPIC" --prefix=$SDK_HOME $3 && make && make install
        # configure again for get filelist
        imgdir=$IMG_DIR/$name
        [ -d "$imgdir" ] && rm -rvf "$imgdir"
        ./configure CPPFLAGS="-fPIC" --prefix=$imgdir $3 && make install 
        if [ -d "$imgdir" ]; then
            pushd "$imgdir"
                find . > "$infofile"
            popd
            #make uninstall
            rm -rvf "$imgdir"
        fi
        #echo "# build: $(DATE)" >> "$infofile"
      popd
      rm -rvf "$dst"
    fi
}

function automake2()
{
    automake "$1" "$BUILD_DIR" "$2"
}

function gen_env()
{
cat << EOF > "$SDK_ENV"
export SDK_HOME=$SDK_HOME
export PATH=\$SDK_HOME/bin:\$PATH
export LD_LIBRARY_PATH=\$SDK_HOME/lib:\$SDK_HOME/dylib:\$LD_LIBRARY_PATH
export PKG_CONFIG_PATH=\$SDK_HOME/lib/pkgconfig:\$PKG_CONFIG_PATH 
EOF
}

function install_env()
{
    bashconf=$HOME/.bash_profile
    envfname=$(basename "$SDK_ENV")
    tmpfile=$$.tmp
    touch "$bashconf"
    # unix not support -i 
    sed "/${envfname}/d" "$bashconf" > $tmpfile && mv -f $tmpfile "$bashconf"
    [ -f "$tmpfile" ] && rm -f "$tmpfile"
    echo "source $SDK_ENV" >> "$bashconf"
}

function main()
{
    automake2 protobuf-2.5.0.tar.gz --enable-shared=no 
    automake2 apr-1.5.1.tar.bz2
    automake2 apr-util-1.5.3.tar.bz2 "--with-apr=$SDK_HOME"
    automake2 curl-7.37.1.tar.bz2
    automake2 htmlcxx-0.84.tar.bz2
    #automake2 gflags-2.1.1.tar.gz
    #automake2 boost_1_55_0.tar.bz2
    mv $SDK_HOME/lib/*.${DYEXT}* "$DYLIB_DIR"
    gen_env
    install_env
}

main
