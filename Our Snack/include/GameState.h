#ifndef GAMESTATE_H
#define GAMESTATE_H


class GameState
{
    public:
        GameState();
        virtual ~GameState();
        enum GameManager
        {
            STARTINTERFACE,//��ʼ����
            SINGLEPLAY,//�˺��˴�
            AIPLAY//AI
        };
        void changeGameState(GameManager gameManager);
    protected:

    private:
};

#endif // GAMESTATE_H
