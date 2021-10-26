-module(the_beer_dbms).
-author("Shin Hyun Kyu").
-export([dbms_init/0,
        create_database/1,
        create_table/3]).

-type key() :: atom() | string() | binary().

-spec dbms_init() -> map().
dbms_init() ->
    io:format("Welcome to The beer DBMS System\n"),
    make_dir("./The_Beer_Database").

create_database(DatabaseName) ->
    Database = get_sha256(DatabaseName),
    make_dir("./The_Beer_Database/" ++ Database),
    {ok, HashIO} = file:open("./The_Beer_Database/" ++ Database ++ "/TableHash", [write]),
    file:close(HashIO).

-spec create_table(key(), key(), [atom()]) -> ok | {error, Reason}.
create_table(DatabaseName, TableName, AttributeName) ->
    make_table_dir(DatabaseName, TableName),
    {ok, TableHashIO} = file:open("./The_Beer_Database/" ++ Database ++ "/TableHash", [write]),
    io:format(TableHashIO, "~s~n", [Table]),
    file:close(TableHashIO),
    {ok, TableSetIO} = file:open("./The_Beer_Database/" ++ Database ++ "/" ++ Table ++ "/TableSet", [write]),
    io:format(TableSetIO, "[~s:~b]", [Attribute]).

-spec select_table(key(), key(), [atom()]) -> ok | error.
select_table(DatabaseName, TableName, Attribute) ->
    Table = get_sha256(DatabaseName ++ TableName),
    Database = get_sha256(DatabaseName),
    {ok, Data} = file:read_file("./The_Beer_Database/" ++ Database ++ "/TableHash"),
    ReadBinary = binary:split(Data, <<"#">>),

insert_into(DatabaseName, TableName, Value) ->
    .

get_sha256(Str) ->
    <<Integer:256>> = crypto:hash(sha256, Str),
    io_lib:format("~64.16.0b", [Integer]).

make_table_dir(DatabaseName, TableName) ->
    Table = get_sha256(DatabaseName ++ TableName),
    Database = get_database(Database),
    make_dir("./The_Beer_Database/" ++ Database ++ "/" ++ Table).

write_all_list(FileIO, Arr) ->
    io:format(FileIO, "[~s:~s]~n", [lists:nth(1, Arr), lists:nth(2, Arr)]),

make_dir(Dir) -> 
    case file:make_dir(Dir) of
        ok -> ok;
        {error, eexist} -> ok;
        {error, Reason} -> {error, Reason}
    end.