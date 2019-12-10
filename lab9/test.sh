./sig_nanosleep &

tmp=`ps aux | grep 'sig_nanos*' | head -1 | tr '[:blank:]' '\n' | tr -s '\n' | head -2 | tail -1`

echo $tmp

i=1
while [ $i -lt 6 ]; do
kill -10 $tmp
sleep 2
i=$(($i+1))
done
