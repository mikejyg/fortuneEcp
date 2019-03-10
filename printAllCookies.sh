#!/usr/bin/env bash
for i in $(cat datFileList); do Debug/fortuneEcp -m $i; done 
