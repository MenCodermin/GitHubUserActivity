#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>

class Activity
{
private:
public:
  static size_t WriteCallback(void *contents, size_t size, size_t nmemb,std::string *output);
  std::string fetchGitHubActivity(std::string username);
  void displayGitHubActivity(const std::string &activityJson);
};

#endif // ACTIVITY_H