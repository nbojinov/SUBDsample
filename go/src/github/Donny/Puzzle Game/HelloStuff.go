package main

import (
	"appengine"
	"net/http"
	"strings"
	"strconv"
	"fmt"

)

type Image struct{
	UrlImage []string  
}


func init(){
	http.HandleFunc("/upload",upload)
	http.HandleFunc("/getPuzzle",handleGetUploadedImages)
	http.HandleFunc("/login",handleLogin)
	http.HandleFunc("/updateScore",handleUpdateHighscore)
	http.HandleFunc("/saveMove",handleSaveMove)
	http.HandleFunc("/getSavedMoves",handleGetSaveGame)
	http.HandleFunc("/getSavedGames",handleGetSavedGames)
	http.HandleFunc("/deleteMoves",handleDeleteMoves)
	http.HandleFunc("/logout",handleLogout)
	http.HandleFunc("/saveMoves",handleSaveMoves)
	http.HandleFunc("/createGame",handleCreateGame)
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

func handleSaveMove(rw http.ResponseWriter, r *http.Request){
	context := appengine.NewContext(r)
	if err := UploadGameSave(context,r); err != nil{
		http.Error(rw,err.Error(),http.StatusInternalServerError)
	}

}

func handleGetSaveGame(rw http.ResponseWriter, r *http.Request){

	if save_game, err:=GetGame(r); err != nil{
		http.Error(rw, err.Error(),http.StatusInternalServerError)
	} else{
		rw.Header().Set("Content-type","application/json")
		fmt.Fprintf(rw,save_game)
	}
}

func handleDeleteMoves(rw http.ResponseWriter, r *http.Request){
	context := appengine.NewContext(r)

	var mail string
	var game_num int 

	if cookie_mail, err_mail:= r.Cookie("dev_appserver_login"); err_mail != nil{
		http.Error(rw,err_mail.Error(),http.StatusInternalServerError)
	} else {
		mail = strings.Split(cookie_mail.Value,":")[0]
		if cookie_game, err_game := r.Cookie("game_num"); err_game != nil{
			http.Error(rw,err_game.Error(),http.StatusInternalServerError)
		} else {
			var errstr error
			game_num,errstr = strconv.Atoi(cookie_game.Value)

			if errstr!=nil{
				http.Error(rw,errstr.Error(),http.StatusInternalServerError)
			}
		}
	}

	if err:=DeleteMoves(mail,game_num,context); err!=nil{
		http.Error(rw,err.Error(),http.StatusInternalServerError)
	}
}

func handleLogout(rw http.ResponseWriter, r *http.Request){
	UserGoogleLogout(rw,r)
}

func handleSaveMoves(rw http.ResponseWriter, r *http.Request){

	if err := SaveMoves(r); err != nil{
		http.Error(rw,err.Error(),http.StatusInternalServerError)
	}

}

func handleCreateGame(rw http.ResponseWriter, r *http.Request){
	if err := SaveGame(r); err != nil{
		http.Error(rw,err.Error(),http.StatusInternalServerError)
	} 
}

func handleGetSavedGames(rw http.ResponseWriter, r *http.Request){
	
	
	 if json_data,err := GetSavedGames(r); err != nil{
	 	if err.Error() != "ErrNoCookie"{
		 	http.Error(rw,err.Error(),http.StatusInternalServerError)
	 	}

	 } else {
		rw.Header().Set("content-type","application/json")
	 	fmt.Fprintf(rw,"%s",json_data)
	 }
}
