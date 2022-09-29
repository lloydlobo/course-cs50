// Package `cli_index`: Coleman–Liau Index
//
// https://readabilityformulas.com/coleman-liau-readability-formula.php
// Hello
//
// `CLI` = 0.0588 * `L` - 0.296 * `S` - 15.8
// `L` is the average number of letters per 100 words.
// `S` is the average number of sentences per 100 words.
//
// Example:
//
//	The best things in an artist’s work are so much a matter of intuition,
//	that there is much to be said for the point of view that would
//	altogether discourage intellectual inquiry into artistic phenomena
//	on the part of the artist. Intuitions are shy things and apt to
//	disappear if looked into too closely.
//	And there is undoubtedly a danger that too much knowledge and
//	training may supplant the natural intuitive feeling of a student,
//	leaving only a cold knowledge of the means of expression in its place.
//	For the artist, if he has the right stuff in him ...
//
// The abstract contains 4 sentences, 100 words, and 448 letters or digits;
// `L` is 448 and `S` is 4.
//
// Formula: `CLI = 0.0588 x 448(L) - 0.296 x 4.0(S) - 15.8 = 10.6`
// Therefore, this formula grades this abstract of text at a grade level
// of 10.6, or roughly appropriate for a 10-11th grade high school student.
package cli_index

import (
	"fmt"
	"math"
	"strings"

	"example.com/readability/testcases"
)

// TODO: Run this when *****okejoke****** binary,
//   returns the string and this grades it.
//
// https://cs50.harvard.edu/x/2022/psets/2/readability/
// A number of “readability tests” have been developed over the years that define formulas for computing the reading level of a text. One such readability test is the Coleman-Liau index. The Coleman-Liau index of a text is designed to output that (U.S.) grade level that is needed to understand some text. The formula is
//
// index = 0.0588 * L - 0.296 * S - 15.8
// where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
//
// Let’s write a program called readability that takes a text and determines its reading level. For example, if user types in a line of text from Dr. Seuss, the program should behave as follows:
//
// $ ./readability
// Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
// Grade 3
// The text the user inputted has 65 letters, 4 sentences, and 14 words. 65 letters per 14 words is an average of about 464.29 letters per 100 words (because 65 / 14 * 100 = 464.29). And 4 sentences per 14 words is an average of about 28.57 sentences per 100 words (because 4 / 14 * 100 = 28.57). Plugged into the Coleman-Liau formula, and rounded to the nearest integer, we get an answer of 3 (because 0.0588 * 464.29 - 0.296 * 28.57 - 15.8 = 3): so this passage is at a third-grade reading level.

func AverageLetters100Words(s string) int {
	var (
		length  int
		n       = len(s)
		split   = strings.Split(s, "") // no space is letter length.
		nSplit  = len(split)
		lenWord = len(strings.Split(s, " "))
	)

	if lenWord >= 100 {
		length = nSplit / n
	} else {
		length = len(split)
	}

	fmt.Printf("len: %v; | lett: %v\n\n", length, split)
	return length
}

func AverageSentences100Words(s string) int {
	var (
		length  int
		n       = len(s)
		split   = strings.Split(s, ".") // no space is letter length.
		nSplit  = len(split)
		lenWord = len(strings.Split(s, " "))
	)

	if lenWord >= 100 {
		length = nSplit / n
	} else {
		length = len(split)
	}

	fmt.Printf("len: %v; | lett: %v\n\n", length, split)
	return length
}

// CLI = 0.0588 * L - 0.296 * S - 15.8
// 26.342399999999998 - 1.184 - 15.8
func CalcCliIndex(avgWordLetters, avgWSentence int) float64 {
	grade := (0.0588*float64(avgWordLetters) - 0.296*float64(avgWSentence) - 15.8)
	fmt.Printf("grade: %v\n", grade)
	return grade
}

func ColemanLiauReadabilityIndex(gradeAndText []testcases.GradeAndText) float64 {
	var (
		index []int
		l     int
		s     int
		len   = len(gradeAndText)
	)

	for i := 0; i < int(math.Min(2, float64(len))); i++ {
		_, t := gradeAndText[i].Grade, gradeAndText[i].Text

		// TODO Implement the AverageLetters100Words & AverageSentences100Words functions!!!
		l, s = AverageLetters100Words(t), AverageSentences100Words(t)

		index = append(index, int(CalcCliIndex(l, s)))
	}
	return CalcCliIndex(l, s)
}

// Similar to the Automated Readability Index (abbv. ARI)
// [ARI](https://readabilityformulas.com/automated-readability-index.php),
// but unlike most of the other grade-level predictors, the
// Coleman–Liau relies on characters instead of syllables per word.
// Instead of using syllable/word and sentence length indices, Meri Coleman
// and T. L. Liau believed that computerized assessments understand characters
// more easily and accurately than counting syllables and sentence length.
