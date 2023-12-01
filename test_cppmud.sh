#!/usr/bin/env bash

rm -f RESULT DEBUG STDERR output.txt raw_output.txt

testcase=$1
if [[ -z "$testcase" ]]; then
  testcase=1
fi
showdebug=$2

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

testcnt=1
output_fn="./output.txt"

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
if [[ -d /usercode ]]; then
  cd /usercode || exit 33
else
  cd "$DIR" || exit 33
fi

###########################################################################################
#  START FUNCTIONS SECTION
###########################################################################################

# Function to be called upon exit
function on_exit() {
    if grep -E "^p" RESULT > /dev/null; then
      echo "Exiting tester." >> DEBUG
    else
      showOutput
      echo "Error occurred, exiting tester ." >> DEBUG
    fi
    if [[ "${DIR}" == *"/tests"* || ! -z "$showdebug" ]]; then
         cat DEBUG RESULT
    fi
}

# Trap the exit signal to call on_exit function
trap on_exit EXIT

function standardExec(){
  ./a.out "$@" > output.txt < INPUT 2>> DEBUG
}

function testoutput(){
  EXPECTED="$1"
  grep_opts="$2"

  while IFS=" " read -r line; do
    if cat output.txt | tr -d " " | grep ${grep_opts} "${line// /}" > /dev/null ; then
      continue
    else
      log_neg "\t\033[38;5;3mMISSING '${line}' in output. \033[0m \n"  >> DEBUG
      return 1 ## BASH thinks this is False
    fi
  done <<< $EXPECTED

  return 0 ## BASH is fun, this is True
}


function showOutput() {

	if [[ -f INPUT ]]; then
	  echo "---- std input ---- " >> DEBUG
	  cat INPUT >> DEBUG
	fi
	if [[ -f raw_output.txt ]]; then
    echo -e "\n---- std out  ---- " >> DEBUG
    cat raw_output.txt >> DEBUG
    printf "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" >> DEBUG
  elif [[ -f output.txt ]]; then
    echo -e "\n---- std out   ---- " >> DEBUG
    cat output.txt >> DEBUG
    printf "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" >> DEBUG
  fi

}

function compile(){

  rm -f a.out
  binary_fn="./mud.bin"

  foundcpp=false

  make -j 5 >> DEBUG 2>&1

  compile_ret=$?

  if [[ $compile_ret -ne 0 ]]; then
      printf "\t\033[38;5;3mFAILED to compile \033[0m \n" >> DEBUG
      echo "np" > RESULT
      exit 44
  fi
}

log_pos() {
    msg="$1"
    printf "\t${testcnt}. \033[38;5;10m✔ ️$msg\033[0m\n" >> DEBUG
    testcnt=$(( testcnt + 1 ))
}
log_neg() {
    msg="$1"
    printf "\n\033[38;5;3m$msg\033[0m\n" >> DEBUG
    echo "np" > RESULT
}

###########################################################################################
#  START FUNCTIONS SECTION
###########################################################################################


compile

printf "\033[38;5;6mTesting test case #${testcase}\033[0m\n" >> DEBUG

touch INPUT
grepopts=""

if [[ "$testcase" -eq 1 ]]; then
  printf "s
s
s
e
e
s
s
s
quit
" > INPUT
  EXPECTED="Market Square
Common Square
Dark Alley
Alley at Levee
Levee
Kate
"
elif [[ "$testcase" -eq 2 ]]; then
  printf "Inventory Test\n" >> DEBUG
  printf "s
s
get ring
get vest
i
quit
" > INPUT
EXPECTED="The Temple Of Mota
The Temple Square
"
  ./mud.bin < INPUT > output.txt 2>> /dev/null
    line="ring signet"
    sigCount=$(cat output.txt | tr -d " " |grep -i "${line// /}" | wc -l)
    line="vest standard merc"
    vestCount=$(cat output.txt | tr -d " " |grep -i "${line// /}" | wc -l)

    if [[  $sigCount -eq 3 && $vestCount -eq 4 ]]; then
      echo "Found 'signet ring' and 'vest standard merc' expected number of times " >> DEBUG
    else
      printf "\033[38;5;1mFailed, found the 'ring signet' in output $sigCount times and expected 3 \033[0m\n"
      printf "\033[38;5;1m        found the 'vest standard merc' in output $vestCount times and expected 4 \033[0m\n"
      echo "np" > RESULT
      exit 1
    fi
elif [[ "$testcase" -eq 3 ]]; then
  printf "Drop with multiple items in a single room\n"
  printf "s
s
get ring
get vest
n
n
drop
1
drop
1
quit
" > INPUT
  grepopts=" -E "
  EXPECTED="banner war merc, sword standard merc,.*helmet standard merc
scimitar blade, ring signet,.*vest standard merc
"
elif [[ "$testcase" -eq 4 ]]; then
  printf "Upstairs to Different Zone\n" >> DEBUG
  python3 -c "print('n\nn\n' + 'u\n'*10  + 'quit\n')" > INPUT

  EXPECTED="On the Rainbow Bridge
1220
Heimdall
"

elif [[ "$testcase" -eq 5 ]]; then
  printf "East to Thalos then attack tourist\n" >> DEBUG
  python3 -c "print('s\ns\n' + 'e\n'*24 + 'attack\nquit\n' )" > INPUT
  grepopts=" -E "
  EXPECTED="Inside the West Gate of New Thalos
9528
nomad
raistlin
killed.*tourist
"

elif [[ "$testcase" -eq 6 ]]; then
  printf "Look at Standard Helmet 2 south\n" >> DEBUG
  python3 -c "print('south\nsouth\nlook helmet\nquit\n' )" > INPUT

  EXPECTED="You see a standard issue helmet here"

elif [[ "$testcase" -eq 7 ]]; then
  printf "Teleport to 3556\n" >> DEBUG
  python3 -c "print('teleport 3556\nquit\n' )" > INPUT

  EXPECTED="Goblin Headquarters
goblin mountain
sword short, sword short, helmet horned black
"
elif [[ "$testcase" -eq 8 ]]; then
  printf "Teleport to 3472\n" >> DEBUG
  python3 -c "print('teleport 3472\nnorth\nwest\ndown\nwest\nwest\nattack\nattack\nquit\n' )" > INPUT
  grepopts=" -E "
  EXPECTED="Ancient Room
10404
Guardian
killed.*Guardian
"
elif [[ "$testcase" -eq 9 ]]; then
  printf "Teleport to 3268, move to moria\n" >> DEBUG
  python3 -c "print('teleport 3268\nnorth\nquit\n' )" > INPUT
  EXPECTED="Outside the North Gate of Midgaard
3904
The long dusty trail following the north wall
"
else
  echo "INAVLID TEST CASE OPTION " >> DEBUG
  echo 'np' > RESULT
  exit 139
fi

./mud.bin < INPUT > output.txt 2>> /dev/null


if testoutput "$EXPECTED" "-i ${grepopts}"; then
  echo 'p' > RESULT
  log_pos "PASSED, passed all tests"
else
  echo 'np' > RESULT
  exit 95
fi


