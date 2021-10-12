package TheBeer.beersock

import java.lang.Exception
import java.io.BufferedReader
import java.io.BufferedWriter
import java.io.InputStreamReader
import java.io.OutputStreamWriter
import java.net.Socket
import java.net.InetSocketAddress
import java.net.ServerSocket

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

    var server_buffer : BufferedReader? = null
    var my_clnt_buffer : BufferedWriter? = null
    var other_clnt_buffer : BufferedWriter? = null

    init {
        server_sock = ServerSocket(port)
    }

    fun server_start() : BeerSockStatus {
        other_clnt_sock = server_sock?.accept() ?: null
        if(other_clnt_sock == null)
            return BeerSockStatus.BEERSOCK_FAIL
        return BeerSockStatus.BEERSOCK_SUCCESS
    }

    fun server_stop() : BeerSockStatus {
        return BeerSockStatus.BEERSOCK_SUCCESS
    }

    fun server_end() : BeerSockStatus {
        return BeerSockStatus.BEERSOCK_SUCCESS
    }

    fun connectServer(ip: String, port: Int) : BeerSockStatus {
        return BeerSockStatus.BEERSOCK_SUCCESS
    }

    fun writeServer(msg: String) : BeerSockStatus {
        return BeerSockStatus.BEERSOCK_SUCCESS
    }

    fun readClient(msg: String) : BeerSockStatus {
        return BeerSockStatus.BEERSOCK_SUCCESS
    }
}