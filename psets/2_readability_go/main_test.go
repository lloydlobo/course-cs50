package main

import (
	"testing"
)

func TestRunMain(t *testing.T) {
	main()
}
func BenchmarkRunMain(b *testing.B) {
	for i := 0; i < b.N; i++ {
		main()
	}
}
