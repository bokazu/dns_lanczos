#! /bin/bash

for i in {1..10}; do
    #fileは各ループごとに上書きされる
    echo ""
    echo "i = $i"
    echo "sample/sample0.txt" | tee set_model/set_filename.txt >/dev/null 
    echo -n "output/output$i.txt" | tee  -a set_model/set_filename.txt >/dev/null
    echo -e "\n"
    cat set_model/set_filename.txt

    make run
done