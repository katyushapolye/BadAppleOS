
rm Dumps/* -f
# Define the directory containing the files
directory="Kernel/object/"
directorydump="Dumps/"

# Check if the directory exists
if [ ! -d "$directory" ]; then
    echo "Directory $directory does not exist."
    exit 1
fi

# Loop through each file in the directory
for file in "$directory"/*; do
    # Check if the file is a regular file (not a directory)
    if [ -f "$file" ]; then
        # Get the file name without the path
        filename=$(basename "$file")
        
        # Execute objdump command and save output to a text file
        objdump -s "$file" > "${directorydump}/${filename}.txt"
        echo "objdump -s $file > ${directorydump}/${filename}.txt"
    fi
done

echo "Done!"