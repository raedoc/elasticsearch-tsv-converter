#!/bin/bash

PROGRAM=./convert

function assert_equal() {
  if [[ "$1" != "$2" ]]
  then
    echo "expected $1 to equal $2, but did not"
  else
    echo "passed"
  fi
}

function test() {
  local actual=`cat test.tsv | $PROGRAM wat taco`
  read -r -d '' expected <<EOF
{"index":{"_index":"wat","_type":"taco","_id":"2-3-4","_parent":"2"}}
{"user_id":"3","collection_id":"4","created_at":"1401887869000"}
{"index":{"_index":"wat","_type":"taco","_id":"w21-Ei1-My1","_parent":"4000"}}
{"user_id":"5000","collection_id":"6000","created_at":"1401887869000"}
EOF
  assert_equal "$actual" "$expected"
}

test
