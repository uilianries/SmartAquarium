#/bin/bash

cd build
for app in test/application/test_application test/device/test_device
do
    $app
    if [ $? -ne 0 ]; then
        exit 1
    fi
done
exit 0
