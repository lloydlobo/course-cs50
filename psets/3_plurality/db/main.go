package main

import (
	"database/sql"
	"fmt"
	"log"
	"math/rand"
	"os"
	"sort"
	"strconv"
	"strings"
	"time"

	"github.com/google/go-cmp/cmp"
	"github.com/google/uuid"
	_ "github.com/mattn/go-sqlite3"
)

type Candidate struct {
	Uuid uuid.UUID
	Id   int
	Name string
	Vote int
}

type Candidates []Candidate

type Voters struct {
	VoteTo      int
	TotalVoters int
}

// Set up a package-level variable called db to hold our database connection pool.
// This variable will be used in several functions.
//
// DB is a database handle representing a pool of zero or more
// underlying connections. It's safe for concurrent use by multiple goroutines.
var (
	db             *sql.DB
	MAX_CANDIDATES = 9
	MAX_VOTERS     = 100
	// c              = make([]Candidate, MAX_CANDIDATES)
	// cPtr           = &c
)

func example() {
	var a = []int{5, 9, 1, 2, 8}
	p := &a
	fmt.Println("Element 0: ", (*p)[0])
	fmt.Println("List of Elements")
	for i := 0; i < len(a); i++ {
		fmt.Print((*p)[i], "  ")
	}
	fmt.Println("\nList of Elements")
	for index, value := range *p {
		fmt.Println(index, ": ", value)
	}
	fmt.Println("Elements of A array")
	ModifyArray(p)
	fmt.Println(a)
}

func ModifyArray(p *[]int) {
	(*p)[2] = 22
}

func GetRandVotes(cPtr *Candidates, collectVotes []int) *Candidates {
	for i := 0; i < MAX_CANDIDATES; i++ {
		for j := 0; j < MAX_VOTERS; j++ {
			if collectVotes[j] == (*cPtr)[i].Id {
				(*cPtr)[i].Vote++
			}
		}
	}
	// fmt.Printf("c: %v\n", cPtr)
	return cPtr
}
func PopulateVotes() (c Candidates) {
	c = make(Candidates, MAX_CANDIDATES)
	collectVotes := []int{}
	for MAX_VOTERS > 0 {
		randVote := RandGenVotes(MAX_CANDIDATES)
		MAX_VOTERS--
		collectVotes = append(collectVotes, randVote)
	}
	sort.Ints(collectVotes)
	cPtr := &c
	for i := 0; i < MAX_CANDIDATES; i++ {
		(*cPtr)[i].Id = i
		(*cPtr)[i].Uuid = uuid.New()
		(*cPtr)[i].Vote = 0
		(*cPtr)[i].Name = NewCandidateName()
	} // fmt.Printf("c: %v\n", cPtr)
	counter := 0
	for i := 0; i < len(*cPtr); i++ {
		for j := 0; j < len(collectVotes); j++ {
			// Increment count for each vote as id matches candidate id.
			if (*cPtr)[i].Id == collectVotes[j] {
				counter++
			}
		}
		// Reset counter when looped over a candidate.
		(*cPtr)[i].Vote = counter
		counter = 0
	}
	return c

}

func RandGenNameLength(MIN, MAX int) (capacity int) {
	capacity = 0 // vote from 0 to 99. candidates/voters
	rand.Seed(time.Now().UnixNano())
	min, max := MIN, MAX
	randOne, randTwo := rand.Intn(max-min+1)+min, rand.Intn(max-min+1)+min
	if randOne <= randTwo {
		randOne, randTwo = randTwo, randOne
	}
	if rand.Int()%2 == 0 {
		capacity = randOne
	} else {
		capacity = randTwo
	}
	return capacity
}

type NameLength struct {
	Min int
	Max int
}

func NewCandidateName() (name string) {
	var (
		b         = []byte{}
		nameRune  []rune
		ru        rune
		nameAscii []int
	)
	n := NameLength{Min: 3, Max: 10}
	count := RandGenNameLength(n.Min, n.Max)
	cacheCount := count
	// TODO: Can also add vowels.
	rand.Seed(time.Now().UnixNano())
	for count > 0 {
		n.Min, n.Max = 65+32, 90+32 // A - Z. 0 -> 26
		randName := RandGenNameLength(n.Min, n.Max)
		// First letter is Uppercase.
		if count == cacheCount {
			randName = randName - 32
		}
		// Populate alternate with vowel.
		if cacheCount-count == 1 && cacheCount-count != 2 && count != cacheCount || count%2 == 0 && count != cacheCount {
			vowel := []rune{'a', 'e', 'i', 'o', 'u'}
			min, max := 0, len(vowel)-1
			randOne, randTwo := rand.Intn(max-min+1)+min, rand.Intn(max-min+1)+min
			if randOne <= randTwo {
				randOne, randTwo = randTwo, randOne
			}
			randName = int(vowel[RandGenNameLength(randTwo, randOne)])
		}
		char := byte(randName)
		b = append(b, char)
		ru = rune(char)
		nameRune = append(nameRune, ru)
		count--
	}
	for range b {
		name = string(b)
		i, err := strconv.Atoi(name) // https://stackoverflow.com/a/27291147
		check(err, "failed to parse string to int : strconv.Atoi(s)")
		nameAscii = append(nameAscii, i)
	}
	return name
}
func check(e error, msg string) error {
	if e != nil {
		return fmt.Errorf("%s : %w", msg, e)
	}
	return nil
}

func main() {
	c := PopulateVotes() // fmt.Printf("c: %v\n", c[4:6])

	// Add candidate name.
	for i := 0; i < cap(c); i++ {
		fmt.Printf("c: %v %s %v %v\n", c[i].Id, c[i].Name, c[i].Vote, c[i].Uuid)
	}
	// example()
	err := runMain(&os.Args)
	if err != nil {
		fmt.Printf("failed to execute runMain() : %v\n", err)
	}
}

// TODO: Add DeleteData function?
func runMain(arg *[]string) error {
	c := Candidate{}
	err := OpenDatabase()
	if err != nil {
		return fmt.Errorf("failed to open database at : "+
			" sql.Open(\"sqlite3\", \"./sqlite-database.db\") : %w\n", err)
	}
	if len(os.Args) > 1 {
		cmd := os.Args[1] // Get cli input.
		if len(os.Args) > 3 {
			vote, err := strconv.Atoi(os.Args[3])
			if err != nil {
				return fmt.Errorf("failed to parse convert string to int : strconve.Atoi(os.Args[3]) : %w", err)
			}
			c.Uuid, c.Name, c.Vote = uuid.New(), strings.TrimSpace(os.Args[2]), vote
			fmt.Printf("os.Args: %v\n", os.Args)
		}
		if cmp.Equal(cmd, "init") {
			err := CreateTable()
			if err != nil {
				return fmt.Errorf("failed to create table at : "+
					" CreateTable() : %w\n", err)
			}
		} else if cmp.Equal(cmd, "list") {
			err := DisplayAllData()
			if err != nil {
				return fmt.Errorf("failed to display data at : "+
					" DisplayAllData() : %w\n", err)
			}
		} else if cmp.Equal(cmd, "new") {
			err := InsertData(c.Uuid, c.Name, c.Vote)
			fmt.Printf("c: %v\n", c)
			if err != nil {
				return fmt.Errorf("failed to insert new data at : "+
					" InsertData(c.Id, c.Name, c.Vote) : %w\n", err)
			}
		}
		// NOTE: RESET global var entry.
		// entry.Id = 0
		c.Vote = 0
		c.Name = ""
		c.Id = 0
	}
	return db.Ping()
}

// OpenDatabase
//
// Open opens a database specified by its database driver name and a driver-specific data source name.
// Ping verifies a connection to the database is still alive, establishing a connection if necessary.
func OpenDatabase() error {
	var err error // Declare err to not redeclare globale var db := .
	db, err = sql.Open("sqlite3", "./sqlite-database.db")
	if err != nil {
		return fmt.Errorf("failed to open database at : "+" sql.Open(\"sqlite3\", \"./sqlite-database.db\") : %w\n", err)
	}
	return db.Ping()
}

func CreateTable() error {
	// "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	createTableSQL := `CREATE TABLE IF NOT EXISTS plurality (
    "id" TEXT NOT NULL PRIMARY KEY,
    "name" TEXT,
    "vote" INTEGER
    );`
	statement, err := db.Prepare(createTableSQL)
	if err != nil {
		return fmt.Errorf("failed to prepare database : db.Prepare() : %w\n", err)
	}
	statement.Exec()
	log.SetFlags(0)
	log.Printf("%v: plurality table created.\n", time.Now().Local())
	return nil
}

func InsertData(id uuid.UUID, name string, vote int) error {
	insertDataSQL := `INSERT INTO plurality(id, name, vote) VALUES (?, ?, ?)`
	fmt.Println(id, name, vote)
	statement, err := db.Prepare(insertDataSQL)
	fmt.Printf("statement: %v\n", statement)
	if err != nil {
		return fmt.Errorf("db.Prepare(insertDataSQL) failed to prepare : %w", err)
	} // TODO: Use Fatalf?
	result, err := statement.Exec(id, name, vote)
	log.Printf("Inserted data successfully.\n"+"%v\n", statement)
	log.Printf("result: %v\n", result)
	return nil
}

func DisplayAllData() error {
	query := "SELECT * FROM plurality ORDER BY id"
	row, err := db.Query(query)
	if err != nil {
		return fmt.Errorf("db.Query(%s) failed to query database; %w", query, err)
	}
	defer row.Close()
	for row.Next() {
		var (
			id   string
			name string
			vote int
		)
		row.Scan(&id, &name, &vote)
		log.SetFlags(0)
		log.Println(id, "[", name, "]", vote)
	}
	return nil
}

func ping() { func() { fmt.Printf("db.Ping(): %v\n", db.Ping()) }() }

// Fuzzy testing :: add dummy votes. for different years.
// Credits: Simple cli app to html app [u/m-O_O reddit:] https://reddit.com
//
// Intn returns, as an int, a non-negative pseudo-random number in the half-open interval [0,n)
// from the default Source. It panics if n <= 0.
func RandGenVotes(MAX int) (vote int) {
	vote = 0 // vote from 0 to 99. candidates/voters
	rand.Seed(time.Now().UnixNano())
	min, max := 0, MAX
	randOne, randTwo := rand.Intn(max-min+1)+min, rand.Intn(max-min+1)+min
	if randOne <= randTwo {
		randOne, randTwo = randTwo, randOne
	}
	if rand.Int()%2 == 0 {
		vote = randOne
	} else {
		vote = randTwo
	}
	return vote
}

// var guess, sum int
// sum = randOne + randTwo
// soup := strconv.Itoa(sum)
// goop := strconv.Itoa(guess)
// if guess == sum {
// 	vote++
// }
// if soup == goop {
// 	vote++
// }

// label
//
// again:
// 	f := float64(rand.Int63()) / (1 << 63)
// 	if f == 1 {
// 		goto again // resample; this branch is taken O(never)
// 	}
