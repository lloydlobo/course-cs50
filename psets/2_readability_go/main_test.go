package main

import (
	"testing"

	"example.com/readability/readability"
)

/*
   func TestRunMain(t *testing.T) {
       main()
   }
   func BenchmarkRunMain(b *testing.B) {
       for i := 0; i < b.N; i++ {
           main()
       }
   }
*/

func TestReadability(t *testing.T) {
	got := readability.Readability()
	want := 3
	if got != want {
		t.Errorf("Readability() = %v; want: %v", got, want)
	}
}

func BenchmarkReadability(b *testing.B) {
	for i := 0; i < b.N; i++ {
		readability.Readability()
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
BenchmarkReadability-12           571066              1997 ns/op
ok      example.com/readability 1.165s


# 2022-09-29 17:14

--- PASS: TestReadability (0.00s)
ok      example.com/readability 0.002s

*/
