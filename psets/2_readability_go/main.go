package main

import (
	"example.com/readability/readability"
)

// Function main() uses Execute of package readability.
func main() {
	readability.Execute()
}

// DEVLOG
//
// 2022-09-24 11:37
// # Test Automation
//      $  fd --extension go | grep _test.go | entr go test
// # Continuous formating on change & save:
//      $ fd --extension go | entr gofmt .
//
