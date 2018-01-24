//
// Race.hh for race in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/inc/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Fri May 26 03:45:38 2017 Gaëtan Léandre
// Last update Fri May 26 03:59:01 2017 Gaëtan Léandre
//

#ifndef             RACE_HH_
#define             RACE_HH_

#include            "Group.hh"

class Race : public Group {
private:
    int _id;

public:
    explicit Race(int id);
    virtual ~Race();
    Race(const Race &obj);
    Race    &operator=(const Race &obj);
    int getId() const;
    void setId(int id);
    int getLeader() const;
};

#endif /* !RACE_HH_ */
