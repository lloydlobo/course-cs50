package main

import (
	"testing"

	"example.com/readability/readability"
	"example.com/readability/testcases"
)

func TestRunMain(t *testing.T) {
	main()
}
func BenchmarkRunMain(b *testing.B) {
	for i := 0; i < b.N; i++ {
		main()
	}
}

func TestReadabilityG3(t *testing.T) {
	tc := testcases.GetGradeAndText()
	got := readability.Readability(tc[2])
	want := 3
	if got != want {
		t.Errorf("Readability() = %v; want: %v", got, want)
	}
}
func BenchmarkReadabilityG3(b *testing.B) {
	tc := testcases.GetGradeAndText()
	for i := 0; i < b.N; i++ {
		readability.Readability(tc[2])
	}
}

func TestReadability(t *testing.T) {
	tc := testcases.GetGradeAndText()
	for i := 0; i < len(tc); i++ {
		got, want := readability.Readability(tc[i]), tc[i].Grade
		if got != want {
			t.Errorf("%v: Readability() = %v; want: %v", i, got, want)
		}

	}
}

func BenchmarkReadability(b *testing.B) {
	tc := testcases.GetGradeAndText()
	for i := 0; i < b.N; i++ {
		for i := 0; i < len(tc); i++ {
			readability.Readability(tc[i])
		}
	}
}

/*
Benchmark Log

# 2022-09-29 17:18

--- PASS: TestReadability (0.00s)
goos: linux
goarch: amd64
pkg: example.com/readability
cpu: Intel(R) Core(TM) i7-8700 CPU @ 3.20GHz
BenchmarkRunMain-12               108967             14598 ns/op
BenchmarkReadability-12           571066              1997 ns/op
ok      example.com/readability 1.165s


# 2022-09-29 17:14

--- PASS: TestReadability (0.00s)
ok      example.com/readability 0.002s

*/
