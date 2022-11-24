#include <stdio.h>
#include <curl/curl.h>

static void curl_verbose_output(
    CURL* handle, curl_infotype type, char* data, size_t size, void* userptr)
{
    const char *text;
    (void)handle; /* prevent compiler warning */
    (void)userptr;
    
    switch (type) {
    case CURLINFO_TEXT:
        fputs("== Info: ", stderr);
        fwrite(data, size, 1, stderr);
    default: /* in case a new one is introduced to shock us */
        return;
    
    case CURLINFO_HEADER_OUT:
        text = "=> Send header";
        break;
    case CURLINFO_DATA_OUT:
        text = "=> Send data";
        break;
    case CURLINFO_SSL_DATA_OUT:
        text = "=> Send SSL data";
        break;
    case CURLINFO_HEADER_IN:
        text = "<= Recv header";
        break;
    case CURLINFO_DATA_IN:
        text = "<= Recv data";
        break;
    case CURLINFO_SSL_DATA_IN:
        text = "<= Recv SSL data";
        break;
    }
    
    printf("err: %s\n", text);
}

int main(void)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://echo.ignition.av-lr.a2z.com/echo/200/body");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        // curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, &curl_verbose_output);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        
        curl_easy_cleanup(curl);
    }

    return 0;
}