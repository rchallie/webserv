#ifndef CGI_CPP
# define CGI_CPP

# include <iostream>
# include <string>
# include <map>
# include <stdlib.h>
# include "HeadersBlock.hpp"
# include "Configuration.hpp"
# include "WebServ.hpp"

class CGI
{
	private:
		std::string _cgi_path;
		std::string _ressource_path;
		HeadersBlock _request;
		Configuration::server _conf;
		Configuration::location _location;
		std::map<std::string, std::string> _getParams(void);
		std::string _getQueryString(void);
		char **_convertParams(std::map<std::string, std::string> args);
		void _freeArgs(char **args);
		char *_newStr(std::string source);
		std::string _execCGI(char **args);
		char **_getExecArgs(void);
		std::string _getScriptName(void);
	public:
		CGI(void);
		CGI(std::string cgi_path, std::string ressource_path, HeadersBlock request, Configuration::server conf, Configuration::location location);
		~CGI(void);
		std::string getOutput(void);

};

#endif