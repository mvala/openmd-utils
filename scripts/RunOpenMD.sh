#!/bin/bash

function usage() {
cat << EOF
usage ./$(basename $0) [options] <file.md>

options:
	-o <direcotry>	Define output direcotry
	-r				Do render in blender
	-c <comment>	Write comment (comment will be appended to README file)
	
EOF
}

function clean() {
	echo "Deleting ${1//.md/.dump} ..."
	rm -f ${1//.md/.dump}	
	echo "Deleting ${1//.md/.xyz} ..."
	rm -f ${1//.md/.xyz}	
}

MYPWD=$(pwd)

OUTPUTDIR="."
BLENDER_PYTHON_OPT=""
PROCESS_INFO="No Info"
while getopts ":rc:o:" optname
  do
    case "$optname" in
      "r")
        echo "Will do rendering ... (TODO)"
        BLENDER_PYTHON_OPT="--render $BLENDER_PYTHON_OPT"
        ;;
      "o")
        OUTPUTDIR=$OPTARG/
        ;;
      "c")
        PROCESS_INFO=$OPTARG
        ;;
      "?")
        echo "Unknown option $OPTARG"
        usage
        exit 1
        ;;
      ":")
        echo "No argument value for option $OPTARG"
        ;;
      *)
      # Should not occur
        echo "Unknown error while processing options"
        ;;
    esac
  done

shift $((OPTIND-1))

[ "$1" = "--" ] && shift

if [ ! $# -eq 1 ];then
	usage
	exit 2
fi

INPUT="$(basename $1)"


if [ -f $OUTPUTDIR/lastdir ]; then
	ID=$(cat $OUTPUTDIR/lastdir)
	let ID=ID+1
	echo $ID > $(dirname $OUTPUTDIR)/lastdir
else
	ID=0
	echo $ID > $(dirname $OUTPUTDIR)/lastdir
	
fi

OUTPUTDIR=$(printf "%s/%03d" $(readlink -m $OUTPUTDIR) $ID)

if [ -d $OUTPUTDIR ];then
	echo "Output directory '$OUTPUTDIR' already exists"
	exit 3
else
	mkdir -p $OUTPUTDIR
fi

cp -rf $(dirname $1)/* $OUTPUTDIR
ln -sfn $OUTPUTDIR $(dirname $OUTPUTDIR)/last
cd $OUTPUTDIR

printf "$PROCESS_INFO" >> README

CURRENT_DIR="$(dirname $(dirname $(readlink -m $0)))"

clean $(basename $1)

echo "Running simulation $INPUT in $(readlink -m $OUTPUTDIR) ..."
openmd $INPUT
[ -f ${INPUT//.md/.dump} ] || exit 2
 
echo "Converting Dump to XYZ ..."
Dump2XYZ -i ${INPUT//.md/.dump}
[ -f ${INPUT//.md/.xyz} ] || exit 2

if hash blender 2>/dev/null; then
	echo "Creating Blender file from '${INPUT//.md/.xyz}' ..."
	export PYTHONPATH="$CURRENT_DIR/src/blender:$PYTHONPATH"
	rm -f ${INPUT//.md/.blend}
	blender --background --python $CURRENT_DIR/src/blender/openmd/create-video.py -- $BLENDER_PYTHON_OPT ${INPUT//.md/.xyz}
	[ $? -eq 0 ] || exit 4
fi
cd $MYPWD
