#!/bin/bash

PROGRAM=./a.out

function assert_equal() {
  if [[ "$1" != "$2" ]]
  then
    echo "expected $1 to equal $2, but did not"
  else
    echo "passed"
  fi
}

function test() {
  local actual=`cat test.tsv | $PROGRAM`
  read -r -d '' expected <<EOF
{"index": {"_index": "wat", "_type": "taco", "_id": "3", "_parent": "4"}}
{"user_id": "5", "collection_id": "6"}
EOF
  assert_equal "$actual" "$expected"
}

test
