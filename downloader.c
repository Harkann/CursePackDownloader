#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
char* get_modpage( char* url,  char* project_id)
{
	CURL* modpage = curl_easy_init();
	char* complete_url ;
	complete_url = malloc(strlen(url)+strlen(project_id)+1);
	strcpy(complete_url, url) ;
	strcat(complete_url, project_id);
	curl_easy_setopt( modpage, CURLOPT_URL, complete_url ) ;
	curl_easy_setopt( modpage, CURLOPT_FOLLOWLOCATION, 1L) ;
	curl_easy_perform( modpage );
	char *currenturl;
	curl_easy_getinfo( modpage, CURLINFO_EFFECTIVE_URL, &currenturl);
	curl_easy_cleanup( modpage );
	return currenturl;
}

int get_modfile(char* url, char* project_id, char* file_id, char* file_name){
	CURL* easyhandle = curl_easy_init();
  	char* page_url = get_modpage(url, project_id);
  	char* complete_url ;
  	complete_url = malloc(strlen(page_url)+strlen(file_id)+1);
	strcpy(complete_url, url) ;
	strcat(complete_url, file_id);
	curl_easy_setopt( easyhandle, CURLOPT_URL, url ) ;
	curl_easy_setopt(easyhandle, CURLOPT_FOLLOWLOCATION, 1L) ; 
	FILE* file = fopen( file_name, "w");
  	curl_easy_setopt( easyhandle, CURLOPT_WRITEDATA, file) ;
	curl_easy_perform( easyhandle );
	curl_easy_cleanup( easyhandle );
	fclose(file);
	return 0;
}


int main (int argc, char *argv[]){
	char* project_id = "238403";
	char* file_id = "2364318";
	get_modfile("http://minecraft.curseforge.com/mc-mods/", project_id, file_id, "plop");
	return 0;
}

