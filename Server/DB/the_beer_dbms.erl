-module(the_beer_dbms).
-author("Shin Hyun Kyu").
-export([dbms_init/0,
        create_database/1,
        create_table/4,
        insert_into/3,
        select_table/3]).

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
    io:format(TableSetIO, "~s~s~n", [Attribute, Type]),
    file:close(TableSetIO),
    {ok, ObjectIO} = file:open("./The_Beer_Database/" ++ Database ++ "/" ++ Table ++ "/ObjectHash", [write]),
    file:close(ObjectIO).

get_arr_value_index([Head | Tail], CompareAtom, Index) -> 
    if 
        Head == CompareAtom ->
            Index;
        Tail == [] ->
            {error, not_found_index};
        true -> 
            get_arr_value_index(Tail, CompareAtom, Index + 1)
    end.

get_arr_value_index(Arr, CompareAtom) ->
    get_arr_value_index(Arr, CompareAtom, 1).

get_file_object_index(Path, [HeadOH | TailOH]) ->
    io:format("~s~n", [binary_to_list(HeadOH)]),
    {ok, ReadBinary} = file:read_file(Path ++ "/" ++ binary_to_list(HeadOH)),
    io:format("Binary: ~s~n", [binary_to_list(ReadBinary)]),
    if
        TailOH == [<<>>] ->
            % io:format("Empty!!~n"),
            [];
        true ->
            % io:format("Not Empty!~n"),
            [HeadOH] ++ get_file_object_index(Path, TailOH)
    end.

get_binary_by_value(BinaryVal) ->
    .

-spec select_table(key(), key(), [atom()]) -> ok | error.
select_table(DatabaseName, TableName, [HeadAttribute | TailAttribute]) ->
    Table = get_sha256(DatabaseName ++ TableName),
    Database = get_sha256(DatabaseName),
    {ok, AllObjectBinary} = file:read_file("./The_Beer_Database/" ++ Database ++ "/" ++ Table ++ "/ObjectHash"),
    io:format("~s~n", [binary_to_list(AllObjectBinary)]),
    AllObject = binary:split(AllObjectBinary, <<"\n">>),
    AllValue = get_file_object_index("./The_Beer_Database/" ++ Database ++ "/" ++ Table, AllObject).

% -spec select_table(key(), key(), [atom()]) -> ok | error.
% select_table(DatabaseName, TableName, Attribute) ->
%     Table = get_sha256(DatabaseName ++ TableName),
%     Database = get_sha256(DatabaseName),
%     load_All_File("./The_Beer_Database/" ++ Database ++ "/" ++ Table ++ "/TableSetting").

-spec insert_into(key(), key(), [any()]) -> ok | error.
insert_into(DatabaseName, TableName, Value) ->
    TableObject = get_All_Value_List(Value),
%   io:format("~s~n", ["./The_Beer_Database/" ++ get_sha256(DatabaseName) ++ "/" ++ get_sha256(DatabaseName ++ TableName) ++ "/" ++ get_sha256(TableObject)]),
    {ok, ObjectIO} = file:open("./The_Beer_Database/" ++ get_sha256(DatabaseName) ++ "/" ++ get_sha256(DatabaseName++TableName) ++ "/" ++ get_sha256(TableObject), [write]),
    io:format(ObjectIO, "~s~n", [TableObject]),
    file:close(ObjectIO),
    {ok, ObjectHashIO} = file:open("./The_Beer_Database/" ++ get_sha256(DatabaseName) ++ "/" ++ get_sha256(DatabaseName++TableName) ++ "/ObjectHash", [write]),
    io:format(ObjectHashIO, "~s~n", get_sha256(TableObject)),
    file:close(ObjectHashIO).

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
    "#".

-spec get_All_Type_List([dbms_type()]) -> string().
get_All_Type_List([Head|Tail]) ->
    atom_to_list(Head) ++ "#" ++ get_All_Type_List(Tail);

get_All_Type_List([]) ->
    "".

load_All_File(FilePath) ->
    {ok, FileData} = file:read_file(FilePath),
    binary:split(FileData, <<"#">>).

load_All_Hash(FilePath) ->
    {ok, FileData} = file:read_file(FilePath),
    binary:split(FileData, <<"\n">>).

concat_All_Binary([HeadBinary | TailBinary]) ->
    binary_to_list(HeadBinary) ++ concat_All_Binary(TailBinary);

concat_All_Binary([]) ->
    "".

-spec read_value_list([key()], integer(), integer()) -> key() | {error, atom()}.
read_value_list([Head|Tail], Num, Count) ->
    if
        Num == Count ->
            Head;
        Tail == [] ->
            {error, value_not_found};
        true ->
            read_value_list(Tail, Num, Count + 1)
    end.

read_value_by_file(FileIO, Num) ->
    read_value_list(FileIO, Num, 1).
