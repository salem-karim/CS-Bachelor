#!/bin/bash

# Install git on Linux or MacOs using the package manager and in Windows using the installer

git init
# Creates a new repository in the current directory with the master branch
# This will create a new subdirectory named .git that contains all of your necessary repository files

git init --help
# Show all the options for the git init command

git config --global user.name "Your Name"
git config --global user.email "youremail@email.com"
# Set the name and email address you want to use with your commits
# The global settings are stored in the .gitconfig file in your home directory

git config --help
# Show all the options for the git config command

touch text.txt
# Create a new files
echo "Hallo Ich bin Eine textfile" >> text.txt 
# Add some text into the file

git status
# Show the status of the working directory and the staging area
# It shows which changes have been staged, which haven't, and which files aren't being tracked by Git nad wich branch you are on

git add text.txt
# Add the file to the staging area
git commit -m "Add text.txt"
# Commit the file to the repository and add a message with the -m flag
# The output will show the changes that were committed
# For new files nee to be added to the staging area before they can be committed
# Can also be done in on command with git commit -m "Add text.txt" -a after a first inital add command 
# git stores the file exactly as it is at the moment of the commit 

# I have created a commit Object which is stored in the .git directory
git log
# Here I can see all commit objects that I have created with their SHA-1 hash, author, date and commit message

# git show <SHA-1 hash>:text.txt SHA is unique to each commit object

echo -n "Hello World!" | git hash-object -w --stdin
# Outputs the SHA hash of Hello World! and stores the object in the .git/objects directory

git commit -m "Empty commit" --allow-empty
# Create a new commit object with the message "Empty commit" and the --allow-empty flag to allow an empty commit 
# The blob object is saved in the .git/objects directory

git log --graph --decorate --oneline --all

git config --global alias.lol "log --graph --decorate --oneline --all"
git lol
# Create an alias for the command above
# Show the commit history in a graph with the SHA-1 hash, author, date and commit message

touch newfile.txt 

git add newfile.txt 

git commit -m "Add newfile.txt"

git checkout -b new-branch
# Create a new branch and switch to it 

touch anotherfile.txt 

git add anotherfile.txt 

git commit --amend --no-edit
# Amend the last commit with the changes made to anotherfile.txt without changing the commit message and on which branch its saved

rm anotherfile.txt 
# Remove the file 

git commit -a -m "Deleted anotherfile.txt"
# Commit the changes to the repository and add a message with the -m flag

git checkout HEAD^ -- anotherfile.txt 
# Restore the file from the last commit 

echo "Hallo Ich bin noch eine textfile" >> newfile.txt
# Add some text to the file 

git status
# Show htat the file has been modified and is not staged for commit

git add newfile.txt 
git commit -m "Add more text to newfile.txt"
# Commit the changes to the repo

git lol

git checkout HEAD^ 
# Switch to the last commit 
# HEAD is a reference to the current commit
# HEAD^ is a reference to the parent of the current commit
# master is the default branch name in git
# Other options are HEAD~2, HEAD~3, HEAD~4, etc.

git lol


