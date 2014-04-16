package main

import (
	"appengine"
	"net/http"
	"strings"
)

type Image struct{
	UrlImage []string  
}


func init(){
	http.HandleFunc("/upload",upload)
	http.HandleFunc("/getPuzzle",handleGetUploadedImages)
	http.HandleFunc("/login",handleLogin)
	http.HandleFunc("/updateScore",handleUpdateHighscore)
	http.HandleFunc("/saveGame",handleSaveGame)
	http.HandleFunc("/getSaveGame",handleGetSaveGame)
	http.HandleFunc("/deleteGame",handleDeleteGame)
	http.HandleFunc("/logout",handleLogout)
	http.HandleFunc("/saveGames",handleSaveGames)
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
	UserGoogleLogin(rw,r)
}



func handleUpdateHighscore(rw http.ResponseWriter, r *http.Request){
	context := appengine.NewContext(r)
	if err := UpdateHighscores(context,r); err != nil{
		http.Error(rw,err.Error(),http.StatusInternalServerError)
	}
}

func handleSaveGame(rw http.ResponseWriter, r *http.Request){
	context := appengine.NewContext(r)
	if err := UploadGameSave(context,r); err != nil{
		http.Error(rw,err.Error(),http.StatusInternalServerError)
	}

}

func handleGetSaveGame(rw http.ResponseWriter, r *http.Request){
	GetGameSave(rw,r)
}

func handleDeleteGame(rw http.ResponseWriter, r *http.Request){
	context := appengine.NewContext(r)
	mail := strings.Split(r.URL.String(),"=")[1]
	if err:=DeleteMoves(mail,context); err!=nil{
		http.Error(rw,err.Error(),http.StatusInternalServerError)
	}
}

func handleLogout(rw http.ResponseWriter, r *http.Request){
	UserGoogleLogout(rw,r)
}

func handleSaveGames(rw http.ResponseWriter, r *http.Request){
	if err := SaveMoves(r); err != nil{
		http.Error(rw,err.Error(),http.StatusInternalServerError)
	}

}
