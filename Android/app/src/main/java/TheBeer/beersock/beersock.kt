package TheBeer.beersock

import java.io.*
import java.lang.Exception
import java.net.Socket
import java.net.InetSocketAddress
import java.net.ServerSocket
import java.net.UnknownHostException

enum class BeerSockStatus {
    BEERSOCK_FAIL,
    BEERSOCK_SUCCESS
}

class BeerSock(port: Int) {

    var server_addr : InetSocketAddress? = null
    var other_server_addr : InetSocketAddress? = null
    var client_addr : InetSocketAddress? = null

    var server_sock : ServerSocket? = null  // Server Socket
    var my_clnt_sock : Socket? = Socket()    // My client Socket
    var other_clnt_sock : Socket? = Socket() // Other Client Socket

    var my_clnt_buffer : OutputStream? = null
    var other_clnt_buffer : InputStream? = null

    var clntMessage : ByteArray = ByteArray(1024) { 0 }
    var msgSize : Int = 0

    var MyClntMessage : ByteArray = ByteArray(1024) { 0 }
    var MyMsgSize : Int = 0

    init {
        server_sock = ServerSocket(port)
    }

    fun server_start() : BeerSockStatus {
        other_clnt_sock = server_sock?.accept() ?: null
        if(other_clnt_sock == null)
            return BeerSockStatus.BEERSOCK_FAIL
        other_clnt_buffer = other_clnt_sock?.getInputStream()
        return BeerSockStatus.BEERSOCK_SUCCESS
    }

    fun server_stop() : BeerSockStatus {
        return BeerSockStatus.BEERSOCK_SUCCESS
    }

    fun server_end() : BeerSockStatus {
        try{
            server_sock?.close()
        }
        catch(e: Exception){
            return BeerSockStatus.BEERSOCK_FAIL
        }
        return BeerSockStatus.BEERSOCK_SUCCESS
    }

    fun connectServer(ip: String, port: Int) : BeerSockStatus {
        server_addr = InetSocketAddress(ip, port)
        try{
            my_clnt_sock?.connect(server_addr)
        }
        catch(ex: UnknownHostException) {
            return BeerSockStatus.BEERSOCK_FAIL
        }
        my_clnt_buffer = my_clnt_sock?.getOutputStream()
        return BeerSockStatus.BEERSOCK_SUCCESS
    }

    fun writeServer(msg: String) : BeerSockStatus {
        MyClntMessage = msg.toByteArray()
        return BeerSockStatus.BEERSOCK_SUCCESS
    }

    fun readClient() : ByteArray {
        msgSize = other_clnt_buffer!!.read(clntMessage)
        return clntMessage
    }
}