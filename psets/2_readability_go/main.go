package main

import (
	// "fmt"

	"fmt"

	"example.com/readability/readability"
	// "example.com/readability/testcases"
)

// Function main() uses Execute of package readability.
func main() {
	text := readability.GetTextStr()
	outs := []string{}

	for i := 0; i < len(text); i++ {
		out := readability.Execute(text[i])
		outs = append(outs, out)
	}

	fmt.Println(outs)
}

// func main() {
// 	tc := testcases.GetGradeAndText()
// 	str := &tc
// 	for i := 0; i < len(*str); i++ {
// 		got := (*str)[i]
// 		// out := readability.Execute(tc[i])
// 		out := readability.Execute(got)
// 		fmt.Printf("str: %v\n", (*str)[i])
// 		fmt.Printf("out: %v\n", out)
// 	}
// }

// DEVLOG
//
// 2022-09-24 11:37
// # Test Automation
//      $  fd --extension go | grep _test.go | entr go test
// # Continuous formating on change & save:
//      $ fd --extension go | entr gofmt .
//
