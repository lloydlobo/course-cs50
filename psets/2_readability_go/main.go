package main

import (
	"fmt"

	"example.com/readability/readability"
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
