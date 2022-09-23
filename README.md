# WebServer
**This is a tiny http web server**

## Dev Log  
*20220922*:  
- The main loop was developed, echo server was built for testing multi-threading structure.
- **Issue:** After receiving a long message from the client, there are some left messages in the buffer char array.   
- **Solution:** read() function returns the length of messages from client. A int variable buf_len can record the length, and '\0' was added after reading in the buffer char array.  

