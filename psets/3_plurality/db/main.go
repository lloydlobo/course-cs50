package main

import (
	"database/sql"
	"fmt"
	"log"
	"os"
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

// Set up a package-level variable called db to hold our database connection pool.
// This variable will be used in several functions.
//
// DB is a database handle representing a pool of zero or more
// underlying connections. It's safe for concurrent use by multiple goroutines.
var (
	db *sql.DB
)

func main() {
	err := runMain(&os.Args)
	if err != nil {
		fmt.Printf("failed to execute runMain() : %v\n", err)
	}
}

// TODO: Add name, vote as os.Args.
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
