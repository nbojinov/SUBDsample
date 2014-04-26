package main

import(
	"database/sql"
	"fmt"
	"time"
)

import _ "github.com/go-sql-driver/mysql"


type Table1 struct {
	id int
	url string
	content_id int
}

type Table2 struct {
	id int
	date time.Time
	name string  
	user_id int
}


func main(){
	database,err := sql.Open("mysql","root:@/Practice?parseTime=true")

	if err != nil{
		fmt.Printf("Database not created")
	}

	res, errx := database.Query("select COUNT(*) from Article")
	

	if errx != nil{
		fmt.Println("Error:",errx.Error())
		return 
	}

	var count int
	res.Next()
	if err := res.Scan(&count); err !=nil{
		fmt.Println("Error:",err.Error())
		return 
	}


	articles := make([]Table1,count,count)
	contents := make([]Table2,count,count)
	
	stmtDel,errdel := database.Prepare("drop table Article")
	
	if errdel != nil{
		fmt.Println("Error:",errdel.Error())
		return 
	}
	

	stmtCreateArticle := "create table Article_part1 (id int not null auto_increment primary key,url varchar(32),part2_id int not null)"
	
	stmtCreateContent := "create table Article_part2 (id int not null auto_increment primary key,created_on date,name varchar(64),category_id int not null)"


	stmtInsertArticle := "insert into Article_part1 values(?,?,?)"
	stmtInsertContent := "insert into Article_part2 values(?,?,?,?)"

	rows, errq := database.Query("select * from Article")
	if errq != nil{
		fmt.Println("Error:",errq.Error())
		return 
	}

	for i:= 0; rows.Next(); i++ {
			if err := rows.Scan(&articles[i].id,&contents[i].date,&contents[i].name,&articles[i].url,&contents[i].user_id); err != nil{
				fmt.Println("Error:",err.Error())
				return 
			}
			
			articles[i].content_id = i + 1

				
			contents[i].id = i + 1

	}	

	if _,err := database.Exec(stmtCreateArticle); err != nil{
		fmt.Println("Error:",err.Error())
		return 
	}

	if _,err := database.Exec(stmtCreateContent); err != nil{
		fmt.Println("Error:",err.Error())
		return 
	}

	
	for _,article_title := range articles{
		if _, err := database.Exec(stmtInsertArticle,article_title.id,article_title.url,article_title.content_id); err != nil{
			fmt.Println("Error:",err.Error())
			return 
		}
	}

	for _,article_content := range contents{
		if _, err := database.Exec(stmtInsertContent,article_content.id,article_content.date, article_content.name, article_content.user_id); err != nil{
			fmt.Println("Error:",err.Error())
			return 
		}
	}	

	if _,err := stmtDel.Exec(); err != nil{
			fmt.Println("Error:",err.Error())
			return 
	}

}
