#include "activity.h"
#include <iostream>

int main(int argc, char *argv[])
{
  Activity a;
  if (argc != 2)
  {
    std::cerr << "Usage: github-activity <username>\n";
    return 1;
  }

  std::string username = argv[1];
  std::string response = a.fetchGitHubActivity(username);

  if (!response.empty())
    a.displayGitHubActivity(response);
  else
    std::cerr << "Failed to fetch activity for user: " << username << "\n";

  return 0;
}