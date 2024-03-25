#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>


std::vector<std::vector<std::vector<std::string>>> get_command_rules()
{
  system("sudo iptables --list-rules > rules.txt");
  std::ifstream rules_file("rules.txt");
  std::vector<std::vector<std::vector<std::string>>> rules;
  std::vector<std::vector<std::string>>  chaine;
  int m=1;
 
  if(rules_file.is_open())
  {
    std::vector<std::string> rule;
    std::string text;
    std::vector<std::vector<std::string>> one_rules;

    while(std::getline(rules_file, text))
    {
      std::stringstream flux(text);
      std::string text_tmp;
      

      while (flux >> text_tmp) 
      {
        rule.push_back(text_tmp);
      }

      if(rule.size() < 4)
      {
        chaine.push_back(rule);
      }
      else 
      {
        if(m)
        {
          for(int i=0;i<chaine.size();i++)
          {
            std::vector<std::vector<std::string>> r;
            rules.push_back(r);
          }
          m=0;
        }

        for(int i=0;i<chaine.size();i++)
        {
          if(rule.at(1) == chaine.at(i).at(1))
          {
            rules.at(i).push_back(rule);
          }
        }
      }

      rule.clear();
    }

    rules_file.close();
  }
  else 
  {
    std::cout << "Erreur de l'ouverture du fichier input.txt!!!" << std::endl;
  }

  return rules;
}

int main()
{
  std::vector<std::vector<std::vector<std::string>>> rules;

  rules = get_command_rules();

  for(std::vector<std::vector<std::string>> v1 : rules)
  {
    for(std::vector<std::string> v2 : v1)
    {
      for(std::string s : v2)
      {
        std::cout << s << " \t";
      }
      std::cout << std::endl;
    }

    std::cout << std::endl << std::endl;
  }

  return 0;
}
