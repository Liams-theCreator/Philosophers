# Tests for the project
#
# ./philo 1 0 0 0 0 program should quit, or the behavior is undefined, avoid segfaults.
# Err!!
# any values in the timing below 60ms, is considered undefined.
#
# ./philo 1 100 500 500
# --> philosopher should died at 100
# 100 1 died
#
#
# ./philo {2..180} 120 60 60 (only even number of philos)
# the loop goes on and no philo should ever die
#
# ./philo {3..189} 180 60 60 (for odd number of philos)
#
# ./philo Any invalid args like non numerical (12ae , 00, 1440- , +++++++12, 1212.12, 543,4 ......)
