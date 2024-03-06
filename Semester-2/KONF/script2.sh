#!/bin/bash


#1 bracnhing
git branch development
git checkout development
#options for branch are -d to delete branch -m to rename branch -r to list remote branches -a to list all branches -v to show the last commit on each branches
# options for checkout are -b to create a new branch and switch to it -t to track a remote branch -f to force the checkout -m to move/rename the branches

# 2 Documentation
git lol
# Show that the HEAD is pointing to the development branches

# 3 Ch ange a File
echo "Hello World!" >> text.txt
git add text.txt
git status
git lol
# shows that we are on the development branch and that the file has been modified and staged history has not changed

# 4 Diff
git restore --staged text.txt
git diff
git add text.txt
# it shows the changes that have been made to the File

# 5 Commit the changes
git commit -m "Changed text.txt in developmetn branch"
git lol
# Head is pointiong to the development branch which is in front of the master branches

# 6 accidentally commited restore history to it prevoius state
git reset --mixed HEAD^
git lol
# mixed is deafult option and it unstages the file and keeps the Changes
# soft keeps the staged changes 
# hard discards the changes

# 7 Changes 2
echo "Even More Text" >> newfile.txt
git commit -a -m "Changed text.txt in development branch"

# 8 .git ignore files that end with .o 
echo "*.o" > .gitignore
echo "Hello World!" > main.o 
git add .
git status
# The file is not staged because it is ignored by the .gitignore file suggested to use git add -f to force the add

# 9 Inn the .git directory what do you now notice
# IN the .git directory there is a file called .gitignore that contains the pattern *.o

# 10 Feature Branches 
git checkout -b feature 
echo "Hello New Features here are some new features" >> feature.txt
git add feature.txt 
git commit -m "Added feature.txt"
git lol
# shows that the head is pointing to the feature branch and that the feature.txt file has been Added

# 11 hotfix 
git checkout master
git checkout -b hotfix
echo "Jsut fixing a bug here" >> hotfix.txt
git add hotfix.txt 
git commit -m "Fixed a bug for master branch" 
git checkout master && git merge hotfix
git lol

# 12 Finish Feature 
git switch feature 
echo "Some more features" >> feature.txt 
git commit -a -m "Added more features"
git merge hotfix

# 13 Delete branches 
git switch master && git merge feature 
git branch -d feature && git branch -D hotfix 
git lol 
# -d deletes only merged branches -D can also deletes unmerged branches







