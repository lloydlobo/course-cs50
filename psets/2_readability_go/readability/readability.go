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

func Execute() {
	grade := Readability()
	fmt.Printf("grade: %v\n\n", grade) // 3
}

func Readability() int {
	gat := tc.GetGradeAndText()
	return int(Run(gat))
}

// Run()
//
// 3, Congratulations! Today is your day. You're off to Great Places! You're off and away!
// 64 letters per 14 words = avg(464.29 Letters / 100 words). (because 65 / 14 * 100 = 464.29).
// 4 sentences per 14 words = avg(28.57 Sentences / 100 words). (because 4 / 14 * 100 = 28.57).
func Run(t []tc.GradeAndText) float64 {
	t3 := t[2].Text
	lw, ll, ls := LenWords(t3), LenLetters(t3), LenSentences(t3) // -> 14 words.

	fmt.Printf("l:%v; s:%v; w:%v\n", ll, ls, lw)
	return GetIndexCLIPer100W(lw, ll, ls)
}

// GetIndexCLIPer100W()
//
// we get an answer of Grade 3
// (because 0.0588 * 464.29 - 0.296 * 28.57 - 15.8 = 3):
func GetIndexCLIPer100W(lw, ll, ls int) float64 {
	avgl, avgS := 100*float64(ll)/float64(lw), 100*float64(ls)/float64(lw)
	return 0.0588*avgl - 0.296*avgS - 15.8
}

// LenWords()
func LenWords(t string) int {
	return len(strings.Split(t, " ")) // 14 words.
}

// LenLetters()
//
// 64 letters per 14 words = avg(464.29 Letters / 100 words).
// (because 65 / 14 * 100 = 464.29).
func LenLetters(s string) int {
	sLow := strings.ToLower(s)
	lenAll := len(strings.Split(s, ""))

	idxNonAlphabets := IndexNonAlphabets([]byte(sLow))

	return lenAll - len(idxNonAlphabets)
}

// LenSentences() find period "." or ! or "?"
//
// fmt.Printf("slicePeriod: %v\n", slicePeriod)
// fmt.Printf("n == 4?: %v; got: %v\n", n == 4, n)
func LenSentences(s string) int {
	B := []byte(strings.ToLower(s))
	sntc := FindLineTerminators(B)

	return len(sntc)
}

// IndexNonAlphabets return slice of index of non-alphabets.
//
// ascii not in the range of: 65-90 (A-Z) && 97-122 (a-z)
// https://asciichart.com/
func IndexNonAlphabets(B []byte) (pos []int) {
	for i := 0; i < len(B); i++ {
		b := B[i]
		isAToZ := b >= 65+32 && b <= 90+32
		if !isAToZ {
			pos = append(pos, i)
		}
	}
	return
}

// FindLineTerminators() finds the positions of line ends.
//
// It find period "." or ! or "?".
func FindLineTerminators(B []byte) (pos []int) {
	for i := 0; i < len(B); i++ {
		b := B[i]
		isDot, isQuestionMark, isExclamation := b == 46, b == 63, b == 33
		if isDot || isQuestionMark || isExclamation {
			pos = append(pos, i)
		}
	}
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
