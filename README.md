# PluginSystem
Simulating DLL export using sockets

Server has list of guid:plugin values. Client sends guid to server and gets the need DLL function. 
Supplier writes new guid:plugin pairs to registry, server updates its list when registry is changed.

Server also writes number of bytes sent to client into registry which is used by Perfomance monitor.

## HOWTO:
To check the result, you need to procedd steps below:

1. Build solution
2. Launch server
3. Launch client with following parameters: 127.0.0.1 {00000000-0000-0000-0100-000000000000}.
You should get message that Plugin 1_1 send
4. Launch supplier, it will write updated guid and plugin information to registry key "SOFTWARE\\PluginSystem"
5. Launch client again with the same parameter.
You should get message that Plugin 1_2 was send. Thus plugin was updated by server
