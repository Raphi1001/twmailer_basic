#include <iostream>
#include <sys/wait.h>
#include <dirent.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <algorithm>
#include <limits.h>

#include "include/MyfindClass.h"

/* Helperfunktionen */
void MyfindClass::Print_usage()
{
   fprintf(stderr, "Usage: %s [-R] [-i] searchpath filename1 [filename2] …[filenameN]\n", program_name);
   exit(EXIT_FAILURE);
}

std::string MyfindClass::StringToLower(std::string str)
{
   // Konvertier string auf kleinschreibung
   std::for_each(str.begin(), str.end(), [](char &c)
                 { c = ::tolower(c); });
   return str;
}

// zur Sicherheit falls irgendwas abhanden gekommen ist
// Holt alle Prozesse und beendet diese
void MyfindClass::KillZombies()
{
   pid_t childpid;
   while ((childpid = waitpid(-1, NULL, WNOHANG)))
   {
      if ((childpid == -1) && (errno != EINTR))
         break;
   }
}

/* relevanter code */

// liest Optionssatz aus und setzt entsprechende Flags
// dazu wird der searchpath gesetzt und die filenamen werden in einem eigenem vector geseichert => filenames
// liefert true bei erfolg ansonsten false zurück
bool MyfindClass::ReadInput(int argc, char *argv[])
{
   int c;
   bool error = false;

   program_name = argv[0];

   while ((c = getopt(argc, argv, ":Ri")) != EOF && !error)
   {
      switch (c)
      {
      case 'R':
         if (recursive)
            error = true;
         recursive = true;
         break;

      case 'i':
         if (!caseSensitve)
            error = true;
         caseSensitve = false;
         break;

      case '?':
         error = true;
         break;

      default:
         assert(0);
         break;
      }
   }

   if (error || argc < optind + 2)
   {
      Print_usage();
      return false;
   }

   //Konotrolle ob gegebens Verzeichnis existiert
   DIR *dirp;
   if ((dirp = opendir(argv[optind])) == NULL)
   {
      perror("Failed to open directory");
      exit(EXIT_FAILURE);
      return false;
   }
   closedir(dirp);

   //Konvertierung auf absoluten Pfad
   char buf[PATH_MAX];
   char *res = realpath(argv[optind], buf);
   if (res)
   {
      searchpath = res;
   }
   else
   {
      std::cout << strerror(errno);
      perror("realpath");
      exit(EXIT_FAILURE);
      return false;
   }

   optind++;
   while (optind < argc)
   {
      filenames.push_back(argv[optind]);
      optind++;
   }
   return true;
}

// startet die filesuche
// setzt working directory
// ruft ForkFiles() und WaitChild() auf
bool MyfindClass::StartSearch()
{
   ForkFiles(); // wird geforkt
   WaitChild(); // jeder Childprozess einzeln
   return true;
}

// für jedes File wird das Programm einmal geforkt
// i wird benutzt um auf das richtige Element zuzugreifen
// parent wartet am ende auf die Childprozesse
// Childprozess ruft FindFile mit i auf
void MyfindClass::ForkFiles()
{
   for (int i = 0; i < (int)filenames.size(); i++)
   {
      pid_t pid = fork();

      switch (pid)
      {
      //fehler
      case -1:
         printf("Child could not be startet.");
         exit(EXIT_FAILURE);
         break;

      //Childprozess
      case 0:
         try
         {
            FindFile(i);
            exit(EXIT_SUCCESS);
         }
         catch (const std::exception &e)
         {
            std::cerr << "Childprozess had an error: " << e.what() << '\n';
            exit(EXIT_FAILURE);
         }
         break;
      //Parentprozess
      default:
         children.push_back(pid);
         break;
      }
   }
}

// wartet auf alle Childprozesse und gibt die Daten Strukturiert aus
void MyfindClass::WaitChild()
{
   while (children.size() > 0)
   {
      int status = 0;
      pid_t pid = wait(&status);
      for (int i = 0; i < (int)children.size(); i++)
      {
         if (children[i] == pid)
         {
            children.erase(children.begin() + i);
            if ((int)filenames.size() >= i)
               filenames.erase(filenames.begin() + i);
            break;
         }
      }
   }
}

void MyfindClass::FindFile(int i)
{
   SingleSearch(searchpath, filenames[i]);
   std::cout << "<" << getpid() << ">: <" << filenames[i] << ">: <" << pathToFile << ">" << std::endl;
}

//sucht nach File in einzelnem Pfad/Verzeichnis, falls rekursiv wird Funktion für jedes Subdirectory/Subfile erneut aufgerufen
void MyfindClass::SingleSearch(std::string path, std::string fileToSearch)
{
   struct dirent *direntp;
   DIR *dirp = opendir(path.c_str());

   if (!dirp)
   {
      return;
   }

   std::string newPath;
   while ((direntp = readdir(dirp)) != NULL)
   {
      if (pathToFile != "Not Found")
         return;

      if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0) //"." und ".." Verzeichnisse überspringen
      {
         newPath = path + "/" + direntp->d_name;

         std::string str1 = direntp->d_name;
         std::string str2 = fileToSearch;

         if (!caseSensitve)
         {
            str1 = StringToLower(str1);
            str2 = StringToLower(str2);
         }

         if (str1 == str2)
         {
            pathToFile = newPath;

            closedir(dirp);
            return;
         }

         if (recursive)
         {
            SingleSearch(newPath, fileToSearch);
         }
      }
   }
   closedir(dirp);
}
