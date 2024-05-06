#!/bin/bash
git add .
echo "Write commit message :"
read commit_message
git commit -m "$commit_message"
git push
echo "Pushing to git"