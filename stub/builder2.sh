#!/bin/bash
#

URI_REDIS="http://download.redis.io/releases/redis-3.0.7.tar.gz"
F_SRC_CONF="src.conf"

# tarball(tar.gz, tar.bz2)
# git
function get_src_type()
{
    stype=""
    bname=$(basename "$1")
    echo $bname | grep ".tar.gz$"  &>/dev/null && stype=".tar.gz"
    echo $bname | grep ".tar.bz2$" &>/dev/null && stype=".tar.bz2"
    echo $bname | grep ".git$"     &>/dev/null && stype=".git"
    [ -n "$stype" ] && {
        echo $stype; return 0
    } || {
        return -1
    }
}

function sub_verify_tarball()
{
    local_src_tarball="$2"
    if [ ! -f "$local_src_tarball" ]; then
        wget "$1"
    fi
}

function sub_verify_git()
{
    local_src_git_dir="$2"
    if [ ! -d "$local_src_git_dir" ]; then
        git clone "$1"
    else
        echo "update PASS"
    fi
}

function verify_src()
{
    uri="$1"
    bname=$(basename "$uri")
    ename=$(get_src_type "$bname")
    if [ -z "$ename" ]; then
        echo "EMPTY src type and basename=${ename}"
        return -2
    fi
    prj_name=$(echo $bname | sed "s:$ename::g")
    echo "prj_name=$prj_name"
    case "$ename" in
        ".tar.gz"|".tar.bz2") sub_verify_tarball "$uri" "$bname" ;;
        ".git") sub_verify_git "$uri" "$prj_name" ;;
        *)
            echo "NOT support the src type=${ename}"
            return -1
            ;;
    esac
    return 0
}

function eval_pack_env()
{
    eval $(cat "$F_SRC_CONF" | sed -n "/^\[$1\]\$/,/^[ \t]*\$/p" | sed 1d)
    echo "URI=$URI"
    echo "PREFIX=$PREFIX"
}


## build special
function build_redis()
{
    wget "$URI_REDIS"
    tarball=$(basename "$URI_REDIS")
    fname=$(basename "$URI_REDIS" | sed "s:.tar.gz$::g")
    tmpdir=/tmp/$$/
    mkdir -p $tmpdir
    tar -zxvf $tarball -C $tmpdir
    tmpdir1=$tmpdir/$fname
    if [ -d "$tmpdir1" ]; then
        pushd "$tmpdir1"
        make PREFIX=$SDK_HOME install
        make -C deps/hiredis PREFIX=$SDK_HOME install
        popd
    fi
}

# build sth
function build()
{
    product_name="$1"
    eval_pack_env "$product_name"
    verify_src "$URI"
}

# build_redis
#get_src_type "htmlcxx-0.84.tar.bz2"
#get_src_type "protobuf-2.5.0.tar.gz"
#get_src_type "protobuf-2.5.0.tar.gz.x"
#get_src_type "googletest.git"
#verify_src "protobuf-2.5.0.tar.gz"

build redis
build googletest
