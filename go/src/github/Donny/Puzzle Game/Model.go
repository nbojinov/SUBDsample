package main;

import(

	"appengine/blobstore"
	"appengine/datastore"
	"appengine"
	"appengine/image"
	"net/http"
	"net/url"
	"encoding/json"
	"appengine/user"
	"fmt"
	"strings"
	"strconv"
)

type Puzzles struct{
	PuzzleName string
	ImageBlobKeys string
}


type HighScore struct{
	Username_mail string
	Highscore int
}

type User_Game struct{
	Username_mail string
	Game_num int
	Move int
	Indexes string
	Positions string
}

type Saved_Game struct {
	Username_mail string
	Game string
	Game_num int 
}


func UploadImageUrl(rw http.ResponseWriter,r *http.Request) (*url.URL){
	context := appengine.NewContext(r)
	url, err := blobstore.UploadURL(context,"/upload",nil)

	if err != nil{
		http.Error(rw,err.Error(),http.StatusInternalServerError)
	}

	return url;
} 


func UploadImage(rw http.ResponseWriter,r *http.Request){
	context := appengine.NewContext(r)
	blobs,_, err := blobstore.ParseUpload(r)
	if  err != nil{
		http.Error(rw,err.Error(),http.StatusInternalServerError)
	}

	file := blobs["file"]
	if len(file) == 0{
		http.Error(rw,"File isn't uploaded",http.StatusInternalServerError)
	}

	puzzleImages := Puzzles{}
	puzzleImages.PuzzleName = "First Puzzle"
	puzzleImages.ImageBlobKeys = string(file[0].BlobKey)

	if _,err:=datastore.Put(context,
		datastore.NewIncompleteKey(context,"Puzzles",ParentDatastoreKey(context,"Puzzles","puzzle_images")),&puzzleImages);
	err != nil{
		http.Error(rw,err.Error(),http.StatusInternalServerError)		
	} 


}

func GetAllUploadedImages(rw http.ResponseWriter,r *http.Request) (img Image){
	 context := appengine.NewContext(r)
	 query := datastore.NewQuery("Puzzles").Ancestor(ParentDatastoreKey(context,"Puzzles","puzzle_images")).Filter("PuzzleName=","First Puzzle").Limit(8)
	 puzzles := make([]Puzzles,0,8)
	 images := make([]string,8,8)
	 _,errq := query.GetAll(context,&puzzles)

	 if errq != nil{
	 	http.Error(rw,errq.Error(),http.StatusInternalServerError)
	 }

	 num := 0

	 for _,puzzleImage:= range puzzles{
	 	blob:=appengine.BlobKey(puzzleImage.ImageBlobKeys)
	 	url,err := image.ServingURL(context,blob,nil)
	 	if err!=nil{
	 		http.Error(rw,err.Error(),http.StatusInternalServerError)
	 		return 
	 	}
	 	images[num] = url.String();
	 	num++
	 }

	 img.UrlImage = images
	 return 
}

func ParentDatastoreKey(context appengine.Context, entityName string, databaseName string) *datastore.Key{
	return datastore.NewKey(context, entityName, databaseName, 0, nil);
}



func UpdateHighscores(context appengine.Context,r *http.Request)( error ){

	decoder := json.NewDecoder(r.Body)
	highscore := HighScore{}
	if err:=decoder.Decode(&highscore); err!=nil{
		return err
	}
	highscores := make([]HighScore,0,1)
	q := datastore.NewQuery("User").Ancestor(ParentDatastoreKey(context,"HighScore","highscores")).Filter("Username_mail=",highscore.Username_mail)
	keys,errq := q.GetAll(context,&highscores)
	if  errq != nil{
		return errq
	} 

	if len(highscores) == 1{
		if _,errput:= datastore.Put(context,keys[0],&highscore); errput != nil{
			return errput
		}
	} else if len(highscores) == 0{
			if _,errput:= datastore.Put(context,datastore.NewIncompleteKey(context,"HighScore",ParentDatastoreKey(context,"HighScore","highscores")),&highscore); 
			errput != nil{
				return errput
			}
	}
	return nil
}

func UserGoogleLogin(rw http.ResponseWriter, r *http.Request){
	context := appengine.NewContext(r)
	usr := user.Current(context)
	if usr == nil{
		url, err := user.LoginURL(context,"/PuzzleGame.html")
		if err != nil{
			http.Error(rw,err.Error(),http.StatusInternalServerError)
			return
		}
		rw.Header().Set("Location",url)
		rw.WriteHeader(http.StatusFound)
		return 
	}

	http.Redirect(rw,r,"/PuzzleGame.html",http.StatusFound)
}


func UserGoogleLogout(rw http.ResponseWriter, r *http.Request){
	context := appengine.NewContext(r)
	if dest, err := user.LogoutURL(context,"/login"); err == nil{
		rw.Header().Set("Location",dest)
		rw.WriteHeader(http.StatusFound)
	} else {
		http.Error(rw,err.Error(),http.StatusInternalServerError)
	}

}

func UploadGameSave(context appengine.Context, r *http.Request)( error ){
	game_save_data := User_Game{}
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&game_save_data); err!=nil{
		return err
	}
	  	
	if _,errput:= datastore.Put(context,datastore.NewIncompleteKey(context,"User_Game",
	ParentDatastoreKey(context,"User_Game","saves")),&game_save_data); 
	errput != nil{
		return errput
	}

	return nil
}

func GetGameSave(rw http.ResponseWriter,r *http.Request){



	var mail string
	var game_num int 
	if cookie,err_mail := r.Cookie("dev_appserver_login"); err_mail != nil{
		http.Error(rw,err_mail.Error(),http.StatusInternalServerError)
		return
	} else {
		mail = strings.Split(cookie.Value,":")[0];
		if cookie_game, err_game := r.Cookie("game_num"); err_game != nil{
			http.Error(rw,err_game.Error(),http.StatusInternalServerError)
			return
		} else {
			var err_conv error
			game_num,err_conv = strconv.Atoi(cookie_game.Value)
			if err_conv != nil{
				http.Error(rw,err_conv.Error(),http.StatusInternalServerError)
				return
			}
		}
	}



	context := appengine.NewContext(r)
	saves:= make([]User_Game,0,25)

	q := datastore.NewQuery("User_Game").Ancestor(ParentDatastoreKey(context,"User_Game","saves")).
			Filter("Username_mail=",mail).Filter("Game_num=",game_num).Order("Move")

    if _,err := q.GetAll(context,&saves); err != nil{
    	http.Error(rw,err.Error(),http.StatusInternalServerError)
	}

	fmt.Fprintf(rw,string(game_num))
	return 

	save_game := ""
	if(len(saves) != 0){
	

		save_data,errJson := json.Marshal(saves)
		if errJson != nil{
			http.Error(rw,errJson.Error(),http.StatusInternalServerError)
		}

		save_game = fmt.Sprintf("%s",save_data)
	}
	rw.Header().Set("Content-type","application/json")
	fmt.Fprintf(rw,save_game)
}

func DeleteMoves(mail string, game_num int, context appengine.Context)(error){
	q := datastore.NewQuery("User_Game").Ancestor(ParentDatastoreKey(context,"User_Game","saves")).
			Filter("Username_mail=",mail).Filter("Game_num=",game_num)
	saves := make([]User_Game,0,10)
	if keys,err := q.GetAll(context,&saves); err == nil{
		datastore.DeleteMulti(context,keys)
	} else{
		return err
	}
	return nil
}

func SaveMoves(r *http.Request) (error){
	context := appengine.NewContext(r)
	decoder := json.NewDecoder(r.Body)
	games := make([]User_Game,0,30)


	if err := decoder.Decode(&games); err != nil{
		return err
	}

	keys := make([]*datastore.Key,len(games),len(games))
	for i := 0; i < len(games); i++{
		keys[i] = datastore.NewIncompleteKey(context, "User_Game",ParentDatastoreKey(context,"User_Game","saves"))
	}

	if _,errput := datastore.PutMulti(context,keys,games); errput != nil{
		return errput;
	}
	return nil
}

func GetSavedGames(r *http.Request) (string, error) {
	context := appengine.NewContext(r)
	var mail string
	if cookie, err := r.Cookie("dev_appserver_login"); err != nil{
		return "",err
	} else {
		mail = strings.Split(cookie.Value,":")[0];
	}

	q := datastore.NewQuery("Saved_Game").Ancestor(ParentDatastoreKey(context,"Saved_Game","games")).
			Filter("Username_mail=",mail).Order("Game_num")

	games := make([]Saved_Game,0,10)

	if _,err := q.GetAll(context,&games); err != nil{
		return "",err
	}

	saved_games := ""

	if(len(games) != 0){
		data, errJson := json.Marshal(games)
		if errJson != nil{
			return "",errJson
		}

		saved_games = fmt.Sprintf("%s",data)
	}

	return saved_games,nil
}

func SaveGame(r *http.Request)(error){
	context := appengine.NewContext(r)

	game := Saved_Game{}


	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&game); err != nil{
		return err
	}
	

	newKey := datastore.NewIncompleteKey(context,"Saved_Game", ParentDatastoreKey(context,"Saved_Game","games"))
	if _,err := datastore.Put(context, newKey, &game); err != nil{
		return err
	}

	return nil
}

func GetGame(r *http.Request) (string,error){
	context := appengine.NewContext(r)

	var mail string
	var game_num int

	if cookie_mail, err_mail := r.Cookie("dev_appserver_login"); err_mail != nil{
		return "",err_mail
	} else {
		mail = strings.Split(cookie_mail.Value,":")[0]
		if cookie_game,err_game := r.Cookie("game_num"); err_game != nil{
			return "",err_game
		} else {
			var errconv error
			game_num,errconv = strconv.Atoi(cookie_game.Value)

			if errconv != nil{
				return "",errconv
			}
		}
	}


	q := datastore.NewQuery("User_Game").Ancestor(ParentDatastoreKey(context,"User_Game","saves")).
			Filter("Username_mail=",mail).Filter("Game_num=",game_num).Order("Move")
	

	saved_games := make([]User_Game,0,10)

	if _,errq := q.GetAll(context,&saved_games); errq != nil{
		return "",errq
	}


	saved_data := ""
	if len(saved_games) != 0{
	
		data, errJson := json.Marshal(saved_games)
		if errJson != nil{
			return "",errJson
		}

		saved_data = fmt.Sprintf("%s",data)
	}
	return saved_data,nil
}