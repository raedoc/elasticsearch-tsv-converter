#!/bin/bash

SAMPLE_PATH=`cd $(dirname $0) && pwd`/benchmark
SAMPLE_SIZE=$1
HOST=localhost:9200
INDEX=wat
TYPE=taco
PARENT=beans

if [ -z "$SAMPLE_SIZE" ]; then
  echo "Usage: $0 <sample-size>"
  exit 1
fi

function reset() {
  curl -s -o /dev/null -XDELETE $HOST/$INDEX
  curl -s -o /dev/null -XPUT $HOST/$INDEX -d"{
    mappings : {
      $PARENT: {},
      $TYPE: {
        _parent: {
          type: \"$PARENT\"
        }
      }
    }
  }"
  curl -s -o /dev/null -XPUT $HOST/$INDEX/_settings -d'{
    "index" : {
      "refresh_interval" : -1
    }
  }'
}

function generateLine() {
  echo $RANDOM $RANDOM $RANDOM $RANDOM
}

function generateData() {
  for o in {1..100}
  do
    for i in {1..100000}
    do
      generateLine
    done
    echo -n '.' 1>&2
  done
  echo 1>&2
}

function makeSample() {
  mkdir -p $SAMPLE_PATH
  generateData > $SAMPLE_PATH/sample.tsv
}

function splitSample() {
  rm -rf $SAMPLE_PATH/sample
  mkdir -p $SAMPLE_PATH/sample
  split -a 10 -l $SAMPLE_SIZE $SAMPLE_PATH/sample.tsv $SAMPLE_PATH/sample/part-
}

function convertAndUpload() {
  for file in $SAMPLE_PATH/sample/part-*
  do
    cat $file | ./convert | time curl -o /dev/null -s -XPOST $HOST/_bulk --data-binary @-
  done
}

reset
makeSample
splitSample
convertAndUpload
