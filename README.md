# REQUIREMENT
Title of the experiment: Implementation of a simple network scanning program using SCANNER.

Experiment objectives: To familiarize with and implement the basic principles of network scanning. To understand several commonly used methods for network scanning.

Experiment environment: Linux/Windows.

Experiment contents: Write a program in C/C++ language (using socket function) to scan hosts within a local network. The program should be able to display a list of hostnames, IP addresses within the local network, and which hosts have open ports.

Experiment requirements: Submit an experimental report (see attachment); submit source code. Filename format: student ID + name + scanner.

# IMPL

`target` is a network target for single IP and multi ports.

`target manager` manage several targets which under same subnet.

use TCP connect to test whether given port open(port in above the TCP layer).

use multithread to accelerate scan rate and preserve their results. 

# RESULT 

something like following:
```shell
# squ @ squ-virtual-machine in ~/proj/Scanner on git:master o [13:20:58] 
$ ./build/linux/x86_64/debug/Scanner -a 127.0.0.1 -m 255.255.255.0
Host Name                IP Address     Opened Port
localhost                127.0.0.1      22        
localhost                127.0.0.1      80        
squ-virtual-machine      127.0.0.2      22        
squ-virtual-machine      127.0.0.2      80        
localhost                127.0.0.3      22        
localhost                127.0.0.3      80        
localhost                127.0.0.4      22        
localhost                127.0.0.4      80        
localhost                127.0.0.5      22        
localhost                127.0.0.5      80        
localhost                127.0.0.6      22        
localhost                127.0.0.6      80        
localhost                127.0.0.7      22        
localhost                127.0.0.7      80        
localhost                127.0.0.8      22        
localhost                127.0.0.8      80 
```