#include "activity.h"
#include "json.hpp"
#include <curl/curl.h>
#include <filesystem>
#include <iostream>
#include <map>

std::string Activity::fetchGitHubActivity(std::string username)
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  if (curl)
  {
    std::string url = "https://api.github.com/users/" + username + "/events";

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    struct curl_slist *headers = nullptr;
    headers = curl_slist_append(headers, "User-Agent: Cpp-GitHub-Activity");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res)
                << std::endl;
    }

    curl_easy_cleanup(curl);
  }
  return readBuffer;
}

void Activity::displayGitHubActivity(const std::string &activityJson)
{
  try
  {
    auto json = nlohmann::json::parse(activityJson);

    for (const auto &event : json)
    {
      std::cout << "Event type: " << event["type"] << "\n";
      std::cout << "Repo: " << event["repo"]["name"] << "\n";
      ;

      if (event.contains("created_at"))
      {
        std::cout << "Created at:" << event["created_at"] << "\n";
      }
      std::cout << "-------------------------------\n";
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error parsion JSON: " << e.what() << "\n";
  }
}

size_t Activity::WriteCallback(void *contents, size_t size, size_t nmemb,
                               std::string *output)
{
  size_t totalSize = size * nmemb;
  output->append((char *)contents, totalSize);
  return totalSize;
}