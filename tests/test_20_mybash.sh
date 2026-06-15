#!/bin/bash
# test_20_mybash.sh - Test script for mybash

# Go to the mybash exercise directory
cd ../exercises/20_mybash

# Create command file
cat > /tmp/mybash_test_commands.txt << 'EOF'
myfile src/myfile/obj/myfile.o
myfile src/mybash/bin/mybash
mysed s/Unix/Linux/ "linux is opensource. unix is free os."
mytrans src/mytrans/text.txt
mywc src/mytrans/text.txt
EOF

# Run mybash with the command file
./src/mybash/bin/mybash /tmp/mybash_test_commands.txt

# Cleanup
rm -f /tmp/mybash_test_commands.txt
