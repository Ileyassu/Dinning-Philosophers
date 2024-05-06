#!/bin/bash
git add .
read commit_message
git commit -m "$commit_message"
git push
echo "Pushing to git"