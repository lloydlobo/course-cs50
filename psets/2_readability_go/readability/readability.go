/*
Package readability
  - Your program must prompt the user for a string of text using get_string.
  - Your program should count the number of letters, words, and sentences in
    the text. You may assume that a letter is any lowercase character from a to z
    or any uppercase character from A to Z, any sequence of characters separated
    by spaces should count as a word, and that any occurrence of a period,
    exclamation point, or question mark indicates the end of a sentence.
  - Your program should print as output "Grade X" where X is the grade level
    computed by the Coleman-Liau formula, rounded to the nearest integer.
  - If the resulting index number is 16 or higher (equivalent to or greater
    than a senior undergraduate reading level), your program should output "Grade
    16+" instead of giving the exact index number. If the index number is less
    than 1, your program should output "Before Grade 1".
*/
package readability

import (
	"fmt"
	"strings"

	tc "example.com/readability/testcases"
)

// "example.com/readability/cli_index"
func readability() {
	fmt.Printf("\nreadability ->\n\n")
	gat := tc.GetGradeAndText()
	Run(gat)
	// _ = cli_index.ColemanLiauReadabilityIndex(gat)
	// fmt.Printf("grade: %v\n", grade)
}
func Execute() {
	readability()
}

// $ ./readability
// Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
// Grade 3
//
// The text the user inputted has 65 letters, 4 sentences, and 14 words.
// 65 letters per 14 words is an average of about 464.29 letters per 100 words
// (because 65 / 14 * 100 = 464.29).
//
// And 4 sentences per 14 words is an average of about 28.57 sentences per 100 words
// (because 4 / 14 * 100 = 28.57).
//
// Plugged into the Coleman-Liau formula, and rounded to the nearest integer,
func Run(t []tc.GradeAndText) {
	var (
		gt3    = t[2]
		g3, t3 = gt3.Grade, gt3.Text
	)
	fmt.Println(g3, t3) // 3, Congratulations! Today is your day. You're off to Great Places! You're off and away!

	lw := lenWords(t3)     // -> 14 words.
	ll := lenLetters(t3)   // 64 letters per 14 words = avg(464.29 Letters / 100 words). (because 65 / 14 * 100 = 464.29).
	ls := lenSentences(t3) // 4 sentences per 14 words = avg(28.57 Sentences / 100 words). (because 4 / 14 * 100 = 28.57).
	fmt.Printf("l:%v; s:%v; w:%v", ll, ls, lw)
	// we get an answer of Grade 3
	// (because 0.0588 * 464.29 - 0.296 * 28.57 - 15.8 = 3):
}

func lenWords(t string) int {
	return len(strings.Split(t, " ")) // 14 words.
}

// 64 letters per 14 words = avg(464.29 Letters / 100 words).
// (because 65 / 14 * 100 = 464.29).
func lenLetters(s string) int {
	var (
		sLow  = strings.ToLower(s)
		space = len(strings.Split(s, ""))
	)
	nonAlphabets := indexNonAlphabets([]byte(sLow))
	return space - len(nonAlphabets)
}

// indexNonAlphabets return slice of index of non-alphabets.
// ascii not in the range of: 65-90 (A-Z) && 97-122 (a-z)
// https://asciichart.com/
func indexNonAlphabets(B []byte) (pos []int) {
	for i := 0; i < len(B); i++ {
		b := B[i]
		isAToZ := b >= 65+32 && b <= 90+32
		if !isAToZ {
			pos = append(pos, i)
		}
	}
	return
}

func lenSentences(t string) (n int) {
	return
}

// TODO: Run this when *****okejoke****** binary,
//   returns the string and this grades it.
//
// https://cs50.harvard.edu/x/2022/psets/2/readability/
// A number of “readability tests” have been developed over the years
// that define formulas for computing the reading level of a text.
// One such readability test is the Coleman-Liau index.
// The Coleman-Liau index of a text is designed to
// output that (U.S.) grade level that is needed to understand some text.
// The formula is
// index = 0.0588 * L - 0.296 * S - 15.8
// where L is the average number of letters per 100 words in the text,
// and S is the average number of sentences per 100 words in the text.
//
// Let’s write a program called readability that takes a text
// and determines its reading level.
// For example, if user types in a line of text from Dr. Seuss,
// the program should behave as follows:
//
// $ ./readability
// Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
// Grade 3
// The text the user inputted has 65 letters, 4 sentences, and 14 words.
// 65 letters per 14 words is an average of about 464.29 letters per 100 words
// (because 65 / 14 * 100 = 464.29).
// And 4 sentences per 14 words is an average of about 28.57 sentences per 100 words
// (because 4 / 14 * 100 = 28.57).
// Plugged into the Coleman-Liau formula, and rounded to the nearest integer,
// we get an answer of 3 (because 0.0588 * 464.29 - 0.296 * 28.57 - 15.8 = 3):
// so this passage is at a third-grade reading level.
