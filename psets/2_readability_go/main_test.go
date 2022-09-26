package main

import "testing"

// $  fd --extension go | grep _test.go | entr go test
func TestRunMain(t *testing.T) {
	main()
}
