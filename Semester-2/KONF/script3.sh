#!/bin/bash 

# 2 Clone remote repo
git clone https://gitlab.com/Karim-Salem/konf.git
git lol 
cd konf
git lol

# 3 Create a local copy
mkdir test
cd test
git init
git remote add origin https://gitlab.com/Karim-Salem/konf.gitlab
git pull origin main 

cd ..
echo "remote file" > konf/remote.txt
echo "local file" > test/local.txt

# 4 commit and try pushing on both 
cd konf
git add remote.txt
git commit -m "Add file"
git push origin main

cd ../test
git add local.txt
git commit -m "Add file"
git push origin main
git pull origin main
git push origin main

# 5 Create a conflict
cd ../konf/
git pull origin main
echo "New Conflict" > conflict.txt
git add conflict.txt
git commit -m "Conflict :)"
git push origin main
cd ../test
git push origin main
git pull origin main
git push origin main

# 6 Add a tag
cd ../konf/
echo "First Release" > release1.0.0.txt
git add release1.0.0.txt
git commit -m "First Release"
git tag -a 1.0.0 -m "First Release"
git tag
git push origin main --tags
cd ../test/ && git pull origin main --tags

# 7 2 Features
cd ../konf/
git switch -c FeatureOne
echo "Feature One" > featureone.txt
git add featureone.txt
git commit -m "First Feature"
git switch main
git merge FeatureOne
git push origin main

# Second 
git switch -c FeatureTwo
echo "Feature Two" > featuretwo.txt
git add featuretwo.txt
git commit -m "Second Feature"
git switch main
git merge FeatureTwo
git push origin main

# 8 Minor Major release 
git switch -c deployment
echo "Minor Feature" > Minor.txt
git add Minor.txt
git commit -m "Minor Feature"
git tag -a 1.1.0 -m "Minor Release"
git push origin deployment --tags
git switch main
git merge deployment
git push origin main

# Major
git switch deployment
echo "Major Feature" > Major.txt
git add Major.txt
git commit -m "Major Feature"
git tag -a 2.0.0 -m "Major Release"
git push origin deployment --tags
git switch main
git merge deployment









