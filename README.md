Simple Shell — hsh
A simple UNIX command line interpreter written in C, reproducing the basic behavior of /bin/sh.

Description
hsh is a simple shell written in C as part of the Holberton School curriculum. It reads commands from standard input (interactive or non-interactive), searches for them in the PATH, and executes them using fork() and execve().

Features

Interactive and non-interactive mode
Command execution with full path (/bin/ls) or via PATH resolution (ls)
Error handling mimicking /bin/sh
Built-ins: exit, env
Handles EOF (Ctrl+D)
Betty style compliant
No memory leaks


Requirements

Ubuntu 20.04 LTS
GCC with flags: -Wall -Werror -Wextra -pedantic -std=gnu89


Compilation
bashgcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

Usage
Interactive mode
bash$ ./hsh
($) /bin/ls
hsh main.c shell.h find_path.c split_line.c builtins.c execute.c
($) ls
hsh main.c shell.h find_path.c split_line.c builtins.c execute.c
($) exit
$
Non-interactive mode
bash$ echo "/bin/ls" | ./hsh
hsh main.c shell.h find_path.c split_line.c builtins.c execute.c

$ cat commands.txt | ./hsh
hsh main.c shell.h find_path.c split_line.c builtins.c execute.c

Error handling
The shell prints errors using the program name as it was called:
bash$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found

$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found

Flowchart
#mermaid-r1es{font-family:inherit;font-size:16px;fill:#E5E5E5;}@keyframes edge-animation-frame{from{stroke-dashoffset:0;}}@keyframes dash{to{stroke-dashoffset:0;}}#mermaid-r1es .edge-animation-slow{stroke-dasharray:9,5!important;stroke-dashoffset:900;animation:dash 50s linear infinite;stroke-linecap:round;}#mermaid-r1es .edge-animation-fast{stroke-dasharray:9,5!important;stroke-dashoffset:900;animation:dash 20s linear infinite;stroke-linecap:round;}#mermaid-r1es .error-icon{fill:#CC785C;}#mermaid-r1es .error-text{fill:#3387a3;stroke:#3387a3;}#mermaid-r1es .edge-thickness-normal{stroke-width:1px;}#mermaid-r1es .edge-thickness-thick{stroke-width:3.5px;}#mermaid-r1es .edge-pattern-solid{stroke-dasharray:0;}#mermaid-r1es .edge-thickness-invisible{stroke-width:0;fill:none;}#mermaid-r1es .edge-pattern-dashed{stroke-dasharray:3;}#mermaid-r1es .edge-pattern-dotted{stroke-dasharray:2;}#mermaid-r1es .marker{fill:#A1A1A1;stroke:#A1A1A1;}#mermaid-r1es .marker.cross{stroke:#A1A1A1;}#mermaid-r1es svg{font-family:inherit;font-size:16px;}#mermaid-r1es p{margin:0;}#mermaid-r1es .label{font-family:inherit;color:#E5E5E5;}#mermaid-r1es .cluster-label text{fill:#3387a3;}#mermaid-r1es .cluster-label span{color:#3387a3;}#mermaid-r1es .cluster-label span p{background-color:transparent;}#mermaid-r1es .label text,#mermaid-r1es span{fill:#E5E5E5;color:#E5E5E5;}#mermaid-r1es .node rect,#mermaid-r1es .node circle,#mermaid-r1es .node ellipse,#mermaid-r1es .node polygon,#mermaid-r1es .node path{fill:transparent;stroke:#A1A1A1;stroke-width:1px;}#mermaid-r1es .rough-node .label text,#mermaid-r1es .node .label text,#mermaid-r1es .image-shape .label,#mermaid-r1es .icon-shape .label{text-anchor:middle;}#mermaid-r1es .node .katex path{fill:#000;stroke:#000;stroke-width:1px;}#mermaid-r1es .rough-node .label,#mermaid-r1es .node .label,#mermaid-r1es .image-shape .label,#mermaid-r1es .icon-shape .label{text-align:center;}#mermaid-r1es .node.clickable{cursor:pointer;}#mermaid-r1es .root .anchor path{fill:#A1A1A1!important;stroke-width:0;stroke:#A1A1A1;}#mermaid-r1es .arrowheadPath{fill:#0b0b0b;}#mermaid-r1es .edgePath .path{stroke:#A1A1A1;stroke-width:2.0px;}#mermaid-r1es .flowchart-link{stroke:#A1A1A1;fill:none;}#mermaid-r1es .edgeLabel{background-color:transparent;text-align:center;}#mermaid-r1es .edgeLabel p{background-color:transparent;}#mermaid-r1es .edgeLabel rect{opacity:0.5;background-color:transparent;fill:transparent;}#mermaid-r1es .labelBkg{background-color:rgba(0, 0, 0, 0.5);}#mermaid-r1es .cluster rect{fill:#CC785C;stroke:hsl(15, 12.3364485981%, 48.0392156863%);stroke-width:1px;}#mermaid-r1es .cluster text{fill:#3387a3;}#mermaid-r1es .cluster span{color:#3387a3;}#mermaid-r1es div.mermaidTooltip{position:absolute;text-align:center;max-width:200px;padding:2px;font-family:inherit;font-size:12px;background:#CC785C;border:1px solid hsl(15, 12.3364485981%, 48.0392156863%);border-radius:2px;pointer-events:none;z-index:100;}#mermaid-r1es .flowchartTitleText{text-anchor:middle;font-size:18px;fill:#E5E5E5;}#mermaid-r1es rect.text{fill:none;stroke-width:0;}#mermaid-r1es .icon-shape,#mermaid-r1es .image-shape{background-color:transparent;text-align:center;}#mermaid-r1es .icon-shape p,#mermaid-r1es .image-shape p{background-color:transparent;padding:2px;}#mermaid-r1es .icon-shape rect,#mermaid-r1es .image-shape rect{opacity:0.5;background-color:transparent;fill:transparent;}#mermaid-r1es .label-icon{display:inline-block;height:1em;overflow:visible;vertical-align:-0.125em;}#mermaid-r1es .node .label-icon path{fill:currentColor;stroke:revert;stroke-width:revert;}#mermaid-r1es :root{--mermaid-font-family:inherit;}yesnoEOFexitenvnonot foundfoundchildparentStartInteractive\nmode ?Display promptRead input\ngetlineexit 0Parse command\nstrtok -> argvBuilt-in ?exitPrint environmentSearch in PATH\naccessPrint error\ncmd: not foundforkexecvewaitpid

File structure
FileDescriptionmain.cEntry point — main loop, input reading, command dispatchingexecute.cFork, execve and waitpid — child process executionbuiltins.cBuilt-in commands: exit and envfind_path.cPATH resolution — searches command in PATH directoriessplit_line.cTokenizer — splits input line into argv arrayshell.hHeader file — prototypes and includesman_1_simple_shellManual pageAUTHORSList of contributors

Authors
See AUTHORS

License
This project is part of the Holberton School curriculum.