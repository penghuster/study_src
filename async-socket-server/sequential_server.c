//Sequential socket server --accepting one client at a time 
#include <sys/socket.h>
#include <stdint.h>
#include <stdio.h>


typedef enum 
{
    WAIT_FOR_MSG,
    IN_MSG
} process_state_t;

void server_connection(int sockfd)
{
    //Clients attempting to connect and send data will succeed even before the 
    //connection is accept()-ed by the server. Therefore, to better simulate 
    //blocking of other clients while one is being served. do this 'ack' from
    //the server which the client expects to see before proceeding.(为了更好模拟
    //串行服务状态， 客户端在收到服务端“*”后方可继续发送消息)
    if(send(sockfd, "*", 1, 0) < 1)
    {
        perror_die("send");
    }

    process_state_t state = WAIT_FOR_MSG;

    while(1)
    {
        uint8_t buf[1024];
        int len = recv(sockfd, buf, sizeof(buf), 0);
        if(len < 0)
        {
            perror_die("recv");
        }
        else if(0 == len)
        {
            break;
        }

        for(int i = 0; i < len; ++i)
        {
            switch(state)
            {
            case WAIT_FOR_MSG:
                if('^' == buf[i])
                {
                    state = IN_MSG;
                }
                break;

            case IN_MSG:
                if('$' == buf[i])
                {
                    state = WAIT_FOR_MSG;
                }
                else
                {
                    buf[i] += 1;
                    if(send(sockfd, &buf[i], 1, 0) < 1)
                    {
                        perror("send error");
                        close(sockfd);
                        return;
                    }
                }
                break;

            }
        }
    }


    close(sockfd);

}


int main(int argc, char** argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);

    int portnum = 9090;
    if(argc >= 2)
    {
        portnum = atoi(argv[1]);
    }

    printf("Serving on port %d\n", portnum);

    int sockfd = listen_inet_socket(portnum);
    while(1)
    {
        struct sockaddr_in peer_addr;
        socklen_t peer_addr_len = sizeof(peer_addr);

        int newsockfd = accept(sockfd, (struct sockaddr*)&peer_addr, &peer_addr_len);

        if(newsockfd < 0)
            perror_die("ERROR on accept.");

        report_peer_connected(  )
    }
}
