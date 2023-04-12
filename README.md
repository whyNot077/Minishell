# Create a simple shell, as beautiful as bash

### reference

[GNU Bash Manual][bash]  
[Posix shell][posix]  
[Shell Grammar Rules][shell]  
[Base Definitions][base]  
[LL parser][ll]  
[Chomsky hierarchy][chom]  

[bash]: https://www.gnu.org/software/bash/manual/bash.html
[posix]: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/contents.html
[shell]: https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_10_02
[base]: https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/
[ll]: https://en.wikipedia.org/wiki/LL_parser
[chom]: https://en.wikipedia.org/wiki/Chomsky_hierarchy  


### External Functions
<details>
<summary>readline, printf, write, malloc, free </summary>
<div markdown="1">

### readline
Reads a line from the user input (stdin) and returns it as a dynamically allocated string. The user can edit the input line with various editing commands similar to those used in Unix command line environments.  
```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input = readline("Enter a string: ");
    printf("You entered: %s\n", input);
    free(input);
    return 0;
}
```

### rl_clear_history
Clears the entire history of input lines previously read by readline.  
```c
#include <readline/readline.h>
#include <readline/history.h>

void clear_history_and_exit() {
    rl_clear_history();
    exit(0);
}
```

### rl_on_new_line
Indicates that the cursor is on a new line, allowing readline to maintain proper screen output.  
```c
#include <readline/readline.h>

void print_new_line() {
    rl_on_new_line();
    rl_redisplay();
}
```

### rl_replace_line
Replaces the current line buffer with a new string, without redisplaying the new line.   
```c
#include <readline/readline.h>

void replace_current_line(const char *new_line) {
    rl_replace_line(new_line, 0);
}
```

### rl_redisplay
Refreshes the display of the input line, useful after modifying the line buffer.   
```c
#include <readline/readline.h>

void refresh_display() {
    rl_redisplay();
}
```

### add_history
Adds the recently-read line to the input history, allowing the user to recall previous lines.   
```c
#include <readline/readline.h>
#include <readline/history.h>

void add_input_to_history(const char *input) {
    add_history(input);
}
```

### printf
Formats and prints a string to the stdout (standard output).   
```c
#include <stdio.h>

int main() {
    int age = 25;
    printf("I am %d years old.\n", age);
    return 0;
}
```

### write
Writes a specified number of bytes from a buffer to a file descriptor.   
```c
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        return 1;
    }

    const char *text = "Hello, World!";
    ssize_t bytes_written = write(fd, text, 13);

    close(fd);
    return 0;
}
```

### malloc & free
malloc allocates a specified size of memory in bytes and returns a pointer to the allocated memory. free deallocates previously allocated memory pointed to by the provided pointer.   
```c
#include <stdlib.h>

int main() {
    int *arr = (int *)malloc(5 * sizeof(int));
    if (!arr) {
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }

    free(arr);
    return 0;
}
```

</div>
</details>

<details>
<summary>access, open, opendir, read </summary>
<div markdown="1">

### access
Checks the access permissions of a file based on the specified mode.   
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    if (access("test.txt", R_OK) == 0) {
        printf("The file test.txt is readable.\n");
    } else {
        printf("The file test.txt is not readable.\n");
    }
    return 0;
}
```

### open & close
open() opens a file with specified flags and mode, returning a file descriptor. close() closes a file descriptor, freeing up system resources.   
```c
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        return 1;
    }

    // Do something with the file descriptor here.

    close(fd);
    return 0;
}
```

### opendir, readdir, closedir
opendir opens a directory stream, readdir reads entries from the directory stream, and closedir closes the directory stream.   
```c
#include <dirent.h>
#include <stdio.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Failed to open directory");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("Found file: %s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
```

### read
Reads a specified number of bytes from a file descriptor into a buffer.   
```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        return 1;
    }

    char buffer[256];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytes_read] = '\0';

    printf("Content: %s\n", buffer);

    close(fd);
    return 0;
}
```
</div>
</details>


<details>
<summary>fork, wait, waitpid, execve, dup, pipe </summary>
<div markdown="1">

### fork
Creates a new process by duplicating the calling process, resulting in a parent and child process with separate memory spaces.
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("I am the child process with pid %d.\n", getpid());
    } else {
        printf("I am the parent process with pid %d.\n", getpid());
    }
    return 0;
}
```

### wait
Suspends the calling process until one of its child processes terminates, returning the child's process ID and exit status.
```c
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        sleep(2);
        return 42;
    } else {
        // Parent process
        int status;
        wait(&status);
        printf("Child exited with status %d.\n", WEXITSTATUS(status));
    }
    return 0;
}
```

### waitpid
Similar to wait, but allows the calling process to wait for a specific child process or any child process that matches the specified process ID.   
```c
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        sleep(2);
        return 42;
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        printf("Child exited with status %d.\n", WEXITSTATUS(status));
    }
    return 0;
}
```

### wait3 & wait4
These functions are similar to wait and waitpid but also return resource usage information about the child process in a struct rusage parameter.
```c
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        sleep(2);
        return 42;
    } else {
        // Parent process
        int status;
        struct rusage usage;
        wait3(&status, 0, &usage); // Use wait4(pid, &status, 0, &usage) to wait for a specific pid
        printf("Child exited with status %d.\n", WEXITSTATUS(status));
    }
    return 0;
}
```

### execve
Replaces the current process image with a new process image specified by the given file. The new process starts executing at its main() function.
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    char *argv[] = { "ls", "-l", NULL };
    char *envp[] = { NULL };

    if (execve("/bin/ls", argv, envp) == -1) {
        perror("Failed to execute ls");
    }
    return 0;
}
```

### dup & dup2
dup creates a new file descriptor that is a duplicate of the specified file descriptor, whereas dup2 duplicates a file descriptor to a specified file descriptor.   
```c
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("test.txt", O_RDONLY);
    int new_fd = dup(fd);
    // new_fd now refers to the same file as fd.

    int another_fd = open("another.txt", O_RDONLY);
    dup2(fd, another_fd);
    // another_fd now refers to the same file as fd, and the previous file is closed.

    close(fd);
    close(new_fd);
    close(another_fd);
    return 0;
}
```

### pipe
Creates a unidirectional pipe, with one end for reading and the other for writing.   
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Failed to create pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close read end
        write(pipefd[1], "Hello from child!", 17);
        close(pipefd[1]);
    } else {
        // Parent process
        close(pipefd[1]); // Close write end
        char buffer[256];
        ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
        buffer[bytes_read] = '\0';
        printf("Received from child: %s\n", buffer);
        close(pipefd[0]);
    }
    return 0;
}
```
</div>
</details>


<details>
<summary>signal, kill</summary>
<div markdown="1">

### signal
Sets a function to handle a specific signal. When the signal is received, the specified handler function is called.   
```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handle_signal(int sig) {
    printf("Signal %d received.\n", sig);
}

int main() {
    signal(SIGINT, handle_signal);

    while (1) {
        sleep(1);
    }
    return 0;
}
```

### sigaction
Similar to signal, but provides more control over the signal handling process. Allows for specifying additional signal handling options and obtaining the previous signal handler.  
```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handle_signal(int sig) {
    printf("Signal %d received.\n", sig);
}

int main() {
    struct sigaction action;
    action.sa_handler = handle_signal;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    sigaction(SIGINT, &action, NULL);

    while (1) {
        sleep(1);
    }
    return 0;
}
```

### sigemptyset & sigaddset
sigemptyset initializes a signal set to be empty. sigaddset adds a specific signal to a signal set.   
```c
#include <signal.h>

int main() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    // Use the signal set with other signal-related functions
    return 0;
}
```

### kill
Sends a specific signal to a process or a group of processes.   
```c
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child process started with pid %d.\n", getpid());
        while (1) {
            sleep(1);
        }
    } else {
        // Parent process
        sleep(3);
        printf("Killing child process with pid %d.\n", pid);
        kill(pid, SIGTERM);
    }
    return 0;
}
```

</div>
</details>


<details>
<summary>exit, strerror & perror </summary>
<div markdown="1">

### exit
Terminates the calling process and returns the specified exit status.   
```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    printf("Exiting with status 0.\n");
    exit(0);
}
```

### strerror & perror
strerror returns a string describing an error number, and perror prints a string describing the last error encountered.   
```c
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main() {
    FILE *file = fopen("nonexistent.txt", "r");
    if (file == NULL) {
        printf("Error: %s\n", strerror(errno));
        perror("Failed to open nonexistent.txt");
    }
    return 0;
}
```

</div>
</details>


<details>
<summary>getcwd, chdir, stat, unlink </summary>
<div markdown="1">

### getcwd
Gets the current working directory and stores it in the provided buffer.
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    char buffer[256];
    if (getcwd(buffer, sizeof(buffer)) != NULL) {
        printf("Current working directory: %s\n", buffer);
    }
    return 0;
}
```

### chdir
Changes the current working directory of the calling process to the specified path.   
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    if (chdir("/tmp") == 0) {
        printf("Changed working directory to /tmp.\n");
    } else {
        perror("Failed to change working directory");
    }
    return 0;
}
```

### stat, lstat, fstat
These functions obtain information about a file. stat() and lstat() take a file path as an argument, while fstat() takes a file descriptor. lstat() is similar to stat() but does not follow symbolic links.   
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    struct stat file_info;
    if (stat("test.txt", &file_info) == 0) {
        printf("Size of test.txt: %ld bytes\n", file_info.st_size);
    } else {
        perror("Failed to get file information");
    }
    return 0;
}
```

### unlink
Deletes a specified file by removing its link from the file system.   
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    if (unlink("test.txt") == 0) {
        printf("Successfully deleted test.txt.\n");
    } else {
        perror("Failed to delete test.txt");
    }
    return 0;
}
```
</div>
</details>


<details>
<summary>isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr </summary>
<div markdown="1">


### isatty
Checks if a given file descriptor is associated with a terminal device.   
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    if (isatty(STDOUT_FILENO)) {
        printf("stdout is a terminal.\n");
    } else {
        printf("stdout is not a terminal.\n");
    }
    return 0;
}
```

### ttyname
Returns a pointer to a string containing the name of the terminal device associated with a given file descriptor.   
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    char *name = ttyname(STDIN_FILENO);
    if (name) {
        printf("Terminal name: %s\n", name);
    } else {
        printf("Not a terminal.\n");
    }
    return 0;
}
```

### ttyslot
Returns the index of the terminal device associated with the calling process's standard input in the system's terminal table (utmp file).   
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    int slot = ttyslot();
    if (slot > 0) {
        printf("Terminal slot: %d\n", slot);
    } else {
        printf("Not a terminal.\n");
    }
    return 0;
}
```

### ioctl
Performs various control operations on a file descriptor.   
```c
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        printf("Terminal size: %d rows, %d columns\n", ws.ws_row, ws.ws_col);
    } else {
        perror("Failed to get terminal size");
    }
    return 0;
}
```

### getenv
Returns the value of an environment variable as a string.   
```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    char *path = getenv("PATH");
    if (path) {
        printf("PATH: %s\n", path);
    } else {
        printf("PATH not found.\n");
    }
    return 0;
}
```

### tcsetattr & tcgetattr
tcsetattr sets the terminal attributes for a file descriptor, and tcgetattr gets the terminal attributes for a file descriptor.   
```c
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == 0) {
        printf("Terminal attributes retrieved.\n");

        term.c_lflag &= ~ECHO; // Turn off echoing

        if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == 0) {
            printf("Terminal attributes set.\n");
        } else {
            perror("Failed to set terminal attributes");
        }
    } else {
        perror("Failed to get terminal attributes");
    }
    return 0;
}
```
</div>
</details>


<details>
<summary>tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs </summary>
<div markdown="1">

### tgetent
Loads the termcap entry for a terminal into a provided buffer.   
```c
#include <term.h>
#include <stdio.h>

int main() {
    char term_buffer[1024];
    if (tgetent(term_buffer, getenv("TERM")) == 1) {
        printf("Termcap entry loaded.\n");
    } else {
        printf("Failed to load termcap entry.\n");
    }
    return 0;
}
```

### tgetflag
Gets the value of a boolean capability from the termcap entry.   
```c
#include <term.h>
#include <stdio.h>

int main() {
    char term_buffer[1024];
    tgetent(term_buffer, getenv("TERM"));

    int has_am = tgetflag("am");
    printf("Auto-margins: %s\n", has_am ? "Yes" : "No");
    return 0;
}
```

### tgetnum
Gets the value of a numeric capability from the termcap entry.   
```c
#include <term.h>
#include <stdio.h>

int main() {
    char term_buffer[1024];
    tgetent(term_buffer, getenv("TERM"));

    int columns = tgetnum("co");
    printf("Columns: %d\n", columns);
    return 0;
}
```

### tgetstr
Gets the value of a string capability from the termcap entry.   
```c
#include <term.h>
#include <stdio.h>

int main() {
    char term_buffer[1024];
    char cap_buffer[256];
    tgetent(term_buffer, getenv("TERM"));

    char *clear_screen = tgetstr("cl", &cap_buffer);
    if (clear_screen) {
        tputs(clear_screen, 1, putchar);
    } else {
        printf("Failed to get clear screen capability.\n");
    }
    return 0;
}
```

### tgoto
Generates a cursor addressing string with specified row and column values.   
```c
#include <term.h>
#include <stdio.h>

int main() {
    char term_buffer[1024];
    tgetent(term_buffer, getenv("TERM"));

    char *cursor_address = tgetstr("cm", NULL);
    if (cursor_address) {
        char *move_cursor = tgoto(cursor_address, 10, 5);
        tputs(move_cursor, 1, putchar);
        printf("X");
    } else {
        printf("Failed to get cursor movement capability.\n");
    }
    return 0;
}
```

### tputs
Outputs a string capability, applying necessary padding.   
```c
#include <term.h>
#include <stdio.h>

int main() {
    char term_buffer[1024];
    tgetent(term_buffer, getenv("TERM"));

    char cap_buffer[256];

    // Get the string capability to enable underline
    char *underline_on = tgetstr("us", &cap_buffer);
    if (underline_on) {
        // Output the capability using tputs
        tputs(underline_on, 1, putchar);
        printf("Underlined text");

        // Get the string capability to disable underline
        char *underline_off = tgetstr("ue", &cap_buffer);
        if (underline_off) {
            // Output the capability using tputs
            tputs(underline_off, 1, putchar);
            printf("\nNormal text");
        }
    } else {
        printf("Failed to get underline capability.\n");
    }
    return 0;
}
```

</div>
</details>

### Setting
<details>
<summary>Setting</summary>
<div markdown="1">

**install brew**  
```
rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && export PATH=$HOME/.brew/bin:$PATH && brew update && echo "export PATH=$HOME/.brew/bin:$PATH" >> ~/.zshrc
```

**install readline**  
```
brew install readline && mkdir $HOME/.brew && curl -fsSLhttps://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C $HOME/.brew
mkdir -p /tmp/.$(whoami)-brew-locks
mkdir -p $HOME/.brew/var/homebrew
ln -s /tmp/.$(whoami)-brew-locks $HOME/.brew/var/homebrew/locks
export PATH="$HOME/.brew/bin:$PATH"
```

**upgrade brew**
```
brew update && brew upgrade
```

**upgrade bash**
```
brew install bash
```

</div>
</details>