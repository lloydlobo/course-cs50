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

// DB is a database handle representing a pool of zero or more
// underlying connections. It's safe for concurrent use by multiple goroutines.

var (
	db             *sql.DB // Set up a package-level variable called db to hold our database connection pool.
	MAX_CANDIDATES = 9
	MAX_VOTERS     = 100
	VOWEL          = []rune{'a', 'e', 'i', 'o', 'u'}
)

type Candidate struct {
	Uuid uuid.UUID
	Id   int
	Name string
	Vote int
}

type Candidates []Candidate

func main() {
	c := PopulateVotes() // fmt.Printf("c: %v\n", c[4:6])

	for i := 0; i < cap(c); i++ {
		// fmt.Printf("c: %v %s %v %v\n", c[i].Id, c[i].Name, c[i].Vote, c[i].Uuid)
		err := runMain(&os.Args, c[i])
		if err != nil {
			fmt.Printf("failed to execute runMain() : %v\n", err)
		}
	}
}

// TODO: Add DeleteData function?
func runMain(arg *[]string, ca Candidate) error {
	var (
		vote    int
		voteErr error
	)
	c := Candidate{}
	c = ca // TODO: Fix automatic copy of pre-made list.
	err := OpenDatabase()
	if err != nil {
		return fmt.Errorf("failed to open database at : "+
			" sql.Open(\"sqlite3\", \"./sqlite-database.db\") : %w\n", err)
	}
	if len(os.Args) > 1 {
		cmd := os.Args[1] // Get cli input.
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
			if len(os.Args) > 3 {
				vote, voteErr = strconv.Atoi(os.Args[3])
				if voteErr != nil {
					return fmt.Errorf("failed to parse convert string to int : strconve.Atoi(os.Args[3]) : %w", voteErr)
				}
			}
			err := InsertData(c.Uuid, os.Args[2], c.Vote)
			c.Uuid, c.Name, c.Vote = uuid.New(), strings.TrimSpace(os.Args[2]), vote
			fmt.Printf("os.Args: %v\n", os.Args)
			if err != nil {
				return fmt.Errorf("failed to insert new data at : "+
					" InsertData(c.Id, c.Name, c.Vote) : %w\n", err)
			}
			// NOTE: RESET global var entry.
			c.Vote = 0
			c.Name = ""
			c.Id = 0
		} else if cmp.Equal(cmd, "random") {
			err := InsertData(c.Uuid, c.Name, c.Vote)
			if err != nil {
				return fmt.Errorf("failed to insert new data at : "+
					" InsertData(c.Id, c.Name, c.Vote) : %w\n", err)
			}
		}
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

func CreateTable() error { // "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
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
	statement, err := db.Prepare(insertDataSQL)
	if err != nil {
		return fmt.Errorf("db.Prepare(insertDataSQL) failed to prepare : %w", err)
	} // TODO: Use Fatalf?
	_, err = statement.Exec(id, name, vote)
	log.Printf("Inserted data successfully.\n"+"%v\n", statement)
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

func GetRandVotes(cPtr *Candidates, collectVotes []int) *Candidates {
	for i := 0; i < MAX_CANDIDATES; i++ {
		for j := 0; j < MAX_VOTERS; j++ {
			if collectVotes[j] == (*cPtr)[i].Id {
				(*cPtr)[i].Vote++
			}
		}
	} // fmt.Printf("c: %v\n", cPtr)
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
		(*cPtr)[i].Id, (*cPtr)[i].Uuid = i, uuid.New()
		(*cPtr)[i].Vote, (*cPtr)[i].Name = 0, NewCandidateName()
	}
	counter := 0
	for i := 0; i < len(*cPtr); i++ {
		for j := 0; j < len(collectVotes); j++ {
			// Increment count for each vote as id matches candidate id.
			if (*cPtr)[i].Id == collectVotes[j] {
				counter++
			}
		}
		(*cPtr)[i].Vote = counter
		// Reset counter when looped over a candidate.
		counter = 0
	}
	return c

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
	rand.Seed(time.Now().UnixNano())
	for count > 0 {
		n.Min, n.Max = 65+32, 90+32 // A - Z. 0 -> 26
		randName := RandGenNameLength(n.Min, n.Max)
		// First letter is Uppercase.
		if count == cacheCount {
			randName = randName - 32
		}
		// Populate alternate with vowel.
		IsSecondChar := cacheCount-count == 1 && cacheCount-count != 2 && count != cacheCount
		isEvenChar := count%2 == 0
		isFirstChar := count == cacheCount
		if IsSecondChar || isEvenChar && !isFirstChar {
			min, max := 0, len(VOWEL)-1
			randOne, randTwo := rand.Intn(max-min+1)+min, rand.Intn(max-min+1)+min
			if randOne <= randTwo {
				randOne, randTwo = randTwo, randOne
			}
			randName = int(VOWEL[RandGenNameLength(randTwo, randOne)])
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

func ping() { func() { fmt.Printf("db.Ping(): %v\n", db.Ping()) }() }

func check(e error, msg string) error {
	if e != nil {
		return fmt.Errorf("%s : %w", msg, e)
	}
	return nil
}

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
