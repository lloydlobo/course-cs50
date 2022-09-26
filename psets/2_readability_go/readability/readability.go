/*
Package readability

	Your program must prompt the user for a string of text using get_string.

	Your program should count the number of letters, words, and sentences in
	the text. You may assume that a letter is any lowercase character from a to z
	or any uppercase character from A to Z, any sequence of characters separated
	by spaces should count as a word, and that any occurrence of a period,
	exclamation point, or question mark indicates the end of a sentence.

	Your program should print as output "Grade X" where X is the grade level
	computed by the Coleman-Liau formula, rounded to the nearest integer.

	If the resulting index number is 16 or higher (equivalent to or greater
	than a senior undergraduate reading level), your program should output "Grade
	16+" instead of giving the exact index number. If the index number is less
	than 1, your program should output "Before Grade 1".

*
*/
package readability

import (
	"fmt"

	"example.com/readability/cli_index"
	"example.com/readability/testcases"
)

func readability() {
	fmt.Printf("\nreadability ->\n\n")
}

func Execute() {
	readability()

	gat := testcases.GetGradeAndText()

	_ = cli_index.ColemanLiauReadabilityIndex(gat)

	// fmt.Printf("grade: %v\n", grade)
}
