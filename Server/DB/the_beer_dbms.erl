-module(the_beer_dbms).
-author("Shin Hyun Kyu").
-export([dbms_init/0,
        create_database/1,
        create_table/4,
        insert_into/3]).

-type key() :: atom() | string() | binary().

-type dbms_type() :: 'Int' | 'String' | 'Atom'. 

-spec dbms_init() -> map().
dbms_init() ->
    io:format("Welcome to The beer DBMS System\n"),
    make_dir("./The_Beer_Database").

create_database(DatabaseName) ->
    Database = get_sha256(DatabaseName),
    make_dir("./The_Beer_Database/" ++ Database),
    {ok, HashIO} = file:open("./The_Beer_Database/" ++ Database ++ "/TableHash", [write]),
    file:close(HashIO).

-spec create_table(key(), key(), [atom()], [dbms_type()]) -> ok | error.
create_table(DatabaseName, TableName, AttributeName, TypeName) ->
    Database = get_sha256(DatabaseName),
    Table = make_table_dir(DatabaseName, TableName),
    {ok, TableHashIO} = file:open("./The_Beer_Database/" ++ Database ++ "/TableHash", [write]),
    Attribute = get_All_Value_List(AttributeName),
    Type = get_All_Type_List(TypeName),
    TableHash = get_sha256(Attribute),
    io:format(TableHashIO, "~s", [Table]),
    file:close(TableHashIO),
    {ok, TableSetIO} = file:open("./The_Beer_Database/" ++ Database ++ "/" ++ Table ++ "/TableSetting", [write]),
    io:format(TableSetIO, "~s", [Type]),
    file:close(TableSetIO),
    {ok, ObjectIO} = file:open("./The_Beer_Database/" ++ Database ++ "/" ++ Table ++ "/ObjectHash", [write]),
    file:close(ObjectIO).

-spec select_table(key(), key(), [atom()]) -> ok | error.
select_table(DatabaseName, TableName, Attribute) ->
    Table = get_sha256(DatabaseName ++ TableName),
    Database = get_sha256(DatabaseName),
    {ok, Data} = file:read_file("./The_Beer_Database/" ++ Database ++ "/TableHash"),
    ReadBinary = binary:split(Data, <<"#">>).

-spec insert_into(key(), key(), any()) -> ok | error.
insert_into(DatabaseName, TableName, Value) ->
    TableObject = get_All_Value_List(Value),
    {ok, ObjectIO} = file:open("./The_Beer_Database/" ++ get_sha256(DatabaseName) ++ "/" ++ get_sha256(TableName) ++ "/" ++ get_sha256(TableObject)),
    io:format(ObjectIO, "~s~n", get_sha256(TableObject)),
    file:close(ObjectIO).

get_sha256(Str) ->
    <<Integer:256>> = crypto:hash(sha256, Str),
    io_lib:format("~64.16.0b", [Integer]).

make_table_dir(DatabaseName, TableName) ->
    Table = get_sha256(DatabaseName ++ TableName),
    Database = get_sha256(DatabaseName),
    make_dir("./The_Beer_Database/" ++ Database ++ "/" ++ Table),
    Table.

make_dir(Dir) -> 
    case file:make_dir(Dir) of
        ok -> ok;
        {error, eexist} -> ok;
        {error, Reason} -> {error, Reason}
    end.

get_All_Value_List([Head|Tail]) ->
    if
        is_atom(Head) ->
            Val = atom_to_list(Head);
        is_integer(Head) ->
            Val = integer_to_list(Head);
        true ->
            Val = Head
    end,
    "#" ++ Val ++ get_All_Value_List(Tail);

get_All_Value_List([]) ->
    "".

-spec get_All_Type_List([dbms_type()]) -> string().
get_All_Type_List([Head|Tail]) ->
    atom_to_list(Head) ++ "#" ++ get_All_Type_List(Tail);

get_All_Type_List([]) ->
    "".

load_All_File(FilePath) ->
    {ok, FileData} = file:read_file(FilePath),
    .

concat_All_Binary([HeadBinary | TailBinary]) ->
    binary_to_list(HeadBinary) ++ concat_All_Binary(TailBinary);

concat_All_Binary([]) ->
    "".