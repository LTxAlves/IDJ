#pragma once

class Timer
{
    public:
        Timer();
        
        void Update(float);
        void Restart();
        float Get();

    private:
        float time;
};
