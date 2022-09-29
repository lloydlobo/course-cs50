package testcases

// getGradesArray() returns slice array of grade.
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

/*
# EXAMPLE GRADED TEXTS

	"Would you like them here or there? I would not like them here or there. I would not like them anywhere. (Grade 2)"
	"Congratulations! Today is your day. You're off to Great Places! You're off and away! (Grade 3)"
	"Harry Potter was a highly unusual boy in many ways. For one thing, he hated the summer holidays more than any other time of year. For another, he really wanted to do his homework, but was forced to do it in secret, in the dead of the night. And he also happened to be a wizard. (Grade 5)
	"In my younger and more vulnerable years my father gave me some advice that I've been turning over in my mind ever since. (Grade 7)
	"Alice was beginning to get very tired of sitting by her sister on the bank, and of having nothing to do: once or twice she had peeped into the book her sister was reading, but it had no pictures or conversations in it, "and what is the use of a book," thought Alice "without pictures or conversation?" (Grade 8)
	"When he was nearly thirteen, my brother Jem got his arm badly broken at the elbow. When it healed, and Jem's fears of never being able to play football were assuaged, he was seldom self-conscious about his injury. His left arm was somewhat shorter than his right; when he stood or walked, the back of his hand was at right angles to his body, his thumb parallel to his thigh. (Grade 8)
	"There are more things in Heaven and Earth, Horatio, than are dreamt of in your philosophy. (Grade 9)
	"It was a bright cold day in April, and the clocks were striking thirteen. Winston Smith, his chin nuzzled into his breast in an effort to escape the vile wind, slipped quickly through the glass doors of Victory Mansions, though not quickly enough to prevent a swirl of gritty dust from entering along with him. (Grade 10)
	"A large class of computational problems involve the determination of properties of graphs, digraphs, integers, arrays of integers, finite families of finite sets, boolean formulas and elements of other countable domains. (Grade 16+)
*/
