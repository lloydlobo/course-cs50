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
	"math"
	"strconv"
	"strings"
	"sync"
)

// PERF: erase this struct if not needed.
type ColemanLiau struct {
	Text string
}

// Methods.
type LenWSL interface {
	LenWords() int
	LenSentence() int
	LenLetters() int
}

// Methods.
type AverageLenCalculator interface {
	FindAverageLetters() float64
	FindAverageSentences() float64
}

// Methods.
type CLICalculator interface {
	CalculateGrade() float64
}

type Input struct {
	text  *string
	grade *int
}

type InputCount struct {
	Words     int
	Sentences int
	Letters   int
}

type InputCountAverage struct {
	letters   float64
	sentences float64
}

func ProcessGrade(s string) string {
	msg := "\nText: %s\nGrade %2s\n"

	g := GetGrade(s)

	grade := math.Round(*g)

	if grade <= 1 {
		return fmt.Sprintf(msg, s, "Before 1")
	} else if grade > 15 {
		return fmt.Sprintf(msg, s, "16+")
	}

	return fmt.Sprintf(msg, s, strconv.FormatInt(int64(grade), 10))
}

// GetGrade()
func GetGrade(txt string) *float64 {
	var (
		wsl   LenWSL
		avg   AverageLenCalculator
		grade CLICalculator
		g     = 0
		wg    sync.WaitGroup
	)
	// If a WaitGroup is reused to wait for several independent sets of events,
	// new Add calls must happen after all previous Wait calls have returned\.
	wsl = Input{&txt, &g}
	wg.Add(3)
	lenW, lenS, lenL := Length(wsl, &wg)

	avg = InputCount{lenW, lenS, lenL}
	wg.Add(2)
	avgS, avgL := AverageLength(avg, &wg)

	grade = InputCountAverage{avgS, avgL}
	out := grade.CalculateGrade()
	// PERF: No need of pointers here,
	// unless storing something.
	return &out
}

/*
// A WaitGroup waits for a collection of goroutines to finish\.
The main goroutine calls Add to set the number of goroutines to wait for\. Then each of the goroutines
runs and calls Done when finished\. At the same time, Wait can be used to block until all goroutines have finished\.
A WaitGroup must not be copied after first use\. In the terminology of the Go memory model, a call to Done
“synchronizes before” the return of any Wait call that it unblocks\. */
// Note: if a WaitGroup is explicitly passed into functions, it should be done by pointer.
func AverageLength(avg AverageLenCalculator, wg *sync.WaitGroup) (float64, float64) {
	cs, cl := make(chan float64), make(chan float64)

	go func() { defer wg.Done(); cs <- avg.FindAverageSentences() }()
	go func() { defer wg.Done(); cl <- avg.FindAverageLetters() }()

	s, l := <-cs, <-cl
	wg.Wait() // Wait till current wg counter = 0.
	return s, l
}

func Length(wsl LenWSL, wg *sync.WaitGroup) (int, int, int) {
	chanW, chanL, chanS := make(chan int), make(chan int), make(chan int)

	go func() { defer wg.Done(); chanW <- wsl.LenWords() }()
	go func() { defer wg.Done(); chanS <- wsl.LenSentence() }()
	go func() { defer wg.Done(); chanL <- wsl.LenLetters() }()

	w, s, l := <-chanW, <-chanL, <-chanS
	wg.Wait() // Wait till current wg counter = 0.
	return w, s, l
}

func (c InputCountAverage) CalculateGrade() float64 {
	return 0.0588*c.letters - 0.296*c.sentences - 15.8
}

func (c InputCount) FindAverageLetters() float64 {
	out := 100 * float64(c.Letters) / float64(c.Words)
	// log.Printf("out: %v\n", out)
	return out
}

func (c InputCount) FindAverageSentences() float64 {
	out := 100 * float64(c.Sentences) / float64(c.Words)
	// log.Printf("out: %v\n", out)
	return out
}

func (in Input) LenLetters() (out int) {
	t := &in.text
	count := 0

	for i := 0; i < len(**t); i++ {
		b := (**t)[i]

		if IsALetter(&b) {
			count++
		}
	}
	return count
}

func IsALetter(b *byte) bool { return *b > 64+32 && *b < 91+32 }

func (i Input) LenSentence() int {
	out := len(strings.Split(*i.text, ". "))
	// fmt.Printf("out: %v\n", out)
	return out
}

func (i Input) LenWords() int {
	out := len(strings.Split(*i.text, " "))
	// fmt.Printf("out: %v\n", out)
	return out
}

func sum(s []int, c chan int) {
	sum := 0
	for _, v := range s {
		sum += v
	}
	c <- sum // send sum to c
}

func Run() {
	s := []int{7, 2, 8, -9, 4, 0}

	c := make(chan int)
	go sum(s[:len(s)/2], c)
	go sum(s[len(s)/2:], c)
	x, y := <-c, <-c // receive from c

	fmt.Println(x, y, x+y)
}

// ////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////

// Execute()
func Execute(s string) (out string) {
	str := strings.ToLower(s)
	cli := ColemanLiau{}
	lettC, wordC, sentenC := make(chan int), make(chan int), make(chan int)

	go func() { sentenC <- cli.LenSentence(str) }()
	go func() { lettC <- cli.LenLetters(str) }()
	go func() { wordC <- cli.LenWords(str) }()

	nw := <-wordC
	nl := <-lettC
	ns := <-sentenC

	avgS, avgL := cli.AverageSL100W(nw, ns, nl)
	grade := int64(cli.GetGrade(avgS, avgL))

	if grade <= 1 {
		out = fmt.Sprintf("\nText: %s\nGrade %2s\n", s, "Before 1")
	} else if grade > 15 {
		out = fmt.Sprintf("\nText: %s\nGrade %2s\n", s, "16+")
	} else {
		out = fmt.Sprintf("\nText: %s\nGrade %2s\n",
			s, strconv.FormatInt(grade, 10))
	}
	// fmt.Printf("got: %v\n\n", grade)
	return out
}

// `CLI` = 0.0588 * `L` - 0.296 * `S` - 15.8
// `L` is the average number of letters per 100 words.
// `S` is the average number of sentences per 100 words.
func (cli ColemanLiau) GetGrade(s, l float64) float64 {
	grade := 0.0588*l - 0.296*s - 15.8
	return math.Round(grade)
}

func (cl ColemanLiau) AverageSL100W(w, s, l int) (sentenceAvg float64, letterAvg float64) {
	fw, fs, fl := float64(w), float64(s), float64(l)
	sentenceAvg, letterAvg = 100*fs/fw, 100*fl/fw
	return sentenceAvg, letterAvg
}

func (cl ColemanLiau) LenWords(s string) int {
	cl.Text = s
	word := strings.Split(cl.Text, " ")
	return len(word)
}

// LenSentence()
// if [i]byte == 32, it's a space. cli.SpaceCount(s)
//
//		Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
//		Grade 3
//	 w:14, s:1, l:65
//
// fmt.Printf("s: %v\n", s) mb := make(map[int]byte) ms := make(map[int]string)
//
// G_8_0     =
//
//	Alice was beginning to get very tired of sitting by her sister on the bank,
//	and of having nothing to do: once or twice she had peeped into the book her sister was reading,
//	but it had no pictures or conversations in it, \"and what is the use of a book,\"
//	thought Alice \"without pictures or conversation?\"
func (cl ColemanLiau) LenSentence(s string) int {
	cl.Text = s
	var (
		bytes = []byte{}
		t     = &cl.Text
		n     = len(*t)
	)

	for i := 0; i < n; i++ {
		var isPrevCharEnd bool
		// debugByteString(bCurr, bNext, i, mb, ms)
		bCurr := byte((*t)[i])
		bNext := byte((*t)[(i+1)%n])

		// Fallback: Example: ...thought Alice "without pictures or conversation?"
		if i == n-2 {
			isPrevCharEnd = (*t)[i-1] == '?' || (*t)[i-1] == '!' || (*t)[i-1] == '.'
		}
		if bCurr == byte('"') && isPrevCharEnd {
			bytes = append(bytes, bCurr)
		}

		if bCurr == byte('.') && bNext == byte(' ') {
			bytes = append(bytes, bCurr)
		} else if bCurr == byte('.') && i == n-1 {
			bytes = append(bytes, bCurr)
		}

		if bCurr == byte('?') || bCurr == byte('!') {
			if bNext == byte(' ') {
				bytes = append(bytes, bCurr)
			} else if bCurr == byte('!') || bCurr == byte('!') && i == n-1 {
				bytes = append(bytes, bCurr)
			}
		}
	}
	out := len(bytes)
	if out == 0 {
		out++
	}
	return out
}

// ms[i], ms[i+1], mb[i], mb[i+1] = string(bCurr), string(bNext), bCurr, byte(bNext)
func debugByteString(a, b byte, i int, mb map[int](byte), ms map[int]string) {
	mb[i], mb[i+1] = a, byte(b)
	ms[i], ms[i+1] = string(a), string(b)
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

func (cl ColemanLiau) TotalLen(s string) int {
	cl.Text = s // receiver.Text
	return len(cl.Text)
}

/*
GetIndexCLIPer100W()
(because 0.0588 * 464.29 - 0.296 * 28.57 - 15.8 = 3):
Run()
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

// Example:
//
//	Text: Harry Potter was a highly unusual boy in many ways. For one thing, he hated the summer holidays more than any other time of year.
//	For another, he really wanted to do his homework, but was forced to do it in secret, in the dead of the night. And he also happened to be a wizard.
//	Grade 5
//
// This text has 214 letters, 4 sentences, and 56 words. That comes out to about
// 382.14 letters per 100 words, and 7.14 sentences per 100 words.
//
// Example:
//
//	Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
//	Grade 3
//
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
