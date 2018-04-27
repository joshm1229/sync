# About
Command-line utility to sync two folders in Windows 

# Usage
sync <folder1> <folder2>

# Current State
The program syncs files across two folders, but only goes 1 layer deep. Files located inside sub-folders will not be copied, but the folder itself will be created. The two folders are entered as command-line arguments, and the program uses filenames to compare two files. 
 
# Future Road-map
-Recursion to sync files inside sub-folders. 
-Comparison of file contents and timestamps 
