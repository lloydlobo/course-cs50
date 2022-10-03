package main

import (
	"fmt"

	"example.com/readability/readability"
)

// Function main() uses Execute of package readability.
func main() {
	readability.Run()
	text := readability.GetTextStr()
	outputs := []string{}

	for i := 0; i < len(text); i++ {
		out := readability.ProcessGrade(text[i])
		outputs = append(outputs, out)
	}
	fmt.Println(outputs)
}

// https://www.geeksforgeeks.org/interfaces-in-golang/
// Go program to illustrate
// the type assertion
func myfun(a interface{}) {
	// Extracting the value of a
	val := a.(string)
	fmt.Println("Value: ", val)
}

// Value:  GeeksforGeeks
func assertMyfunType() {
	var val interface {
	} = "GeeksforGeeks"

	myfun(val)
}

// Go program to illustrate
// the type assertion
func myfunAdvanced(a interface{}) {
	// Extracting the value of a.
	val, okBool := a.(string)
	fmt.Println("Value: ", val, okBool)
}

// Value:   false
// Value:  GeeksforGeeks true
func assertMyfunTypeAdvanced() {
	var a1 interface {
	} = 98.09
	myfunAdvanced(a1)

	var a2 interface {
	} = "GeeksforGeeks"
	myfunAdvanced(a2)
}
