#include <stdio.h>
#include "curl/curl.h"


// Callback function to handle the received data
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    printf("%.*s", (int)realsize, (char *)contents);
    return realsize;
}

int main() {
    CURL *curl;
    CURLcode res;

    // Initialize cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set the URL to make the request to
        curl_easy_setopt(curl, CURLOPT_URL, "https://github.com/junxian428");

        // Set the callback function to handle the received data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // Make the HTTP GET request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        // Clean up
        curl_easy_cleanup(curl);
    }

    // Cleanup cURL resources
    curl_global_cleanup();

    return 0;
}
