
all: job.cc
	g++ job.cc -lgmp -lgmpxx -O3 -Wall -pedantic -Wextra -o job

TEST: job.cc
	g++ job.cc -lgmp -lgmpxx -O3 -Wall -pedantic -Wextra -o job -DTEST


cpplint: job.cc
	@cpplint --filter=-legal/copyright,-runtime/references $<

cppcheck: job.cc
	@cppcheck --enable=all --suppress=missingIncludeSystem $< --check-config

clean:
	rm -f job
