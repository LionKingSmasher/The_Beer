all: compile

compile:
	if [ ! -d "ebin/" ]; then \
		mkdir ebin/ ;\
	fi

	erlc -pa ebin/ -o ebin/ DB/*.erl
	erlc -pa ebin/ -o ebin/ Server/*.erl
