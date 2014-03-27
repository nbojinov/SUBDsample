package main

import (
	"appengine"
	"html/template"
	"net/http"
)

type Image struct{
	UrlImage []string  
}


func init(){
	http.HandleFunc("/uploadForm",uploadForm)
	http.HandleFunc("/upload",upload)
	http.HandleFunc("/getPuzzle",handleGetUploadedImages)
	http.HandleFunc("/login",handleLogin)
	http.HandleFunc("/signUp",handleSignUp)
	http.HandleFunc("/updateScore",handleUpdateHighscore)
}

const uploadTemplate = "<html><body><form action='{{.}}' method='POST' enctype='multipart/form-data'>Upload File: <input type='file' name='file'><br><input type='submit' name='submit' value='Submit'></form></body></html>";
func uploadForm(rw http.ResponseWriter, r *http.Request){
	uploadUrl := UploadImageUrl(rw,	r)	

	template.Must(template.New("upload").Parse(uploadTemplate)).Execute(rw,uploadUrl)
}

func upload(rw http.ResponseWriter, r *http.Request){
	UploadImage(rw,r)
	http.Redirect(rw,r,"/uploadForm",http.StatusFound)
}

func handleGetUploadedImages(rw http.ResponseWriter,r *http.Request){
	image := GetAllUploadedImages(rw,r)
	returnPuzzle(image,rw)
}

func handleLogin(rw http.ResponseWriter, r *http.Request){
	
}

func handleSignUp(rw http.ResponseWriter,r *http.Request){
	context := appengine.NewContext(r)
	username := r.FormValue("username")
	if r.FormValue("pass") == r.FormValue("repeat_pass"){
		pass := r.FormValue("pass")

		if err := AddUser(context,username,pass); err != nil{
			http.Error(rw,err.Error(),http.StatusInternalServerError)
		}

	} else {
		http.Error(rw,"Passwords don't match",http.StatusInternalServerError)
	}
	http.Redirect(rw,r,"/PuzzleGame.html",http.StatusFound)
}

func handleUpdateHighscore(rw http.ResponseWriter, r *http.Request){
	
}
