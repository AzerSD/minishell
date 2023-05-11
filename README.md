references:<br>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="https://www.gnu.org/software/bash/manual/html_node/">bash_manual</a><br>
&nbsp;&nbsp;&nbsp;&nbsp;<a href="https://git.savannah.gnu.org/cgit/bash.git/tree/">bash_source_code</a><br>
  
## Features

- [ ] Structure
  - [x] Init
  - [x] Input
  - [x] Lexer
  - [x] Parser
  - [x] Expand
    - [x] Special Parameters: One of `@`, `*`, `#`, `?`, `-`, `$`, `!`, or `0`
    - [x] A Variables name
    - [x] A variable name surrounded by `{` and `}`
    - [x] An arithmetic expansion, surrounded by `(` and `)`
    - [ ] A command substitution, surrounded by `((` and `))`
    - [ ] Positional Parameters `$0`, `$1`, `$n`, `$#`, `$@` and `$*`
  - [x] Ast
  - [x] Execution
  - [ ] Builtins
    - [x] `cd` | `chdir`
    - [x] `echo`
    - [ ] `exit`
    - [x] `env`
    - [ ] `setenv`
    - [ ] `unsetenv`
    - [ ] `unset`
    - [ ] `export`
    - [ ] `history`
    - [x] `pwd`

- [ ] Line editing
  - [ ] Simple and advanced line editing
  - [ ] Edit the line where the cursor is positionned
  - [ ] Move cursor left or right
  - [ ] Up and Down arrows to navigate in the history
  - [ ] Enter Insert mode with `alt+i` and exit it with `alt+i`
  - [ ] Copy and paste with `alt+C` `alt+v`
  - [ ] Move word per word left or right `alt+LEFT` `alt+RIGHT`
  - [ ] Go to beginning or end of a line. `home` `end`
  - [ ] Move to top or bottom line. `alt+UP` `alt+DOWN`
  - [ ] Waits for the end of a quote or double quote.
  - [ ] ctrl+D and ctrl+C usable when editing a line or in multi-line.
  - [ ] Multiline line editing
  

- [ ] Builtins with their POSIX options (For more info type `help` once in the shell)


- [ ] Exec
  - [ ] Executing commands stored in path with their parameters
  - [ ] Error handling and return value handling
  - [ ] Redirections handled : `>`, `<`, `<<` and `>>`
  - [ ] Pipes `|`
  - [ ] Logical operators `&&` and `||`
  - [x] Backquotes "‘" (TODO)
  - [x] Ihibitors """ (double quote), "’" (simple quote) et "\" (backslash).
  - [ ] `;`
  - [x] `\n` handling where `\n` can be used as a `;`. Example: `ls \n ls` == `ls ; ls`


- [ ] Prompt
  - [ ] Multi line editing with `\`, `'` and `"`
  - [ ] History handles the multi-line editing


- [ ] Shell
  - [ ] This shell proposes multiple options to enhance user experience
  - [ ] `h` This option will display help for all options as described here
  - [ ] `v` Verbose mode
  - [ ] `d` Debug mode (Enables the logger). A log file will be created where the binary exists. This option requires a log level from 0 to 7
  - [ ] `t` Test mode. This mode will test the module `X` with `Y` parameter as follows : `-t X Y`. Can be used with modules `env` `ast` `parser` `lexer` `ast`
  - [ ] `c` Command. Use this option to send a command to the shell and get it's output
  - [ ] `C` Color. Use this option to enable color in the shell
  - [ ] `l` Disables the termcaps. This is a debug option and not a feature ! To be used lightly


- [ ] Signals
  - [ ] We kill all childs when we get a signal that kills the program so no zombie process is left behind
  

- [ ] Autocompletion
  - [ ] Dynamic autocompletion
  - [ ] Autocompletes binaries from `PATH`
  - [ ] Autocompletes files and paths
  - [ ] Autorefreshing with a new input from the user: modification of the list of possibility. TODO WIP


- [ ] Environ
  - [x] Local Variables are available
  - [x] Normal environment is used when the shell is started
  - [x] Uses the `=` syntax (`VAR=VALUE`)
  - [x] Default env is given when **42sh** is started with env -i (TODO to be customized)
  - [ ] Message to warn the User when **42sh** is started without an env


- [ ] Bonuses
  - [ ] Heredocs "<<".
  - [ ] File descriptors aggregation


- [ ] History
  - [ ] A menu is printed when the history fil is to big
  - [ ] The history is printed in the log when exiting the program
  - [ ] History research `ctrl+R.`

</div>


have fun. Programming can be a lot of fun, and if you’re not generally having fun, you’re not in the right mindset to be programming. Tired or unhappy programmers make mistakes, and debugging code tends to take much longer than writing it correctly in the first place! Often you can save yourself some time by going to bed, getting a good night’s sleep, and coming back to a problem in the morning.
