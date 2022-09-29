package main

import "testing"

// TODO: gofmt all *.go files/packages
// ➜  fd --extension go | xclip && echo (xclip -o) | grep go
// 09:20  ➜  fd --extension go | xclip && echo (xclip -o) >> test.txt
// $  fd --extension go | grep _test.go | entr go test
func TestRunMain(t *testing.T) {
	main()
}

func BenchmarkRunMain(b *testing.B) {
	for i := 0; i < b.N; i++ {
		main()
	}
}
