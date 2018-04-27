#include <stdio.h> //Input/Output
#include <windows.h> //Used for Windows API
#include <dirent.h> //opendir, readdir
#include <sys/stat.h> //used to pull info about files
#include <stdlib.h> //exit
int createDir(char *filename) { //creates a new directory
    char command[7+strlen(filename)];
    strcpy(command, "mkdir ");
    strcat(command, filename);
    printf("%s\n", command);
    return system(command); //runs "mkdir filename" on the system
}

int createFile(char *filename1, char *filename2) { //copies filename1 to a new file at filename2
    char command[11+strlen(filename1)+strlen(filename2)];
    strcpy(command, "copy \"");
    strcat(command, filename1);
    strcat(command, "\" \"");
    strcat(command, filename2);
    strcat(command, "\"");
    printf("%s\n", command);
    return system(command); //runs "copy filename1 filename2" on the system
}

int fileExists(char *filename) { //returns 1 if file exists, 0 otherwise
    struct stat buffer;
    return (stat(filename, &buffer)==0);
}

int isDir(char *filename) { //returns 1 if file is directory, 0 otherwise
    struct stat buffer;
    stat(filename, &buffer);
    if ((buffer.st_mode & S_IFDIR) == S_IFDIR) {
        return 1;
    }
    else  
        return 0;
}

int main(int argc, char *argv[]) {
    //Check number of arguments
    if (argc != 3) {
        printf("Invalid number of arguments.");
        return 1;
    }
    
    //setup variables
    char folder1path[260];
    char folder2path[260];
    char fullpath1[260]; //these variables are used for comparisons
    char fullpath2[260]; 
    strncpy(folder1path, argv[1], 260);
    strncpy(folder2path, argv[2], 260);
    struct dirent *dir; //declare dirent struct
    DIR *dp = opendir(folder1path); //attempt to open directory, dp is directory pointer
    if (dp == NULL) { //if directory cannot be opened, exit program
        printf("Failed to open directory %s. Exiting program.\n",folder1path);
        return 1;
    }
    //This loops runs through all items in the first directory and checks if they are present in the second directory
    while ((dir = readdir(dp)) != NULL) { //read all items in the directory
        memset(fullpath1,0,sizeof(fullpath1)); //zero out array
        strncpy(fullpath1,folder1path,strlen(folder1path)); //copy folder1 path
        strcat(fullpath1, "\\"); //append '\' to folder1 path
        strcat(fullpath1, dir->d_name); //append file name to folder1 path
        memset(fullpath2,0,sizeof(fullpath2)); //zero out array
        strncpy(fullpath2,folder2path,strlen(folder2path)); //copy folder2 path
        strcat(fullpath2, "\\"); //append '\' to folder2 path
        strcat(fullpath2, dir->d_name); //append file name to folder2 path
        if (!fileExists(fullpath2)) { //If fullpath2 does not exist, create it
            (isDir(fullpath1)) ? createDir(fullpath2) : createFile(fullpath1, fullpath2); 
        }
    }
    dp = opendir(folder2path); //attempt to open second directory
    if (dp == NULL) { //if directory cannot be opened, exit program
        printf("Failed to open directory %s. Exiting program.\n",folder2path);
        return 1;
    }
    //This loops runs through all items in the second directory and checks if they are present in the first directory
    while ((dir = readdir(dp)) != NULL) { //read all items in the directory
        memset(fullpath2,0,sizeof(fullpath2)); //zero out array
        strncpy(fullpath2,folder2path,strlen(folder2path)); //copy folder2 path
        strcat(fullpath2, "\\"); //append '\' to folder2 path
        strcat(fullpath2, dir->d_name); //append file name to folder2 path
        memset(fullpath1,0,sizeof(fullpath1)); //zero out array
        strncpy(fullpath1,folder1path,strlen(folder1path)); //copy folder2 path
        strcat(fullpath1, "\\"); //append '\' to folder2 path
        strcat(fullpath1, dir->d_name); //append file name to folder2 path
        if (!fileExists(fullpath1)) { //If fullpath2 does not exist, create it
            (isDir(fullpath2)) ? createDir(fullpath1) : createFile(fullpath2, fullpath1); 
        }
    }
    closedir(dp);
    return 0;
}