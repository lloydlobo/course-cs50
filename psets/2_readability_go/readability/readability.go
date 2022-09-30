package readability

import (
	"fmt"
	"strconv"
	"strings"
)

type ColemanLiau struct {
	Text string
}

// Execute()
//
// Example:
// Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
// Grade 3
func Execute(s string) (output string) {
	str := strings.ToLower(s)
	cli := ColemanLiau{}
	lettC, wordC, sentenC := make(chan int), make(chan int), make(chan int)

	go func() { sentenC <- cli.LenSentence(str) }()
	go func() { lettC <- cli.LenLetters(str) }()
	go func() { wordC <- cli.LenWords(str) }()

	// if [i]byte == 32, it's a space.
	// cli.SpaceCount(s)
	nw := <-wordC
	nl := <-lettC
	ns := <-sentenC

	fmt.Println(nw, nl, ns)

	grade := int64(cli.GetGrade(float64(nl), float64(ns), float64(nw)))

	output = fmt.Sprintf("\nText: %s\nGrade %2s\n",
		s, strconv.FormatInt(grade, 10),
	)
	return output
}

func (cl ColemanLiau) LenWords(s string) int {
	cl.Text = s
	word := strings.Split(cl.Text, " ")

	return len(word)
}

func (cl ColemanLiau) LenLetters(s string) int {
	cl.Text = s       // receiver.Text
	bytes := []byte{} // cache bytes that are letters.

	for i := 0; i < len(s); i++ {
		b := byte(cl.Text[i])
		if b > 64+32 && b < 91+32 {
			bytes = append(bytes, b)
		}
	}

	return len(bytes)
}

func (cl ColemanLiau) LenSentence(s string) int {
	bytes := []byte{}
	cl.Text = s

	t := &cl.Text
	n := len(*t)

	for i := 0; i < n; i++ {
		b := byte((*t)[i])

		if b == byte('.') {
			bytes = append(bytes, b)
		}
	}

	return len(bytes)
}

func (cl ColemanLiau) TotalLen(s string) int {
	cl.Text = s // receiver.Text
	return len(cl.Text)
}

func (cli ColemanLiau) GetGrade(l, s, w float64) float64 {
	avgLetters, avgSentence := 100*l/w, 100*s/w
	return 0.0588*avgLetters - 0.296*avgSentence - 15.8
}

/*
 GetIndexCLIPer100W()
 (because 0.0588 * 464.29 - 0.296 * 28.57 - 15.8 = 3):

 Run()
 Congratulations! Today is your day. You're off to Great Places! You're off and away!

	64 letters per 14 words = avg(464.29 Letters / 100 words). (because 65 / 14 * 100 = 464.29).
	4 sentences per 14 words = avg(28.57 Sentences / 100 words). (because 4 / 14 * 100 = 28.57).
*/
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
func GetGradesInt() []int {
	var g []int

	G_1, G_2, G_3, G_5, G_7, G_8_0, G_8_1, G_9, G_10, G_16_PLUS :=
		-9, 2, 3, 5, 7, 8, 8, 9, 10, 16
	g = append(g,
		G_1, G_2, G_3, G_5, G_7, G_8_0, G_8_1, G_9, G_10, G_16_PLUS,
	)

	return g
}

// getText() returns slice array of text.
func GetTextStr() []string {
	var (
		t         []string
		G_1       = "One fish. Two fish. Red fish. Blue fish." // Grade 1.
		G_2       = "Would you like them here or there? I would not like them here or there. I would not like them anywhere."
		G_3       = "Congratulations! Today is your day. You're off to Great Places! You're off and away!"
		G_5       = "Harry Potter was a highly unusual boy in many ways. For one thing, he hated the summer holidays more than any other time of year. For another, he really wanted to do his homework, but was forced to do it in secret, in the dead of the night. And he also happened to be a wizard."
		G_7       = "In my younger and more vulnerable years my father gave me some advice that I've been turning over in my mind ever since."
		G_8_0     = "Alice was beginning to get very tired of sitting by her sister on the bank, and of having nothing to do: once or twice she had peeped into the book her sister was reading, but it had no pictures or conversations in it, \"and what is the use of a book,\" thought Alice \"without pictures or conversation?\" "
		G_8_1     = "When he was nearly thirteen, my brother Jem got his arm badly broken at the elbow. When it healed, and Jem's fears of never being able to play football were assuaged, he was seldom self-conscious about his injury. His left arm was somewhat shorter than his right; when he stood or walked, the back of his hand was at right angles to his body, his thumb parallel to his thigh."
		G_9       = "There are more things in Heaven and Earth, Horatio, than are dreamt of in your philosophy."
		G_10      = "It was a bright cold day in April, and the clocks were striking thirteen. Winston Smith, his chin nuzzled into his breast in an effort to escape the vile wind, slipped quickly through the glass doors of Victory Mansions, though not quickly enough to prevent a swirl of gritty dust from entering along with him."
		G_16_PLUS = "A large class of computational problems involve the determination of properties of graphs, digraphs, integers, arrays of integers, finite families of finite sets, boolean formulas and elements of other countable domains."
	)
	t = append(t, G_1, G_2, G_3, G_5, G_7, G_8_0, G_8_1, G_9, G_10, G_16_PLUS)

	return t
}

// type CLI struct {
// 	GAT testcases.GradeAndText
// }

// func Execute(s testcases.GradeAndText) int {
// 	cli := CLI{}
// 	cli.GAT = s

// 	out := CLI.LettersLen(cli)
// 	// fmt.Printf("%v\n", cli.GAT.Text)
// 	return out
// }

// func (s CLI) LettersLen() int {
// 	n := len(s.GAT.Text)
// 	fmt.Printf("n: %v\n", n)
// 	return 0
// }
