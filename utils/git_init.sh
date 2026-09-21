#!/bin/bash
if (($# == 0)); then
	echo "This is script for creating git & github repo"
	exit 0
fi
if (($# > 2)); then
	echo "This script do not take more than 2 arguments"
	exit 1
fi

NAME=""
MAIL=""
BRANCH=""

if (( ! -f "../.git_myconfig" )); then
	read -p "There is no .git_myconfig file. Create it? [y/n]: " ANSWER
	if  [[ "$ANSWER" != "y" ]]; then
		echo "Stopping script"
		exit 1;
	fi
	read -p "Username: " NAME
	read -p "Email: " MAIL
	read -p "Branch: " BRANCH
	cat > ../.git_myconfig << EOF
	USER_NAME="$NAME"
	USER_EMAIL="$MAIL"
	USER_BRANCH="$BRANCH"
	EOF
else
	source ../.git_myconfig
	NAME="$USER_NAME"
	MAIL="$USER_EMAIL"
	BRANCH="$USER_BRANCH"
fi

CATALOG_NAME="$1"

if git rev-parse --is-inside-work-tree > /dev/null 2>&1; then
    echo "Error: current directory is inside a Git repository"
    exit 1
fi

if [[ -d "$CATALOG_NAME" ]]; then
	if [[ -n "$(find "$CATALOG_NAME" -mindepth 1 -maxdepth 1 -quit)" ]]; then
    		echo "Catalog with same name already exist & is not empty"
		if [[ -d "$CATALOG_NAME/.git" ]]; then
        		if (( $# == 2 )); then
           			cd "$CATALOG_NAME" || exit 1
            			git remote add origin "$2"
            			echo "Remote repository added."
            			exit 0
			fi
		fi
		exit 1
	else 
		echo "Catalog with same name exist & is empty."
	fi
else
	mkdir "$CATALOG_NAME"
fi

cd "$CATALOG_NAME"
git init . || exit 1
git config --local user.name "$NAME"
git config --local user.email "$MAIL"
git config --local init.defaultBranch "$BRANCH"
touch .gitignore
echo "# $CATALOG_NAME" >> README.md

if (( $# == 1)); then
	echo "Script is done"
	exit 0
fi

if git remote add origin "$2"; then
	echo "Script is done"
	exit 0
else 
	echo "Failed to add remote repo"
	exit 1
fi

exit 1
