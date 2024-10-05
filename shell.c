#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

#define max_inp 1024
#define PI 3.14159265358979323846
#define RESET   "\033[0m"  // Reset to default color 
#define YELLOW  "\033[33m" // Yellow text 
#define GREEN   "\033[32m" // Green text
#define WHITE   "\033[37m" // White text

void print_help() {
    printf("Hello! Welcome to my shell. Here are some of the commands available:\n");
    printf("  exit - Exits shell\n");
    printf("  help - Displays me\n");
    printf("  tri <side1> <side2> - Pythagorean\n");
    printf("  calc <num1> <operator> <num2> - Simple calculator\n");
    printf("  color <clr> - changes text color, type in name of color for argument\n");
    printf("  face <expression> - prints a happy, mad or sad face\n");
}

void calculate_triangle(double side1, double side2) {
    float hypotenuse = sqrt(side1 * side1 + side2 * side2);
    float angle1 = atan(side1 / side2) * (180.0 / PI);
    float angle2 = atan(side2 / side1) * (180.0 / PI);

    printf("Given sides: %f and %f\n", side1, side2);
    printf("Hypotenuse: %f\n", hypotenuse);
    printf("Angle1: %f degrees\n", angle1);
    printf("Angle2: %f degrees\n", angle2);
}

void calculator(double num1, char operator, double num2) {
    double result;
    switch (operator) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                printf("Sorry, you can't divide bt zero.):\n");
                return;
            }
            break;
        default:
            printf("Use a valid operator.\n");
            return;
    }
    printf("Result: %.2f %c %.2f = %.2f\n", num1, operator, num2, result);
}

void print_happy(){
    printf(YELLOW"                          @@@@@                               \n");
    printf("                        @+:................-#@                      \n");
    printf("                     =.........................:*                   \n");
    printf("                 -.................................-+               \n");
    printf("              +:......................................-&            \n");
    printf("            =...........................................-#          \n");
    printf("           =..............................................*         \n");
    printf("         +.................................................:#       \n");
    printf("        :................-:................:-................=      \n");
    printf("       -...............&@@@@-............:@@@@@...............+     \n");
    printf("      +...............&@@@@@@............@@@@@@@...............#    \n");
    printf("     *................@@@@@@@=..........-@@@@@@@:...............&   \n");
    printf("    &.................@@@@@@@=..........-@@@@@@@:................@  \n");
    printf("    :.................&@@@@@@............@@@@@@@.................-  \n");
    printf("   *...................@@@@@-............:@@@@@:..................# \n");
    printf("   -.....................:..................:.....................- \n");
    printf("   -..............................................................- \n");
    printf("   -..............................................................- \n");
    printf("   -..............................................................- \n");
    printf("   -..............................................................- \n");
    printf("   -..............+................................+:.............- \n");
    printf("   #:............*..................................*:............# \n");
    printf("    -.......:-+*@....................................@*+=-.......-  \n");
    printf("    &...........-@:................................:@=...........&  \n");
    printf("     &...........:@*..............................*@-...........&   \n");
    printf("      #............&@+..........................=@&............#    \n");
    printf("       +............:@@#:....................:#@@:............+     \n");
    printf("        =..............*@@&+:............:+&@@*..............=      \n");
    printf("         #:...............=@@@@@@@@@@@@@@@@=...............:#       \n");
    printf("           #....................:-==-:....................*         \n");
    printf("            #-..........................................-#          \n");
    printf("              &-......................................-&            \n");
    printf("                 +-................................-+               \n");
    printf("                    #+:.........................+#                  \n");
    printf("                        @#=................-#@                      \n");
    printf("                               @@@@@@                               \n"RESET);
}

void print_mad(){
    printf(YELLOW"                   .-+#**********#*-.                        \n");
    printf("                     -#**********************#=                    \n");
    printf("                 .+#*****************************+.                \n");
    printf("               -#**********************************#=              \n");
    printf("             +****************************************+            \n");
    printf("           :********************************************:          \n");
    printf("          +***********************************************         \n");
    printf("         #************************************************#        \n");
    printf("        ****************************************************       \n");
    printf("       ******************************************************      \n");
    printf("      +*******************************************************     \n");
    printf("      ********************************************************.    \n");
    printf("     +********@@@@@******************************@@@@@********+    \n");
    printf("     ********&@@@@@@@@@@&******************&@@@@@@@@@@@********    \n");
    printf("    .**************#&&@@@@@@************@@@@@@&&#**************:   \n");
    printf("    :****************&@@@@@@@@********@@@@@@@@&****************-   \n");
    printf("    -***************&@@@@@@@@@********@@@@@@@@@&***************-   \n");
    printf("    .***************&@@@@@@@&**********&@@@@@@@&***************:   \n");
    printf("     ***************&@@@@@@@#**********#@@@@@@@&***************    \n");
    printf("     +***************&@@@@@@************@@@@@@&***************+    \n");
    printf("      *****************&&&****************&&&*****************.    \n");
    printf("      +*******************************************************     \n");
    printf("       ******************************************************      \n");
    printf("        ********************##&@@@@@@&&#********************       \n");
    printf("         #***************&@@@@@@@@@@@@@@@@&***************#        \n");
    printf("          *************@@@@@@@@@@@@@@@@@@@@@@*************         \n");
    printf("           .*********#@@@@#**************#@@@@#*********:          \n");
    printf("             +*******&&**********************&&*******+            \n");
    printf("               =#**********************************#=              \n");
    printf("                 .+#****************************#+.                \n");
    printf("                     =#**********************#=.                   \n");
    printf("                         .-+#**********#+=:                        \n"RESET);
}

void print_sad(){
    printf(YELLOW"                                                                                  \n");
    printf("                     =@@@@&*=:.......:=*&@@@@+                                          \n");
    printf("                  @@&*-..:--==+******+=--:.:-*&@@                                       \n");
    printf("               @@#-.:-=+*##*=:..    ..=+##**=-:.-#@@                                    \n");
    printf("              @@=:--+*#=.                   .-**+=::=&@                                 \n");
    printf("           @&=:-=**:     .................      **+-:=&@                                \n");
    printf("         +@=:-=*=    .........................    :*+-:=@*                              \n");
    printf("        @#::=+=   ...............................   .+=::#@                             \n");
    printf("       @+:-=*.  ...................................   =+-:+@                            \n");
    printf("      @=.-=-  .......................................  .=-.=@                           \n");
    printf("      &:-=-  .......................................... .+-:&.                          \n");
    printf("     @::-+ ..............   ...........  ............... :=::@                          \n");
    printf("    -&.-=. ............  ... ......... :.   ..............=-.&=                         \n");
    printf("    @::-=...........   #@@@@..........:@@@@.   ...........:-::@                         \n");
    printf("    @.:--........   -@@@@@+ ........... &@@@@@.   .........-:.@                         \n");
    printf("    @.-:-.....   +@@@@@+.  .............  .&@@@@@.  ......:::.@                         \n");
    printf("    @::::-....@@@@#     ...................     @@@@@....:-:::@                         \n");
    printf("    =&.:::---.     .........  ......   .........    ..:--:::.&+                         \n");
    printf("     @::::......@@   ....   @@......@@    ...   @@ :-:...::..@                          \n");
    printf("      &.::-==++..@@@@    @@@@ ...... @@@@    @@@@..===+=-::.&:                          \n");
    printf("      @-..--=+*=.  @@@@@@@@  ........  @@@@@@@@. .-+**+=-:.-@                           \n");
    printf("       @=:-==++==-.        ............        .:=======-:=@                            \n");
    printf("        @+.:=-===:.....:.......     ........:.....:----..+@                             \n");
    printf("         &@..:.....::::..::...=@@@@@-..:.::..:.:........@&                              \n");
    printf("           @+ .==:::::.::....@@@@&@@@@....:..:::::--:.*@                                \n");
    printf("              @# .-+-::::::.:.         ..:::::::-=-. *@                                 \n");
    printf("               @@. .:--:::::::::::::::::::::--:...@@                                    \n");
    printf("                  @@:.......:::::::::::.:.....=@@                                       \n");
    printf("                     &@@@&#=...........=*&@@@@                                          \n");
    printf("                             .........                                                  \n"RESET);
}

int main() {
    char input[max_inp];
    char *cmds[max_inp];
    char *tmp;
    pid_t pid;
    int state;
    int clr;

    while (1) {
        printf("\e[%dmgc-shell>>", clr);
        if (fgets(input, max_inp, stdin) == NULL) { //fgets - reads a text line or a string from the console and store into string variable input
            exit(EXIT_FAILURE);
        }
        input[strcspn(input, "\n")] = '\0'; //strcspn - searches for \n in input and gets rid of newline character produced from fgets(allows for comparison to work further on)

        int i = 0;
        tmp = strtok(input, " "); // strtok - splits the string from the input and splits along the delimiter in the 2nd argument, in this case it splits the command from the rest of the arguments
        while (tmp != NULL && i < max_inp - 1) { // this loop stores the value of the input values split by above into the cmds values, goes until tmp is null(no more values)
            cmds[i++] = tmp; 
            tmp = strtok(NULL, " ");
        }
        cmds[i] = NULL;

        if (cmds[0] == NULL) {
            continue;
        }else if (strcmp(cmds[0], "exit") == 0) {   //exit command
            break; //exits shell
        }else if (strcmp(cmds[0], "help") == 0) {   //help command
            print_help();
            continue;
        }else if (strcmp(cmds[0], "tri") == 0) {    //pythagorean command
            if (cmds[1] != NULL && cmds[2] != NULL) {
                double side1 = atof(cmds[1]);
                double side2 = atof(cmds[2]);
                if (side1 > 0 && side2 > 0) {
                    calculate_triangle(side1, side2);
                } else {
                    printf("Sides must be positive numbers.\n");
                }   
            }
            continue;
        }else if (strcmp(cmds[0], "calc") == 0) {
            if (cmds[1] != NULL && cmds[2] != NULL && cmds[3] != NULL) {    //calculator command
                double num1 = atof(cmds[1]);
                char operator = cmds[2];
                double num2 = atof(cmds[3]);
                calculator(num1, operator, num2);
            }
            continue;
        }else if(strcmp(cmds[0], "color") == 0){    //ansi color text command
         if(cmds[1] != NULL){   
                if(!strcasecmp(cmds[1], "black"))
                    clr = 30;
                else if(!strcasecmp(cmds[1], "red"))
                    clr = 31;
                else if(!strcasecmp(cmds[1], "green"))
                    clr = 32;
                else if(!strcasecmp(cmds[1], "yellow"))
                    clr = 33;
                else if(!strcasecmp(cmds[1], "blue"))
                    clr = 34;
                else if(!strcasecmp(cmds[1], "purple"))
                    clr = 35;
                else if(!strcasecmp(cmds[1], "cyan"))
                    clr = 36;
                else if(!strcasecmp(cmds[1], "white"))
                    clr = 37;
            else
                printf("Please Enter a Color\n");
            }else{
                printf("Please Enter a Color\n");
                continue;
            }
        }else if(strcmp(cmds[0], "face") ==0){
            if(cmds[1] != NULL){
                if(!strcasecmp(cmds[1], "happy")){
                    print_happy();
                }else if(!strcasecmp(cmds[1], "mad")){
                    print_mad();
                }else if(!strcasecmp(cmds[1], "sad")){
                    print_sad();
                }
                continue;
            }
        }

        pid = fork();
        if (pid < 0) {
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execvp(cmds[0], cmds) < 0) {    //execvp allows for ls
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            waitpid(pid, &state, 0);
        }
    }

    return 0;
}
