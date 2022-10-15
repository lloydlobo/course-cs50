package main

import (
	"database/sql"
	"fmt"
	"log"
	"os"
	"time"

	"github.com/google/go-cmp/cmp"
	_ "github.com/mattn/go-sqlite3"
)

// Set up a package-level variable called db to hold our database connection pool.
// This variable will be used in several functions.
//
// DB is a database handle representing a pool of zero or more
// underlying connections. It's safe for concurrent use by multiple goroutines.
var db *sql.DB

func main() {
	err := runMain(&os.Args)
	if err != nil {
		fmt.Printf("failed to execute runMain() : %v\n", err)
	}
}

type Candidate struct {
	Id   int
	Name string
	Vote int
}

// TODO: Add name, vote as os.Args.
func runMain(arg *[]string) error {
	c := Candidate{}
	c.Id, c.Name, c.Vote = 1, "Ida", 3
	cmd := os.Args[1]
	err := OpenDatabase()
	if err != nil {
		return fmt.Errorf("failed to open database at : "+
			" sql.Open(\"sqlite3\", \"./sqlite-database.db\") : %w\n", err)
	}
	if len(os.Args) > 1 {
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
			err := InsertData(c.Id, c.Name, c.Vote)
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

/*  Candidates have name and vote count
    typedef struct {
        char *name; // string name;
        int votes;
    } candidate; */

func CreateTable() error {
	createTableSQL := `CREATE TABLE IF NOT EXISTS plurality (
        "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
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

func InsertData(id int, name string, vote int) error {
	insertDataSQL := `INSERT INTO plurality(id, name, vote) VALUES (?, ?, ?)`
	statement, err := db.Prepare(insertDataSQL)
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
			id   int
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
