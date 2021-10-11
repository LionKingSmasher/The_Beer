-module(the_beer_dbms).
-author("Shin Hyun Kyu").
-export([dbms_init/0,
        create_database/2]).

-spec dbms_init() -> List.
dbms_init() ->
    io:format("Welcome To The Beer DBMS"),
    [].

create_database(Database, DatabaseName) -> 
    DatabaseName ++ [DatabaseName, []].