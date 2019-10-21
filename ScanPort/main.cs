using System;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Threading;
using static System.Console;

namespace ScanPort
{
    public static class Program
    {
        private static void Main()
        {
            IPAddress[] host = new IPAddress[] { };
            PortScanner ps;
            int portStart = 1, portStop = 65555, crtThread = 200;
            try
            {
                Write("Enter IP address or domain name to dig : ");
                var tmp = ReadLine();
                if (tmp != null && !int.TryParse(tmp[0].ToString(), out int i))
                {
                    host = Dns.GetHostAddresses(tmp);
                    PrintAddresses(host);
                    //WriteLine("Address used : " + host[host.Length - 1]);
                    ps = new PortScanner(host[host.Length - 1], portStart, portStop);
                }
                else
                {
                    host[host.Length - 1] = IPAddress.Parse(tmp ?? throw new InvalidOperationException());
                    ps = new PortScanner(host[host.Length - 1], portStart, portStop);
                }
            }
            catch (Exception e)
            {
                WriteLine(e);
                PrintUsage();
                return;
            }
            Write("Do you want to search for opened sockets ? (Y/N) ");
            var ch = ReadLine();
            
            switch (ch)
            {
                case "y":
                    IPAddress hostD;
                    WriteLine("Enter IP address to search for opened sockets : ");
                    var tmp = ReadLine();
                    hostD = IPAddress.Parse(tmp ?? throw new InvalidOperationException());
                    var process = Process.Start(@"D:\My_Projects\WIP\TcpListener\bin\Debug\TcpListener.exe", hostD.ToString());
                    ps.Start(crtThread, portStart);
                    break;
                case "n":
                    WriteLine("\nBye !");
                    break;
            }

            ReadKey();
        }

        private static void PrintAddresses(IPAddress[] hostAddresses)
        {
            WriteLine("Addresses : ");
            foreach (var t in hostAddresses)
            {
                WriteLine(t);
            }
        }
        private static void PrintUsage()
        {
            WriteLine("Usage: PortScanner target-name [starting-port ending-port] [no-threads]\n");
            WriteLine("Where\n\tstarting-port\tStarting port number. Default is 1");
            WriteLine("\tending-port\tEnding port number. Default is 65535.");
            WriteLine("\tno-threads\tNumber of threads. Default is 200");
            WriteLine("\ttarget-name\tTarget host.\n");
            WriteLine("Example 1: \"PortScanner 127.0.0.1 1 10000\" will scan for open TCP ports from port 0 to port 10000.\n");
            WriteLine("Example 2: \"PortScanner 127.0.0.1\" will scan for open TCP ports from port 1 to port 65535.\n");
        }
    }


    public class PortScanner
    {
        private readonly IPAddress _host;
        private readonly PortList _portList;

        public PortScanner(IPAddress host, int portStart, int portStop)
        {
            _host = host;
            _portList = new PortList(portStart, portStop);
        }

        public PortScanner(IPAddress host)
            : this(host, 1, 65555)
        {
        }

        public void Start(int crtThread, int port)
        {
            WriteLine("Searching sockets...\n");
            for (int i = 0; i < crtThread; i++)
            {
                var thread = new Thread(Run);
                port += 65535 / crtThread;
                if (port >= 65535)
                    port = 65533;
                thread.Start(port);
            }
        }

        public void Run(object port)
        {
            int _port = (int)port;
            var tcp = new TcpClient();
            var portCl = 0;
            while ((_port = _portList.GetNext()) != (_port +  65535 / 5))
            {
                try
                {
                    tcp = new TcpClient(_host.ToString(), _port);
                }
                catch
                {
                    portCl++;
                    continue;
                }
                finally
                {
                    try
                    {
                        tcp.Close();
                    }
                    catch
                    {
                        // ignored
                    }
                }

                if (IsAvaible(_port))
                    WriteLine("TCP port " + _port + " is open and unused.");
                else
                    WriteLine("TCP port " + _port + " is open.");
            }

            WriteLine(portCl + " ports is closed");
        }

        private static bool IsAvaible(int port)
        {
            var ipGlobalProperties = IPGlobalProperties.GetIPGlobalProperties();
            var tcpConnection = ipGlobalProperties.GetActiveTcpConnections();

            return tcpConnection.All(tcpi => tcpi.LocalEndPoint.Port != port);
        }

        internal class PortList
        {
            private readonly int _stop;
            private int _ptr;
            public int StartPort { get; }

            public PortList(int start, int stop)
            {
                StartPort = start;
                _stop = stop;
                _ptr = start;
            }

            public PortList() : this(1, 65535)
            {
            }

            public bool HasMore()
            {
                return _stop - _ptr >= 0;
            }

            public int GetNext()
            {
                if (HasMore())
                    return _ptr++;
                return -1;
            }
        }
    }
}