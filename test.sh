failed=0
succeed=0

for file in $( ls ./input/*.s );
do
    as=$( basename $file .s )
    printf "test case: ./assembler input/%s.s out/%s.int out/%s.out\n" $as $as $as
    ./assembler input/"$as".s out/"$as".int out/"$as".out

    if [ $? -eq 0 ]
    then
        printf "diff ./out/%s.int ./out/ref/%s_ref.int\n" $as $as
        diff ./out/"$as".int ./out/ref/"$as"_ref.int
        if [ $? -eq 0 ]
        then
            printf "diff ./out/%s.out ./out/ref/%s_ref.out\n" $as $as
            diff ./out/"$as".out ./out/ref/"$as"_ref.out
        fi
    fi

    if [ $? -eq 0 ]
    then
        echo "Succeed."
        succeed=$(($succeed+1))
    else
        echo "Failed!"
        failed=$(($failed+1))
    fi
    echo
done

echo "Failed case: " $failed " Succeed case: " $succeed