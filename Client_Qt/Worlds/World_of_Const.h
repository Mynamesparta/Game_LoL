#ifndef WORLD_OF_CONST_H
#define WORLD_OF_CONST_H

namespace World_of_const
{
    enum Animation_state{Stand,Start_move,Move,End_move,Autoattacks};
    const unsigned int TimeStep_World_move=0.1*1000;
    const unsigned int TimeStep_Animation=0.5*1000;
}

#endif // WORLD_OF_CONST_H
