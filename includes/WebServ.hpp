/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:25:44 by rchallie          #+#    #+#             */
/*   Updated: 2020/11/06 17:28:50 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

#if DEBUG_ACTIVE == 1 
	#define DEBUG(x) std::cout << x << std::endl;
#else
	#define DEBUG(x)
#endif

#include <errno.h>
#include <string.h>
#include <exception>
#include <iostream>
#include <sstream>
#include <signal.h>
#include "Configuration.hpp"
#include "HeadersBlock.hpp"

class throwMessage : public std::exception {
	private:
		std::string _msg;

	public:
		throwMessage (const std::string& msg) throw() : _msg(msg) {}
		throwMessage (const throwMessage&) throw() {}
		throwMessage& operator= (const throwMessage&) throw();
		virtual ~throwMessage() throw() {}
		virtual const char* what() const throw() { return (_msg.c_str()); }
};

class throwMessageErrno : public std::exception {
	private:
		std::string _msg;

	public:
		throwMessageErrno (const std::string& msg) throw() 
		{
			std::stringstream ss;
			ss << msg << " : " << strerror(errno);
			this->_msg = ss.str();
		}

		throwMessageErrno (const throwMessageErrno&) throw() {}
		throwMessageErrno& operator= (const throwMessageErrno&) throw();
		virtual ~throwMessageErrno() throw() {}
		virtual const char* what() const throw() { return (_msg.c_str()); }
};

void throwError(const std::exception& ex);
void outError(const std::string& msg);
int treat(int sd, fd_set working_set, HeadersBlock &header_block, Configuration::server server_conf);
void endServer(int signal);

#endif