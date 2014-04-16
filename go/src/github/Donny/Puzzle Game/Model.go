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
	Move int
	Indexes string
	Positions string
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
	mail := strings.Split(r.URL.String(),"=")[1]
	context := appengine.NewContext(r)
	saves:= make([]User_Game,0,25)

	q := datastore.NewQuery("User_Game").Ancestor(ParentDatastoreKey(context,"User_Game","saves")).
			Filter("Username_mail=",mail).Order("Move")

    if _,err := q.GetAll(context,&saves); err != nil{
    	http.Error(rw,err.Error(),http.StatusInternalServerError)
	}


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

func DeleteMoves(mail string, context appengine.Context)(error){
	q := datastore.NewQuery("User_Game").Ancestor(ParentDatastoreKey(context,"User_Game","saves")).
			Filter("Username_mail=",mail)
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