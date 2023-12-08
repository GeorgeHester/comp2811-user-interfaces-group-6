#ifndef STATE_H
#define STATE_H

enum Window
{
    CaptureWindow,
    FriendListWindow,
    ListViewWindow
};

class State
{
    public:
         Window current_window;
    private:
        void rerender();
};

#endif // STATE_H
