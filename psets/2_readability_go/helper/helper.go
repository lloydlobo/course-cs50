package helper

import (
	"errors"
	"log"
	"math"
)

// HandleLengthError handles error if length of lenG != lenT.
//
// The anonymous function returns:
// - error, if the length condition inside the scope is false.
// - nil, if length matches.
func HandleLengthError(gradeLen, textLen int) {
	if err := func() error {
		if gradeLen != textLen { // https://go.dev/blog/error-handling-and-go
			return errors.New("len(): length of grades & texts is not the same.")
		}
		return nil
	}(); err != nil {
		log.Fatalf("GetTextAndGrade(): %s", err)
	}
}

// RoundFloat rounds a floating-point number to the set `precision`.
//
// https://gosamples.dev/round-float/
//
//		To round a floating-point number in Go, you can use the math.Round()
//		function from the built-in math package. However, this function rounds
//		to the nearest integer, so it cannot be used directly to round a float
//		to a particular precision. But you can use it to create your own -
//		function that rounds to any decimal places.
//
//		- multiply the number to be rounded times 10 to the power of X,
//	      where X is the precision you want to achieve
//		- round this raised number to the nearest integer value using
//		  the math.Round() function
//		- divide the rounded number by 10 to the power of X,
//		  where X is the rounding decimal precision
//
//		In this way, by rounding the raised number to the nearest integer,
//		and then dividing, we get a number rounded to the specified decimal places.
func RoundFloat(f float64, precision int) float64 {
	ratio := math.Pow(10, float64(precision))

	return math.Round(f*ratio) / ratio
}
