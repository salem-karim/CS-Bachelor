#!/bin/bash

#1 create local repo with 2 branches and 2 commits on dev branch, then copy the repo
mkdir KONF_4
cd KONF_4
git init
touch initial.txt
git add . && git commit -m "Initial commit"
git switch -c dev
echo "Hello World" > hello.txt
git add . && git commit -m "Second commit"
echo "Hello World" > hello2.txt
git add . && git commit -m "Third commit"
cd ..
cp -r KONF_4 KONF_4_copy

#2 rabse dev to main and then interactive rebase with 2 commits
cd KONF_4 
git switch main
git rebase dev
git lol
git rebase -i HEAD~2
git lol

#3
git tag v1.0.0

#4 the same on remote repo initial commit made automatically
cd ..
git clone https://gitlab.com/Karim-Salem/konf
cd konf 
git switch -c dev
echo "Hello World" > hello.txt
git add . && git commit -m "Initial commit"
echo "Hello World" > hello2.txt
git add . && git commit -m "Second commit"
git push --set-upstream origin dev
git switch main
git rebase dev
git lol 
git rebase -i HEAD~2 
git tag v1.0.0
git push origin main



