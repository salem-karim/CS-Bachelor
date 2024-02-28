#!/bin/bash

#1 Install git on Linux or MacOs using the package manager and in Windows using the installer

mkdir gittest
cd gittest

#2 Creates a new repository and the .git folder in the current directory with the master branch
git init

#3 Set the name and email address you want to use with your commits
git config --global user.name "Your Name"
git config --global user.email "youremail@email.com"
# The settings are stored in the .gitconfig file in the home directory

#4 Create a new files and add some text to it
echo "Hallo Ich bin eine Textfile" > text.txt 

#5 Show the status of all the files in the git ropsitory 
git status
#Shows that the file is untracked

#6 Add the file to the staging area creates a blob object in the .git/objects directory and prepares the file for commit
git add text.txt

#7 Outputs the SHA-1 hash of the added file 
git hash-object text.txt

#8 Outputs the content of the file with the SHA-1 hash
git cat-file -p 0d14234b522f5638ae653b7546efea58b0503365

#9 & 10 Outputs the SHA hash of Hello World! and stores the object in the .git/objects directory
echo -n "Hello World!" | git hash-object -w --stdin
# the -w flag writes the object into the .git driectory and the --stdin flag reads the input from the standard input

#11 Commit the changes to the repository and add a message with the -m flag
git commit -m "My first commit"
# The commit and tree object is saved in the .git/objects directory and for all the options use git commit --help
# The commit object contains the reference to the tree object and the tree object contains the reference to the blob object

#12 Create an alias for the command git log --graph --decorate --oneline --all
git config --global alias.lol "log --graph --decorate --oneline --all"

#13 Show the commit history of the repository in a more readable format
git lol

#14 Create a new File and commit the changes to the repository
echo "Hello World!" > newfile.txt
git add newfile.txt 
git commit -m "Added newfile.txt"

#15 Amend a forgotten change to the last commit
echo "Opps I forgot to add this" > anotherfile.txt
git add anotherfile.txt 
git commit --amend --no-edit
# Amend creates a new commit object but put it together with the previous commit object for a cleaner history

#16 Remove the file 
git rm anotherfile.txt 
git commit -m "Deleted anotherfile.txt"
# Commit the changes to the repository and add a message with the -m flag
git checkout HEAD^ anotherfile.txt 
# Restore the file from the last commit HEAD^ is a reference to the previous commit

#16 Add some text to the file 
echo "Hallo Ich bin neuer Text" > text.txt
git status
# Show modified file on the current branch and suggests to add or restore the file and the commit the changes
git commit -a -m "Add more text to text.txt"
#Stage all modified Files and Commit the changes to the repository and create a new commit object 

#18 Lok at the history go to the previous version and show the history again
git lol
git checkout HEAD^ 
git lol
# HEAD is a reference to the current commit
# Other options are HEAD~2, HEAD~3, HEAD~4, etc. to go back 2, 3, 4, etc. commits



