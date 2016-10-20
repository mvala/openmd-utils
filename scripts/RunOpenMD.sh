#!/bin/bash

trap finish SIGINT SIGTERM

function usage() {
cat << EOF
usage ./$(basename $0) [options] <file.omd>

options:
	
EOF
}

function finish() {
	MYSIG=$?
	mkdir -p $OPENMD_OUTPUT_DIR
	cp * $OPENMD_OUTPUT_DIR/
	echo 
	echo "Cleaning directory '$OPENMD_SANDBOX_DIR' ..."
	rm -rf $OPENMD_SANDBOX_DIR
	echo 
	echo "OPENMD_SANDBOX_DIR = $OPENMD_SANDBOX_DIR"
	echo "OPENMD_OUTPUT_DIR = $OPENMD_OUTPUT_DIR"
	echo
	echo "JOB exit with $MYSIG"
	if [ $MYSIG = 0 ];then
		echo "OK ($MYSIG)" > $OPENMD_OUTPUT_DIR/SUMMARY
	else
		echo "FAILED ($MYSIG)" > $OPENMD_OUTPUT_DIR/SUMMARY	
	fi
	exit $MYSIG
}

function getID() {

	if [ -n "$SLURM_ARRAY_JOB_ID" ];then
		OPENMD_ID="${SLURM_ARRAY_JOB_ID}_${SLURM_ARRAY_TASK_ID}"
		OPENMD_EXEC=${OPENMD_EXEC-openmd_MPI}
	elif [ -n "$SLURM_JOBID" ];then
		OPENMD_ID=$SLURM_JOBID
		OPENMD_EXEC=${OPENMD_EXEC-openmd_MPI}
	else
		OPENMD_ID=$$
		OPENMD_EXEC=${OPENMD_EXEC-openmd}
	fi
}

while getopts ":rc:o:" optname;do
	case "$optname" in
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

CMD_PREFIX="time"
OPENMD_EXEC_PREFIX=${OPENMD_EXEC_PREFIX-}

getID

FORCE_PARAM_PATH=${FORCE_PARAM_PATH-$OPENMD_INPUT_FILE}

OPENMD_INPUT_FILE="$(basename $1)"
OPENMD_DUMP_FILE=${OPENMD_INPUT_FILE//.omd/.dump}
OPENMD_XYZ_FILE=${OPENMD_INPUT_FILE//.omd/.xyz}
OPENMD_BLEND_FILE=${OPENMD_INPUT_FILE//.omd/.blend}

OPENMD_INIT_DIR=$(pwd)
OPENMD_SANDBOX_DIR=${OPENMD_SANDBOX_DIR-/tmp/openmd-utils}
OPENMD_SANDBOX_DIR="$OPENMD_SANDBOX_DIR/$OPENMD_ID"

OPENMD_BLENDER_DIR=${OPENMD_BLENDER_DIR-~/git/github/mvala/openmd-utils/src/blender}
OPENMD_OUTPUT_PREFIX=${OPENMD_OUTPUT_PREFIX-out}
OPENMD_OUTPUT_DIR=$OPENMD_INIT_DIR/$OPENMD_OUTPUT_PREFIX/$(basename $OPENMD_SANDBOX_DIR)

[ -d $OPENMD_SANDBOX_DIR ] && rm -rf $OPENMD_SANDBOX_DIR
mkdir -p $OPENMD_SANDBOX_DIR || exit 10
cd $OPENMD_SANDBOX_DIR
cp $OPENMD_INIT_DIR/*Def.omd .
cp $OPENMD_INIT_DIR/*.frc .
cp $OPENMD_INIT_DIR/$OPENMD_INPUT_FILE .
date
# Run OpenMD
if hash $OPENMD_EXEC 2>/dev/null; then
	$CMD_PREFIX $OPENMD_EXEC_PREFIX $OPENMD_EXEC $OPENMD_INPUT_FILE
else
	echo "Error: $OPENMD_EXEC not found"
    exit 3
fi
date
# Convert to XYZ
if hash Dump2XYZ 2>/dev/null; then
	$CMD_PREFIX Dump2XYZ -i $OPENMD_DUMP_FILE
else
	echo "Error: Dump2XYZ not found"
    exit 3
fi

if hash blender 2>/dev/null; then
	if [ -d $OPENMD_BLENDER_DIR ];then
		echo "Creating Blender file '$OPENMD_BLEND_FILE' from '$OPENMD_XYZ_FILE' ..."
		export PYTHONPATH="$OPENMD_BLENDER_DIR:$PYTHONPATH"
		rm -f $OPENMD_BLEND_FILE
		$CMD_PREFIX blender --background --python $OPENMD_BLENDER_DIR/openmd/create-video.py -- $BLENDER_PYTHON_OPT $OPENMD_XYZ_FILE
		[ $? -eq 0 ] || exit 5
	else
		echo "OPEN_BLENDER_DIR doesn't exist !!!"
		exit 4
	fi
else
	echo "Blender was now found on the system. Skipping ..."
fi

finish

