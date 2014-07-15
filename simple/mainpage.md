
\mainpage CMS 1.0 Documentation
\tableofcontents

\section intro_sec Introduction
This project is the implementation of the CMS application. This application is Commodity Market System (CMS). Commodity markets are markets where raw or primary products are exchanged. These raw commodities are traded on regulated commodities exchanges, in which they are bought and sold in standardized contracts \ref [http://en.wikipedia.org/wiki/Commodity_market].
\par
This platform will allow dealers to list the contracts they have available to buy or sell and allow other dealers to trade these orders.
The system will allow dealers to modify and revoke their orders, and will also allow querying of available orders.
\par 
The implementation is done in Ubuntu 14.04,using boost-1.55.0 and gcc-4.6. 


\section modes Modes of Operations
This application can be used in three modes.
	
\subsection base_sec Base(base)
This is the most basic mode of operation, where all the application launches itself in the standalone mode. All the operations are to be done using standart input/output.

\subsection ext1_sec Extension 1(ext1)
In this mode the application can handle multiple clyients. This implementation follows a server-client architecture, however the server is single threaded. For detailed documentation look at Server class.

\subsection ext2_sec Extension 2(ext2)
This is also a server-client based implementation, however server holds a thread pool to sever incoming connection concurrently. By default  there will be 10 threads in the thread pool. The value of the thread pool can be increased or decreased. Detailed documentation is available in the Server class.


\section compilation Compilation
This application is built using boost library-1.55.0. So make sure that the target system has the proper boost library installed. Once that is in place, then create two environment variables boost_inc and boost_lib.
boost_inc variable should contain the path to the place where the header files of boost library resides, where as boost_lib contains the information the location of the shared lirabries.
For my system ,  
    \par                                                                                 
    boost_inc=/home/arijit/install/boost_1_55_0/install/include   
    \par
    boost_lib=/home/arijit/install/boost_1_55_0/install/lib
    
Once these two variables are in place then run \b make command which create two executable, viz. Server and cms. They can be individually compiled with \bmake \bserver and \b make \b client commands.
The docuementation can be regerated using \b make \b docgen. \b make \b clean  is used to cleanup the compilation.


\section usage Usage
This section will detail the usage of the application.

\subsection base_usage Base Usage
Basic usage of the application is done through a standalone launch of the cms application. Command to use the application in this mode is 
\par                                                                                                                                      
./cms --base

This will open the cms command prompt. Use of proper commands will do the commodity marketing. Illegal  usages will be reported.
\image html base.png

\subsection ext1_usage Extension 1 Usage
Since this server-client architecture based implementation, with a single-threaded server. So in order to use this, first launch the server using
\par
./Server --ext1 <port_num>

where port_num is the port number on which the server should listen. Then one can launch as many as client on many other different terminals, using commands,
\par 
./cms --ext1 <port_num>

Here this port_num has to be the same with that of the server. 
An example launched application should look like, 
\image html ext1.png

\subsection ext2_usage Extension 2 Usage
Using application in this mode is almost similar to that of ext1 mode. Although this mode launches the application with the thread pool created in side the server, which helps to do the operations concurrently. Here the options are almost as likely as ext1 version except arguments of both Server and cms executables should be ext2 instead of ext1. An example of this mode of the application can be seen here.
\image html ext2.png

\subsection help_usage Help Usage
For both the executable --help will display the help message containing the all the necessary information about the arguments.
