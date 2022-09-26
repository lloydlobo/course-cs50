package testcases

import (
	"example.com/readability/helper"
)

type GradeAndText struct {
	Grade int
	Text  string
}

type Grade struct {
	Grade int
}

type Text struct {
	Text string
}

// Function aggregates Grades and Texts into slices together.
func appendGradeAndText(lenG int, grades []int, texts []string) []GradeAndText {
	var (
		g    Grade
		t    Text
		gat  GradeAndText
		gats = make([]GradeAndText, lenG)
	)

	for i := 0; i < lenG; i++ {
		g.Grade, t.Text = grades[i], texts[i]
		gat.Grade, gat.Text = g.Grade, t.Text
		gats[i].Grade, gats[i].Text = gat.Grade, gat.Text
	}

	return gats
}

// Function receives Grades and Texts handles errors if any.
// Then appends corresponding grade with its text together.
func GetGradeAndText() []GradeAndText {
	g, t := GetGradesInt(), GetTextStr() // Retrieve testcases grades and text.
	gLen, tLen := len(g), len(t)         // Get slice length.
	helper.HandleLengthError(gLen, tLen) // Handle error if length of lenG != lenT.

	return appendGradeAndText(gLen, g, t)
}
