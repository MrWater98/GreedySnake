#ifndef GAMESTATE_H
#define GAMESTATE_H


class GameState
{
    public:
        GameState();
        virtual ~GameState();
        enum GameManager
        {
            STARTINTERFACE,//开始界面
            SINGLEPLAY,//人和人打
            AIPLAY//AI
        };
        void changeGameState(GameManager gameManager);
    protected:

    private:
};

#endif // GAMESTATE_H
