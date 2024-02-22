//
// Created by karim on 22.02.24.
//

#ifndef CS_BACHELOR_PLAYER_H
#define CS_BACHELOR_PLAYER_H


class Player {
public:
    Player();
    Player(int x, int y);

    void move(char direction);

    int x;
    int y;
};


#endif //CS_BACHELOR_PLAYER_H
