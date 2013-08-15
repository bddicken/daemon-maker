daemon-maker
============

A tool to turn a bash command into a daemon.

For example, say you have a C project you're working on. You are sick and tired of running `make` all the time, so you want a way to automate it. With this tool, simply cd into your project directory and run:

`dm -c 'make' -i 5 -t 6000`

This will start a background daemon process, that runs `make` in the current directory, every 5 seconds, for the next 6000 seconds (1 hour and 40 mins). 
