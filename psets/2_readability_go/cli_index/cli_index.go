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
