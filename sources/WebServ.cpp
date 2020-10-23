/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:17:48 by rchallie          #+#    #+#             */
/*   Updated: 2020/10/23 02:30:30 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/WebServ.hpp"
#include "../includes/Socket.hpp"
#include "../includes/SocketManager.hpp"
#include "../includes/Server.hpp"
#include "../includes/Configuration.hpp"
#include "../includes/HeadersBlock.hpp"

int main(int argc, char **argv)
{
    // char block[] = "GET / HTTP/12.1\r\nHost: 0.0.0.0:3650\r\nUser-Agent: insomnia/2020.4.1\r\nAccept: */*\r\n\r\n";
    // char block[] = "HTTP/1.1 200 plop\nHost: localhost:5000\nUser-Agent: insomnia/2020.4.1\nAccept: */*\n\n";
    // try
    // {
    //     HeadersBlock test(block);
    // }
    // catch (const std::exception& e)
    // {
    //     throwError(e);
    // }
    // exit(1);

    char *path;

    if (argc != 2)
    {
        outError("Please use : ./WebServ <path>");
        return (1);
    }
    path = argv[1];
    
    DEBUG("")
   
    std::vector<Socket *> socket_list;

    try
    {
        Configuration test = Configuration(path);
		    test.print();
        for (int i = 0; i < (int)test.getServers().size(); i++)
            socket_list.push_back(new Socket(test.getServers()[i]));
        SocketManager sm;

        for (int i = 0; i < (int)socket_list.size(); i++)
            sm.registerSocket(*(socket_list.begin() + i));

        Server server(sm);
        
        server.loop();
    }
    catch(const std::exception& e)
    {
        throwError(e);
    }
    return (0);
}

//Temptorary
int treat(int sd, char *buffer)
{
    (void)buffer;
    DEBUG("TREATMENT");
    DEBUG("BUFFER :\n" << buffer);

    char bufferrtn[] = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 14\n\n<h1>Hello</h1>";      
    int rc = send(sd, bufferrtn, strlen(bufferrtn), 0);
    if (rc < 0)
    {
        DEBUG("  send() failed");
        return (-1);
    }
    return (0);
}