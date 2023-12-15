
if [[ -d ".git" ]] 
then 
	: #noop
else
	echo "Initialising git ..."
	git init -b main
fi

for i in {01..25}
do
	echo "Initialising directory for day $i"
	mkdir -p day_$i
	cd day_$i 

	# Main C file
	mkdir -p src
	echo "#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	FILE* file;
	if (argc > 1) {
		file = fopen(argv[1], \"r\");
	} else {
		file = fopen(\"input.txt\", \"r\");
	}
	
	while(!feof(file)) {
		// Code goes here
	}
	
	fclose(file);
	return 0;
}
" > src/main.c

	# Build script
	echo "mkdir -p build
clang src/main.c -o build/day_$i" > build.sh

	# Files for tests
	mkdir -p test_data/example
	touch test_data/example/input.txt
	touch test_data/example/output.txt
	mkdir -p test_data/input
	touch test_data/input/input.txt
	touch test_data/input/output.txt

	# Test script
	echo "input=\"input.txt\"
output=\"output.txt\"

test () {
  local errors=0
  local successes=0
  local failures=0

  ./build.sh
  
  for d in \$@
  do
    echo \"Testing \$d\"
    local out=\"not empty\"
    { 
      out=\$(./build/day_$i \$d/\$input | diff \$d/\$output -)
    } || {
      ((errors++))
    }
    { 
      if [ -z \$out ]
      then
        ((successes++))
      else 
        ((failures++))
      fi
    } 
  done

  echo \"Tested : \$# | Successes : \$successes/\$# | Failures : \$failures | Errors : \$errors\"

  if [ \"0\" -eq \$failures ]
  then 
    exit 0
  else
    exit 1
  fi
}

test \$(ls -d ./test_data/* | cat)
" > test.sh

	# Files for each day
	touch in.txt
	touch ex.txt

	# .gitignore build files
	echo "build/*" > .gitignore
	cd ..
done

# README
echo "# Advent of Code 2020

My solutions for the Advent of Code 2020, done in 2023." > README.md

# Global test script
echo "args=\"\"

test () {
  local successes=0
  local failures=0
  local skipped=0

  for d in \$@
  do
    d=\${d::-1}
    echo \"== Testing \$d ==\"
    cd \$d
    if [ -f \"test.sh\" ]
    then
      ./test.sh \$args
      local out=\$?
      if [ \"0\" -eq \$out ]
      then
        ((successes++))
      elif [ \"1\" -eq \$out ] 
      then
        ((failures++))
      elif [ \"2\" -eq \$out ]
	  then
	  	echo \"Skipped\"
	  	((skipped++))
	  fi
    else 
      echo \"Skipped\"
      ((skipped++))
    fi
    echo \"\"
    cd ..
  done

  echo \"Test suites : \$# | Skipped : \$skipped | Successful : \$successes | Failed : \$failures\"

  if [[ \$* == *--all* ]]
  then 
	noop
  else
  	echo \"Skipped some tests, to enable them add the '--all' flag\"
  fi
}

if [[ \$* == *--all* ]]
then
	args=\"--all\"
fi
test \$(ls -d */ | cat)
" > test.sh

# License informations
echo "This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>
" > LICENSE

git add .
git commit -m "Initial commit"
git remote add origin git@github.com:EcklerOChokola/AOC_20.git
git branch -M main
git push -u origin main
