#!/bin/bash

# Automates replacing lines containing given string with a different line
function replaceLine() {
  # Takes arguments in following format:
  #   replaceLine <replace lines containing this string> <replace with this string> <Replace in this file>
  sed -i "s/.*$1.*/$2/g" $3
}

# Remove lines with given string
function removeLine() {
  # Takes arguments in following format:
  #   removeLine <remove lines containing this string> <Remove in this file>
  sed -i "/.*$1.*/d" $2
}

# Get/return the PID of a command
# Be aware, this will only return a single PID
# (if there are multiple processes with this command name, only one will be returned)
function getPID() {
  # Takes arguments in following format:
  #   getPID <command>
  cmd=$1
  ps -e | grep $cmd | awk '{print $1;}'
}

# Reverts branch based on number of commits given as argument
# i.e. an argument of 3 would undo the 3 latest commits
function undoNCommits() {
  # Takes an argument in the following format:
  #   undoNCommits <number of commits to undo>
  hash= $(git log -n $1 --pretty=format:"%H" | tail -1)
  git revert $hash

}

# Helpful aliases
alias sl="ls --color=auto"
alias ls="ls --color=auto"
alias untar='tar -zxvf'
alias grep='grep --color=auto'
alias top='top -H' # Show all threads and not just parent processes
alias diff='diff -y' # Make diff more human-readable by using the side-by-side version
