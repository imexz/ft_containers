#!/bin/bash

# run this script from ft_containers directory!

make clean

mkdir ./tests/logs

echo TEST1:
c++ -Wall -Wextra -Werror -std=c++98 -D BUILD_STD=1 ./tests/test1.cpp -o std_containers1
echo Time std:
time ./std_containers1 seed > ./tests/logs/output_std1
c++ -Wall -Wextra -Werror -std=c++98 ./tests/test1.cpp -o ft_containers1
echo
echo Time ft:
time ./ft_containers1 seed > ./tests/logs/output_ft1
diff ./tests/logs/output_std1 ./tests/logs/output_ft1 > ./tests/logs/diff1.diff
echo
echo Result:
if [ -s ./tests/logs/diff1.diff ]
	then
		echo Error
	else
		echo OK
fi

echo
echo TEST2:
c++ -Wall -Wextra -Werror -std=c++98 -D STDSTL=1 ./tests/test2.cpp -o std_containers2
echo Time std:
time ./std_containers2 seed > ./tests/logs/output_std2
c++ -Wall -Wextra -Werror -std=c++98 ./tests/test2.cpp -o ft_containers2
echo
echo Time ft:
time ./ft_containers2 seed > ./tests/logs/output_ft2
diff ./tests/logs/output_std2 ./tests/logs/output_ft2 > ./tests/logs/diff2.diff
echo
echo Result:
if [ -s ./tests/logs/diff2.diff ]
	then
		echo "Possible Error. Check diff2.diff! (Diff in Leaks and Performance Report is OK.)"
	else
		echo OK
fi

echo
echo TEST3:
c++ -Wall -Wextra -Werror -std=c++98 ./tests/test3.cpp -o std_containers3
echo Time std:
time ./std_containers3 seed > ./tests/logs/output_std3
c++ -Wall -Wextra -Werror -std=c++98 -D FT ./tests/test3.cpp -o ft_containers3
echo
echo Time ft:
time ./ft_containers3 seed > ./tests/logs/output_ft3
diff ./tests/logs/output_std3 ./tests/logs/output_ft3 > ./tests/logs/diff3.diff
echo
echo Result:
if [ -s ./tests/logs/diff3.diff ]
	then
		echo Error
	else
		echo OK
fi
