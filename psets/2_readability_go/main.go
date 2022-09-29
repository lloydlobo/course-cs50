package main

import (
	"fmt"

	"example.com/readability/readability"
	"example.com/readability/testcases"
)

// Function main() uses Execute of package readability.
func main() {
	tc := testcases.GetGradeAndText()
	for i := 0; i < len(tc); i++ {
		out := readability.Execute(tc[i])
		fmt.Printf("out: %v\n", out)
	}
}

// DEVLOG
//
// 2022-09-24 11:37
// # Test Automation
//      $  fd --extension go | grep _test.go | entr go test
// # Continuous formating on change & save:
//      $ fd --extension go | entr gofmt .
//
