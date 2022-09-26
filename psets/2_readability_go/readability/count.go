package readability

type Count struct {
	Lines     int
	Words     int
	Sentences int
}

func (C *Count) CountLines(s string) int {
	// return C.Lines

	return len(s)
}
func (C *Count) CountWords(s string) int {
	// return C.Words

	return len(s)
}
func (C *Count) CountSentences(s string) int {
	// return C.Sentences

	return len(s)
}

/*
    type rect struct {
    	width, height int
    }

   func (r *rect) area() int {
   	return r.width * r.height
   }

   func (r rect) perim() int {
   	return 2*r.width + 2*r.height
   }

   func rectmain() {
   	r := rect{width: 10, height: 5}

   	fmt.Println("area: ", r.area())
   	fmt.Println("perim:", r.perim())

   	rp := &r
   	fmt.Println("area: ", rp.area())
   	fmt.Println("perim:", rp.perim())
   }
*/
