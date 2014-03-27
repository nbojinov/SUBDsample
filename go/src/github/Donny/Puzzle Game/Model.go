package main;

import(
	"errors"
	"appengine/blobstore"
	"appengine/datastore"
	"appengine"
	"appengine/image"
	"net/http"
	"net/url"
//	"fmt"
)

type Puzzles struct{
	PuzzleName string
	ImageBlobKeys string
}

type User struct{
	Username string
	Password string
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

//adding a user
func AddUser(context appengine.Context, username string, pass string) (error) {
	users := make([]User,0,1)
	q := datastore.NewQuery("User").Ancestor(ParentDatastoreKey(context,"User","game_users")).
			Filter("Username=",username).Filter("Password=",pass)
	if _,err := q.GetAll(context,&users); err != nil {
		return err
	} else if len(users) >= 1{
		return errors.New("There are already other users")		
	}

	user := User{
		Username: username,
		Password: pass,
	}

	if _,err := datastore.Put(context,
		datastore.NewIncompleteKey(context,"User",ParentDatastoreKey(context,"User","game_users")),&user);
	err != nil{
		return err
	}

	return nil
}


func checkIfUser(context appengine.Context, username string, pass string) (bool,error){

	q := datastore.NewQuery("User").Ancestor(ParentDatastoreKey(context,"User","game_users")).Filter("Username=",username).
			Filter("Password=",pass)
	user := make([]User,0,1)

	if _,err := q.GetAll(context,&user); err != nil || len(user) == 0 {
		return false,err
	} else {
		return true,nil
	}

}

