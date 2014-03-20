package main

import (
	
	"html/template"
	"net/http"
	"strings"
	"appengine"
	"appengine/image"
	"encoding/json"
)

type Image struct{
	urlImage string;
}

func (Image) Error() (string){
	return "I am starting to get angry"
}


func init(){
	http.HandleFunc("/uploadForm",uploadForm)
	http.HandleFunc("/upload",upload)
}

const uploadTemplate = "<html><body><form action='{{.}}' method='POST' enctype='multipart/form-data'>Upload File: <input type='file' name='file'><br><input type='submit' name='submit' value='Submit'></form></body></html>";
func uploadForm(rw http.ResponseWriter, r *http.Request){
	uploadUrl := UploadImageUrl(r)	

	template.Must(template.New("upload").Parse(uploadTemplate)).Execute(rw,uploadUrl)
}

func upload(rw http.ResponseWriter, r *http.Request){
	UploadImage(r)
	http.Redirect(rw,r,"/uploadForm",http.StatusFound)
}

func handleUploadedImages(rw http.ResponseWriter,r *http.Request){

	context := appengine.NewContext(r)
	blobKeys := GetAllUploadedImages(r);
	blobKsForUrl := strings.Split(blobKeys,", ")
	imageUrls  := new(string)
	images := make([]Image,0)

	for _,key := range blobKsForUrl{
		blob := appengine.BlobKey(key)
		url,err := image.ServingURL(context,blob,nil)
		
		if err != nil{
			http.Error(rw,err.Error(),http.StatusInternalServerError)
		}

		image := []Image{Image{url.String()}}	
		res :=append(images,image)
	}

	imageUrls += json.Marshal(images)
	fmt.Fprintf(rw,imageUrls)
}

