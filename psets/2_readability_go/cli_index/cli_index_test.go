// CLI = 0.0588 * L - 0.296 * S - 15.8
// 26.342399999999998 - 1.184 - 15.8
// readability 9.358399999999998 cliIndex: 9.358399
package cli_index

import (
	"testing"

	"example.com/readability/helper"
	"example.com/readability/testcases"
)

func TestCalcCliIndex(t *testing.T) {
	l, s, precision := 448, 4, 4
	got, want := helper.RoundFloat(CalcCliIndex(l, s), precision), helper.RoundFloat(9.358399, precision)
	if got != want {
		t.Errorf("CalcCliIndex(%v,%v) = %v; want: %v", l, s, got, want)
	}
}

/*
2022-09-24 11:28

	11:24  ➜  go test -v -bench=.
	=== RUN   TestCalcCliIndex
	--- PASS: TestCalcCliIndex (0.00s)
	goos: linux
	goarch: amd64
	pkg: example.com/readability/cli_index
	cpu: Intel(R) Core(TM) i7-8700 CPU @ 3.20GHz
	BenchmarkCalcCliIndex
	BenchmarkCalcCliIndex-12        1000000000               0.2342 ns/op
	ok      example.com/readability/cli_index       0.263s
	PASS
*/
func BenchmarkCalcCliIndex(b *testing.B) {
	l, s := 448, 4
	for i := 0; i < b.N; i++ {
		CalcCliIndex(l, s)
	}
}

//	type GradeAndText struct {
//		Grade int
//		Text  string
//	}
func TestColemanLiauReadabilityIndex(t *testing.T) {

	textgrade := testcases.GetGradeAndText()
	for i := 0; i < len(textgrade); i++ {
		l, s, precision := AverageLetters100Words(textgrade[i].Text), AverageSentences100Words(textgrade[i].Text), 4

		got, want := helper.RoundFloat(ColemanLiauReadabilityIndex(textgrade), precision), helper.RoundFloat(9.358399, precision)
		if got != want {
			t.Errorf("CalcCliIndex(%v,%v) = %v; want: %v", l, s, got, want)
		}

	}

}

/*
2022-09-24 11:28

	11:28  ✗  go test -v -bench=.

	=== RUN   TestCalcCliIndex
	--- PASS: TestCalcCliIndex (0.00s)
	=== RUN   TestColemanLiauReadabilityIndex
	--- PASS: TestColemanLiauReadabilityIndex (0.00s)
	goos: linux
	goarch: amd64
	pkg: example.com/readability/cli_index
	cpu: Intel(R) Core(TM) i7-8700 CPU @ 3.20GHz
	BenchmarkCalcCliIndex
	BenchmarkCalcCliIndex-12                        1000000000               0.2340 ns/op
	BenchmarkColemanLiauReadabilityIndex
	BenchmarkColemanLiauReadabilityIndex-12         1000000000               0.2329 ns/op
	PASS
	ok      example.com/readability/cli_index       0.520s
*/
func BenchmarkColemanLiauReadabilityIndex(b *testing.B) {
	textgrade := testcases.GetGradeAndText()
	for i := 0; i < b.N; i++ {
		ColemanLiauReadabilityIndex(textgrade)
	}
}
