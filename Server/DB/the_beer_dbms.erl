-module(the_beer_dbms).
-author("Shin Hyun Kyu").
-export([dbms_init/0,
        create_database/2,
        show_database/1]).

-type key() :: atom() | string() | binary().

-spec dbms_init() -> map().
dbms_init() ->
    rd(databases, {database = []}),
    io:format("Welcome to The beer DBMS System\n")
    #databases{database = []}.

-spec create_database(map(), atom()) -> map().
create_database(Database, DatabaseName) -> 
    #{}.

show_database(Database) ->
    maps:keys(Database).