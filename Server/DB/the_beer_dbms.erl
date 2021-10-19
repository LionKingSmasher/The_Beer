-module(the_beer_dbms).
-author("Shin Hyun Kyu").
-export([dbms_init/0,
        create_database/2,
        show_database/1]).

-type key() :: atom() | string() | binary().

-record(databases, {database=[]}).

-spec dbms_init() -> map().
dbms_init() ->
    io:format("Welcome to The beer DBMS System\n"),
    #databases{database = []}.

-spec create_database(map(), atom()) -> map().
create_database(Database, DatabaseName) -> 
    Database = Database#databases{database = Database#databases.database ++ [DatabaseName]}.

show_database(Database) ->
    maps:keys(Database).