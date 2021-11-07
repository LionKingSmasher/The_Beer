using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

using u8 = System.Byte;
using u16 = System.UInt16;
using u32 = System.UInt32;
using u64 = System.UInt64;

namespace WinTheBeer
{
    enum BeerSockStatus_t
    {
        BEERSOCK_FAIL = -1,
        BEERSOCK_SUCCESS
    };
    class The_Beer_Sock
    {
        private Mutex mtx = new Mutex();

        IPEndPoint serverAddr;
        IPEndPoint otherServerAddr;
        IPEndPoint clntAddr;

        Socket server_sock;
        Socket my_clnt_sock;
        Socket other_clnt_sock;

        Thread serverProc;

        int status;

        byte[] msg = new byte[1024];

        public The_Beer_Sock(String ip, u16 port)
        {
            serverAddr = new IPEndPoint(IPAddress.Parse(ip), port);
        }

        private void serverBinding()
        {
            mtx.WaitOne();
            server_sock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            server_sock.Bind(serverAddr);
            server_sock.Listen(20);
            other_clnt_sock = server_sock.Accept();
            var ip = other_clnt_sock.RemoteEndPoint as IPEndPoint;
            connectServer(ip.Address.ToString(), (u16)(ip.Port));
            mtx.ReleaseMutex();
        }

        private void connectServer(String ip, u16 port)
        {
            otherServerAddr = new IPEndPoint(IPAddress.Parse(ip), port);
            my_clnt_sock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            my_clnt_sock.Connect(otherServerAddr);
        }

        public BeerSockStatus_t server_start()
        {
            serverProc = new Thread(() => serverBinding());
            serverProc.Start();
            return BeerSockStatus_t.BEERSOCK_SUCCESS;
        }

        public BeerSockStatus_t server_end()
        {
            server_sock.Close();
            my_clnt_sock.Close();
            other_clnt_sock.Close();
            return BeerSockStatus_t.BEERSOCK_SUCCESS;
        }

        public BeerSockStatus_t writeServer(String msg)
        {
            my_clnt_sock.Send(Encoding.ASCII.GetBytes(msg));
            return BeerSockStatus_t.BEERSOCK_SUCCESS;
        }

        public BeerSockStatus_t readClient()
        {
            other_clnt_sock.Receive(msg);
            return BeerSockStatus_t.BEERSOCK_SUCCESS;        
        }
    }
}
