-module(the_beer).
-author("Shin Hyun Kyu").

-export([start_server/0]).
-import(the_beer_dbms, [
            dbms_init/0,
            create_database/1,
            create_table/4,
            insert_into/3,
            select_table/3
        ]).

-include("ip.hrl").

start_server() -> 
    init_database(),
    Pid = spawn_link(fun() ->
        {ok, LSocket} = gen_tcp:listen(?PORT, [binary, {active, false}, {ip, {10, 80, 162, 236}}]),
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
        {tcp, ASocket, <<"get ip id=", X/binary>>} ->
            % the_beer_dbms:select_table("TheBeer", "NodeList", )
            handler(ASocket);
        {tcp, ASocket, <<"register name=", X/binary>>} ->
            {ok, {Ip, Port}} = inet:peername(ASocket),
            the_beer_dbms:insert_into("TheBeer", "NodeList", [binary_to_list(X), inet:ntoa(Ip), integer_to_list(Port)]),
            handler(ASocket);
        {tcp, ASocket, BinaryMSG} -> % Test Section
            {ok, {Ip, Port}} = inet:peername(ASocket),
            io:format("~s : ~s~n", [inet:ntoa(Ip), BinaryMSG]),
            gen_tcp:send(ASocket, "Your MSG: " ++ BinaryMSG),
            handler(ASocket)
    end.

init_database() ->
    the_beer_dbms:create_database("TheBeer"),
    the_beer_dbms:create_table("TheBeer", "NodeList", ['Name', 'IP', 'PORT'], ['String', 'String']),
    io:format("The Beer Database Initialized~n").