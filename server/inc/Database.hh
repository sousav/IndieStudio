//
// Database.hh for database in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/inc/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Wed May 24 15:53:40 2017 Gaëtan Léandre
// Last update Thu May 25 02:29:36 2017 Gaëtan Léandre
//

#ifndef         DATABASE_HH_
#define         DATABASE_HH_

class Database {
private:
    /* data */
public:
    Database ();
    virtual ~Database ();
    Database(const Database &obj);
    Database    &operator=(const Database &obj);
};

#endif /* !DATABASE_HH_ */
