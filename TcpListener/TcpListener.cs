using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using static System.Console;

namespace TCPListener
{
 

    public static class TcpListener
    {
        private static void Main(string[] args)
        {
            Write("Enter port : ");
            int portToOpen;
            try
            {
                portToOpen = int.Parse(ReadLine() ?? throw new InvalidOperationException());
            }
            catch (Exception e)
            {
                WriteLine("Error " + e);
                throw;
            }

            Listener tcpListener = new Listener(portToOpen, IPAddress.Parse(args[0]));
            tcpListener.Start();
        }
    }

    public class Listener
    {
        private readonly int _port;
        private readonly System.Net.Sockets.TcpListener _serverListener;

        public Listener(int port, IPAddress host)
        {
            _port = port;
            _serverListener = new System.Net.Sockets.TcpListener(host, port);
        }
        public void Start()
        {
            try
            {
                _serverListener.Start();
                var bytes = new byte[256];

                while (true)
                {
                    WriteLine("Waiting for a connection to port " + _port + "...");
                    TcpClient client;
                    try
                    {
                        client = _serverListener.AcceptTcpClient();
                    }
                    catch (Exception e)
                    {
                        WriteLine("Connection error " + e);
                        break;
                    }

                    WriteLine("Connected !");
                    var stream = client.GetStream();

                    int i;
                    while ((i = stream.Read(bytes, 0, bytes.Length)) != 0)
                    {
                        var data = Encoding.ASCII.GetString(bytes, 0, i);
                        WriteLine("Received: {0}", data);

                        data = data.ToUpper();

                        var msgBytes = Encoding.ASCII.GetBytes(data);

                        stream.Write(msgBytes, 0, msgBytes.Length);
                        WriteLine("Sent: {0}", data);
                    }

                    client.Close();
                }
            }
            catch (SocketException e)
            {
                WriteLine("SocketException : " + e);
            }
            finally
            {
                _serverListener.Stop();
            }

            Read();
        }
    }

}