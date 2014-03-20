package main;

import(
	"appengine/blobstore"
	"appengine/datastore"
	"appengine"
	"net/http"
	"net/url"
)

type Puzzles struct{
	PuzzleName string
	imageBlobKeys string

}


func UploadImageUrl(r *http.Request) (*url.URL){
	context := appengine.NewContext(r)
	url, err := blobstore.UploadURL(context,"/upload",nil)

	if err != nil{

	}

	return url;
} 


func UploadImage(r *http.Request){
	context := appengine.NewContext(r)
	blobs,_, err := blobstore.ParseUpload(r)
	if  err != nil{

	}

	file := blobs["file"]
	if len(file) == 0{

	}

	puzzles := new(Puzzles)
	puzzleImages := make([]Puzzles,0);

	query := datastore.NewQuery("Puzzles")
	newKeyQ,errQ := query.GetAll(context,puzzleImages)
	if errQ != nil{

	}

	key := datastore.NewKey(context,"Puzzles","stringID",0,nil)
	
	if len(puzzleImages) == 0 {
		puzzles.PuzzleName = "First Puzzle"
		puzzles.imageBlobKeys = string(file[0].BlobKey) +", "
		if _,err:= datastore.Put(context,key,&puzzles); err != nil{

		}
	} else {
		puzzleImages[0].imageBlobKeys += string(file[0].BlobKey) + ", "
		datastore.Put(context,newKeyQ[0],&puzzleImages[0])
	}
}

func GetAllUploadedImages(r *http.Request) (string){
	 context := appengine.NewContext(r)
	 query := datastore.NewQuery("Puzzles")
	 puzzles := make([]Puzzles,0)
	 _,errQ := query.GetAll(context,puzzles)

	 blobKeys := puzzles[0].imageBlobKeys;
	 return blobKeys;
}