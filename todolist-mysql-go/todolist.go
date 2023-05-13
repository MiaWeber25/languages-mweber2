// Golang Demo - Todo Application
// Tutorial by: https://betterprogramming.pub/build-a-simple-todolist-app-in-golang-82297ec25c7d
// Completed by: Mia Weber 05/08/2023
package main

import ( // Import packages
	"io"
	"net/http"

	"encoding/json"

	"strconv" // Convert string to int before db queries
	// Don't intend to use the variable -> _ " "
	_ "github.com/go-sql-driver/mysql"        // Backend Database
	"github.com/gorilla/mux"                  // Request router
	"github.com/jinzhu/gorm"                  // ORM to interact with db
	_ "github.com/jinzhu/gorm/dialects/mysql" // Backend Database
	"github.com/rs/cors"                      // Cross-origin resource sharing
	log "github.com/sirupsen/logrus"          // Logging
)

// Initialize database connection with GORM
var db, _ = gorm.Open("mysql", "root:root@/todolist?charset=utf8&parseTime=True&loc=Local")

// Struct TodoItem that contains all of the attributes of a task (id#, desc, status)
type TodoItemModel struct {
	Id          int `gorm:"primary_key"`
	Description string
	Completed   bool
}

// Ensure that the API is up and running. responds "alive":true to the client when invoked
func Healthz(w http.ResponseWriter, r *http.Request) {
	log.Info("API Health is OK")
	w.Header().Set("Access-Control-Allow-Origin", "*") // THIS WAS THE FIX -> router needs to listen correctly to set item.id (CORS)
	w.Header().Set("Content-Type", "application/json")
	io.WriteString(w, `{"alive": true}`)
}

// Set up logger settings
// In Go, init() is run exactly once, when the program first begins
func init() {
	log.SetFormatter(&log.TextFormatter{})
	log.SetReportCaller(true)
}

// Creates a new item when the user clicks the "plus" button
func CreateItem(w http.ResponseWriter, r *http.Request) {
	description := r.FormValue("description") // Get value from POST operation
	// Create todo object, add to db, and query db to ensure add was successful
	log.WithFields(log.Fields{"description": description}).Info("Add new TodoItem. Saving to database.")
	todo := &TodoItemModel{Description: description, Completed: false}
	db.Create(&todo)
	result := db.Last(&todo)
	w.Header().Set("Access-Control-Allow-Origin", "*")
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(result.Value)

}

// Updates the state of the task from Incomplete to Complete
func UpdateItem(w http.ResponseWriter, r *http.Request) {
	// Get URL parameter from mux
	vars := mux.Vars(r)
	id, _ := strconv.Atoi(vars["id"])

	// Test if the TodoItem exist in DB
	err := GetItemByID(id)
	if err == false {
		w.Header().Set("Access-Control-Allow-Origin", "*")
		w.Header().Set("Content-Type", "application/json")
		io.WriteString(w, `{"updated": false, "error": "Record Not Found"}`)
	} else {
		completed, _ := strconv.ParseBool(r.FormValue("completed"))
		log.WithFields(log.Fields{"Id": id, "Completed": completed}).Info("Updating TodoItem")
		todo := &TodoItemModel{}
		db.First(&todo, id)
		todo.Completed = completed
		db.Save(&todo)
		w.Header().Set("Access-Control-Allow-Origin", "*")
		w.Header().Set("Content-Type", "application/json")
		io.WriteString(w, `{"updated": true}`)
	}
}

// Deletes the item when the user clicks the trash can icon
func DeleteItem(w http.ResponseWriter, r *http.Request) {
	// Get URL parameter from mux
	vars := mux.Vars(r)
	id, _ := strconv.Atoi(vars["id"])
	log.WithFields(log.Fields{"Id": id}).Info("IN FUNCTION")

	// Test if the TodoItem exist in DB
	err := GetItemByID(id)
	if err == false {
		log.WithFields(log.Fields{"Id": id}).Info("Could Not Find Record")
		w.Header().Set("Access-Control-Allow-Origin", "*")
		w.Header().Set("Content-Type", "application/json")
		io.WriteString(w, `{"deleted": false, "error": "Record Not Found"}`)
	} else {
		log.WithFields(log.Fields{"Id": id}).Info("Deleting TodoItem")
		todo := &TodoItemModel{}
		db.First(&todo, id)
		db.Delete(&todo)
		w.Header().Set("Access-Control-Allow-Origin", "*")
		w.Header().Set("Content-Type", "application/json")
		io.WriteString(w, `{"deleted": true}`)
	}
}

// Get the ID of the task -> query database to ensure that task is present
func GetItemByID(Id int) bool {
	todo := &TodoItemModel{}
	result := db.First(&todo, Id)
	if result.Error != nil {
		log.Warn("TodoItem not found in database")
		return false
	}
	return true
}

// Get all the completed items for the database
func GetCompletedItems(w http.ResponseWriter, r *http.Request) {
	log.Info("Get completed TodoItems")
	completedTodoItems := GetTodoItems(true)
	w.Header().Set("Access-Control-Allow-Origin", "*")
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(completedTodoItems)
}

// Get all the incomplete items for the databse
func GetIncompleteItems(w http.ResponseWriter, r *http.Request) {
	log.Info("Get Incomplete TodoItems")
	IncompleteTodoItems := GetTodoItems(false)
	w.Header().Set("Access-Control-Allow-Origin", "*")
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(IncompleteTodoItems)
}

// Get all of the tasks
func GetTodoItems(completed bool) interface{} {
	var todos []TodoItemModel
	TodoItems := db.Where("completed = ?", completed).Find(&todos).Value
	return TodoItems
}

// Set up the router
func main() {
	defer db.Close() // Close database connection when main() returns

	// Running automigration against MySQL db directly after starting API server
	db.Debug().DropTableIfExists(&TodoItemModel{})
	db.Debug().AutoMigrate(&TodoItemModel{})

	log.Info("Starting Todolist API server")
	router := mux.NewRouter()
	router.HandleFunc("/healthz", Healthz).Methods("GET")
	router.HandleFunc("/todo-completed", GetCompletedItems).Methods("GET")
	router.HandleFunc("/todo-incomplete", GetIncompleteItems).Methods("GET")
	router.HandleFunc("/todo", CreateItem).Methods("POST")
	router.HandleFunc("/todo/{id}", UpdateItem).Methods("POST")
	router.HandleFunc("/todo/{id}", DeleteItem).Methods("DELETE")

	handler := cors.New(cors.Options{
		AllowedMethods: []string{"GET", "POST", "DELETE", "PATCH", "OPTIONS"},
	}).Handler(router)

	http.ListenAndServe(":8000", handler)
	// OTHER ISSUE: only one listenandserve. HAd one above for the server that was blocking the "DELETE" listen
}
