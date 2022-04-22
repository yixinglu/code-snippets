obj:=$(shell echo *.o)
test_obj:=$(filter %est.o, $(obj))
main_obj:=main.o
run_all_obj:=$(test_obj) $(main_obj)
run_all:=$(basename $(run_all_obj))
other_obj:=$(filter-out $(run_all_obj), $(obj))

all:$(run_all)
	@echo $(run_all)
	@echo $(other_obj)
	mv main nvwa

$(run_all):%:%.o
	g++ -o $@ $< $(other_obj)

clean:
	rm -f *.o nvwa test
