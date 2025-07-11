yes &
fg
jobs
ps f
ps -f
ps -f | grep 1232
ps -f | grep 1232 | awk '{print $2}'
ps -f | grep 1232 | awk '{print $2}' | xargs kill -9
killall yes
kill 1232
