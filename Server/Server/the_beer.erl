-module(the_beer).
-author("Shin Hyun Kyu").

-export([start_server/0]).

-include("ip.hrl").

start_server() -> 
    Pid = spawn_link(fun() ->
        {ok, LSocket} = gen_tcp:listen(?PORT, [binary, {active, false}, {ip, {10, 80, 163, 172}}]),
        spawn(fun() -> acceptState(LSocket) end),
        timer:sleep(infinity)
        end),
    {ok, Pid}.

acceptState(LSocket) ->
    {ok, ASocket} = gen_tcp:accept(LSocket),
    spawn(fun() -> acceptState(LSocket) end),
    handler(ASocket).

handler(ASocket) -> 
    inet:setopts(ASocket, [{active, once}]),
    receive
        {tcp, ASocket, <<"done">>} ->
            gen_tcp:close(ASocket);
        {tcp, ASocket, <<"test">>} ->
            gen_tcp:send(ASocket, "Welcome Server!"),
            handler(ASocket);
        {tcp, ASocket, BinaryMSG} ->
            gen_tcp:send(ASocket, "Your MSG: " ++ BinaryMSG),
            handler(ASocket)
    end.