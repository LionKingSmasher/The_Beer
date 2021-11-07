using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Net;
using System.Net.Sockets;

namespace WinTheBeer
{
    /// <summary>
    /// Window1.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class Window1 : Window
    {
        IPEndPoint NodeServerAddr = new IPEndPoint(IPAddress.Parse("10.80.161.90"), 10000);
        Socket nodeServerSock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        String[] nodeCommand = {
            "register name=", // register
            "get ip",         // get node list
            "done"            // finish connect
        };
        public Window1()
        {
            InitializeComponent();
        }

        private void Connect_Server_Click(object sender, RoutedEventArgs e)
        {
            nodeServerSock.Connect(NodeServerAddr);
            nodeServerSock.Send(Encoding.ASCII.GetBytes(nodeCommand[0] + UserNameBox.Text));
        }
    }
}
