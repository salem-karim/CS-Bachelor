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
git diff
# it shows the changes that have been made to the File

# 5 Commit the changes
git commit -m "Changed text.txt in developmetn branch"
git lol
# Head is pointiong to the development branch which is in front of the master branches

# 6 accidentally commited restore history to it prevoius state
git reset --hard HEAD^
# --hard flag resets the working directory and the staging area to the previous commit 
# --soft flag only resets the HEAD to the previous commit
# other options are --mixed which resets the staging area to the previous commited
# --merge which resets the working directory and the staging area to the previous commit and keeps the changes in the working directory
# --keep which resets the working directory and the staging area to the previous commit and keeps the changes in the working directory

# 7 Changes 2
echo "Hello World!" >> text.txt
git commit -a -m "Changed text.txt in development branch"

# 8 .git ignore files that end with .o 
echo "*.o" > .gitignore
echo "Hello World!" > main.o 
git add main.o
# The file is not staged because it is ignored by the .gitignore file suggested to use git add -f to force the add

# 9 Inn the .git directory what do you now notice
# IN the .git directory there is a file called .gitignore that contains the pattern *.o

# 10 Feature Branches 
# After developing a lot and commiting the history is a mess
#





