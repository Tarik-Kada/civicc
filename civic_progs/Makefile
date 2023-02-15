.PHONY: run clean

%.s: %.cvc
	civcc -o $@ $^

%.out: %.s
	civas -o $@ $^

run: array.out
	civvm $^

clean:
	rm -f *.cpp *.s *.out
