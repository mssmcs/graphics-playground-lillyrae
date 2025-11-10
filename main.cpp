#include "graphics.h"

using namespace std;
using namespace mssm;

class Button {
public:
    Vec2d pos;
    Color color;
    int width;
    int height;

    void draw(Graphics& g);
    void fill(Graphics& g);
    //void update(Graphics& g);

    bool isMouseOver(Graphics& g); // return true if mouse is currently over the button
    bool isClicked(Graphics& g); // return true if mouse is clicked
};

void Button::draw(Graphics& g)
{
    g.rect(pos,width,height,color);
}

void Button::fill(Graphics& g)
{
    g.rect(pos,width,height,color,color);
}

bool Button::isMouseOver(Graphics& g)
{
    Vec2d mp = g.mousePos();
    return (mp.x>pos.x&&mp.x<pos.x+width&&mp.y>pos.y&&mp.y<pos.y+height);
}

bool Button::isClicked(Graphics &g)
{
    return(g.onMousePress(MouseButton::Left)&&Button::isMouseOver(g));
}
int main()
{
    Graphics g("Hello Graphics!", 1024, 768);
    Array<int> pattern;
    Array<int> input;
    int frames = 0;
    int score = 0;
    bool correct = true;
    Array<Button> buttons = {{{100,100},RED,100,100},{{350,100},GREEN,100,100},{{600,100},BLUE,100,100},{{850,100},YELLOW,100,100}};
    pattern.append(rand()%4);
    while (g.draw())
    {
        if (!g.isDrawable())
        {
            continue;
        }
        g.text({g.width()/2,2*g.height()/3},18,format("{}",score),WHITE,HAlign::center,VAlign::center);
        if(frames%12>5&&frames/12<pattern.size())
        {
            buttons[pattern[frames/12]].fill(g);
        }
        for(int i=0;i<4;i++)
        {
            buttons[i].draw(g);
            if(buttons[i].isClicked(g))
            {
                buttons[i].fill(g);
                input.append(i);
            }
        }
        frames = frames + 1;
        if(pattern.size()==input.size())
        {
            for(int i=0;i<pattern.size();i++)
            {
                correct = (pattern[i]==input[i]);
            }
            while(input.size()>0)
            {
                input.removeAtIndex(0);
            }
            if(correct)
            {
                frames = 0;
                score = score + pattern.size();
                pattern.append(rand()%4);
            }
        }
        if(correct==false)
        {
            g.text({g.width()/2,g.height()/2},48,format("GAME OVER"),WHITE,HAlign::center,VAlign::center);
            while(pattern.size()>0)
            {
                pattern.removeAtIndex(0);
            }
        }
    }

    return 0;
}
