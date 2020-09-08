#include<play.h>
int slider;
int slider_puzzle(int a[], int step[], int slider, int depth);
void simplify_print(int*);
int down1(int a[], int slider, int step[], int depth);
int up1(int a[], int slider, int step[], int depth);
int left1(int a[], int slider, int step[], int depth);
int right1(int a[], int slider, int step[], int depth);
int search_depth = 20;
int tile_puzzle();
int step[200] = { 0 };
int c = 0;


bool check(int a[])
{
    for (int i = 0; i < 9; i++)
    {
        if (a[i] != i)
            return false;
    }
    return true;
}
bool up(int a[], int slider)
{
    for (int i = 0; i < 9; i++)
    {
        if (a[i] == slider)
        {
            if (i < 3)
                return false;
            int temp = a[i];
            a[i] = a[i - 3];
            a[i - 3] = temp;
            return true;
        }
    }
}
bool down(int a[], int slider)
{
    for (int i = 0; i < 9; i++)
    {
        if (a[i] == slider)
        {
            if (i > 5)
                return false;
            int temp = a[i];
            a[i] = a[i + 3];
            a[i + 3] = temp;
            return true;
        }
    }
}
bool left(int a[], int slider)
{
    for (int i = 0; i < 9; i++)
    {
        if (a[i] == slider)
        {
            if (i % 3 == 0)
                return false;
            int temp = a[i];
            a[i] = a[i - 1];
            a[i - 1] = temp;
            return true;
        }
    }
}
bool right(int a[], int)
{
    for (int i = 0; i < 9; i++)
    {
        if (a[i] == slider)
        {
            if (i % 3 == 2)
                return false;
            int temp = a[i];
            a[i] = a[i + 1];
            a[i + 1] = temp;
            return true;
        }
    }
}

struct position
{
    int x;
    int y;
};
bool tile_up(position& a, int b[])
{
    if (a.x == 0)
        return false;
    int temp = b[a.x * 3 + a.y];
    b[a.x * 3 + a.y] = b[a.x * 3 + a.y - 3];//question: why a.(x-1)*3 is wrong
    b[a.x * 3 + a.y - 3] = temp;
    a.x--;
    step[c] = 1;
    c++;
    return true;
}
bool tile_down(position& a, int b[])
{
    if (a.x == 2)
        return false;
    int temp = b[a.x * 3 + a.y];
    b[a.x * 3 + a.y] = b[a.x * 3 + a.y + 3];
    b[a.x * 3 + a.y + 3] = temp;
    a.x++;
    step[c] = 2;
    c++;
    return true;
}
bool tile_left(position& a, int b[])
{
    if (a.y == 0)
        return false;
    int temp = b[a.x * 3 + a.y];
    b[a.x * 3 + a.y] = b[a.x * 3 + a.y - 1];
    b[a.x * 3 + a.y - 1] = temp;
    a.y--;
    step[c] = 3;
    c++;
    return true;
}
bool tile_right(position& a, int b[])
{
    if (a.y == 2)
        return false;
    int temp = b[a.x * 3 + a.y];
    b[a.x * 3 + a.y] = b[a.x * 3 + a.y + 1];
    b[a.x * 3 + a.y + 1] = temp;
    a.y++;
    step[c] = 4;
    c++;
    return true;
}
void target_up(position& target, position& slider, int height, int a[9])//height:target height after moving
{
    while (target.x != height)
    {
        while (slider.x >= target.x)
        {
            if (a[slider.x * 3 + slider.y - 3] != a[target.x * 3 + target.y])
                tile_up(slider, a);
            else
            {
                if (tile_left(slider, a) == 0)
                    tile_right(slider, a);
            }
        }
        while (slider.x < (target.x) - 1)
        {
            tile_down(slider, a);
        }
        while (slider.y != target.y)
        {
            if (slider.y > target.y)
                tile_left(slider, a);
            if (slider.y < target.y)
                tile_right(slider, a);
        }
        if (tile_down(slider, a))
            target.x--;
    }
}
void target_down(position& target, position& slider, int des, int a[9])
{
    while (target.x != des)
    {
        while (slider.x <= target.x)
        {
            if (a[slider.x * 3 + slider.y + 3] != a[target.x * 3 + target.y])
                tile_down(slider, a);
            else
            {
                if (tile_left(slider, a) == 0)
                    tile_right(slider, a);
            }
        }
        while (slider.x > (target.x) + 1)
        {
            tile_up(slider, a);
        }
        while (slider.y != target.y)
        {
            if (slider.y > target.y)
                tile_left(slider, a);
            if (slider.y < target.y)
                tile_right(slider, a);
        }
        if (tile_up(slider, a))
            target.x++;
    }
}
void target_left(position& target, position& slider, int des, int a[9])
{
    while (target.y != des)
    {
        while (slider.y >= target.y)
        {
            if (a[slider.x * 3 + slider.y - 1] != a[target.x * 3 + target.y])
                tile_left(slider, a);
            else
            {
                if (tile_up(slider, a) == 0)
                    tile_down(slider, a);
            }
        }
        while (slider.y < (target.y) - 1)
        {
            tile_right(slider, a);
        }
        while (slider.x != target.x)
        {
            if (slider.x < target.x)
                tile_down(slider, a);
            if (slider.x > target.x)
                tile_up(slider, a);
        }
        if (tile_right(slider, a))
            target.y--;
    }
}
void target_right(position& target, position& slider, int des, int a[9])
{
    while (target.y != des)
    {
        while (slider.y <= target.y)
        {
            if (a[slider.x * 3 + slider.y + 1] != a[target.x * 3 + target.y])
                tile_right(slider, a);
            else
            {
                if (tile_up(slider, a) == 0)
                    tile_down(slider, a);
            }
        }
        while (slider.y > (target.y) + 1)
        {
            tile_left(slider, a);
        }
        while (slider.x != target.x)
        {
            if (slider.x < target.x)
                tile_down(slider, a);
            if (slider.x > target.x)
                tile_up(slider, a);
        }
        if (tile_left(slider, a))
            target.y++;
    }
}
void one_move(position& target, position& slider, position& destination, int a[9])
{
    if (destination.y > target.y)
        target_right(target, slider, destination.y, a);
    if (destination.x < target.x)
        target_up(target, slider, destination.x, a);
    if (destination.x > target.x)
        target_down(target, slider, destination.x, a);
    if (destination.y < target.y)
        target_left(target, slider, destination.y, a);
}
void two_move(position& two, position& slider, int a[])
{
    while (a[1] != 2)
    {
        if (two.x == 2)
        {
            if (slider.x == 0)
            {
                tile_down(slider, a);
            }
            while (slider.y > two.y)
                tile_left(slider, a);
            while (slider.y < two.y)
                tile_right(slider, a);
            tile_down(slider, a);
            if (two.y == 0)
            {
                tile_right(slider, a);
                tile_up(slider, a);
                tile_left(slider, a);
                while (tile_down(slider, a));
                while (tile_right(slider, a));
                while (tile_up(slider, a));
                tile_left(slider, a);
                tile_down(slider, a);
            }
            if (two.y == 1)
            {
                tile_right(slider, a);
                tile_up(slider, a);
                tile_up(slider, a);
                tile_left(slider, a);
                tile_down(slider, a);
            }
            if (two.y == 2)
            {
                tile_left(slider, a);
                tile_up(slider, a);
                tile_right(slider, a);
                tile_up(slider, a);
                tile_left(slider, a);
                tile_down(slider, a);
            }
        }
        if (two.x == 1)
        {
            if (slider.x == 0)
            {
                if (two.y == 0)
                {
                    tile_down(slider, a);
                    tile_left(slider, a);
                    while (tile_down(slider, a));
                    while (tile_right(slider, a));
                    while (tile_up(slider, a));
                    tile_left(slider, a);
                    tile_down(slider, a);
                }
                if (two.y == 1)
                {
                    tile_down(slider, a);
                }
                if (two.y == 2)
                {
                    tile_down(slider, a);
                    tile_right(slider, a);
                    tile_up(slider, a);
                    tile_left(slider, a);
                    tile_down(slider, a);
                }
            }
            if (slider.x == 1)
            {
                if (two.y == 1)
                {
                    tile_down(slider, a);
                    while (tile_right(slider, a));
                    while (tile_up(slider, a));
                    tile_left(slider, a);
                    tile_down(slider, a);
                }
                else
                {
                    tile_right(slider, a);
                    tile_right(slider, a);
                    tile_up(slider, a);
                    tile_left(slider, a);
                    tile_down(slider, a);
                }
            }
        }
        if (two.x == 0)
        {
            if (slider.x == 0)
                tile_right(slider, a);
            if (slider.x == 1)
            {
                tile_right(slider, a);
                tile_up(slider, a);
                tile_right(slider, a);
            }
        }
    }
    two.x = 0;
    two.y = 1;
}
bool check_three(int a[])
{
    if (a[1] == 3)
        return true;
    return false;
}
void update_position(position& target, int num, int a[])
{
    for (int i = 0; i < 9; i++)
    {
        if (a[i] == num)
            target = { i / 3,i % 3 };
    }
}
void three_move(position& three, position& slider, int a[])
{
    while (tile_right(slider, a));
    while (tile_up(slider, a));
    tile_down(slider, a);
    tile_left(slider, a);
    tile_left(slider, a);
    if (a[6] == 3)
    {
        tile_down(slider, a);
        tile_right(slider, a);
        tile_up(slider, a);
        tile_left(slider, a);
    }
    tile_up(slider, a);
    tile_right(slider, a);
    update_position(three, 3, a);
    if (three.x == 2)
    {
        tile_down(slider, a);
        int i = 0;
        while (three.x != 1 || slider.x != 1)
        {
            if (i % 4 == 0)
                tile_down(slider, a);
            if (i % 4 == 1)
                tile_right(slider, a);
            if (i % 4 == 2)
                tile_up(slider, a);
            if (i % 4 == 3)
                tile_left(slider, a);
            i++;
            update_position(three, 3, a);
        }
        tile_right(slider, a);
        update_position(three, 3, a);
        i = 0;
        while (!check_three(a))
        {
            if (i % 4 == 0)
                tile_up(slider, a);
            if (i % 4 == 1)
                tile_left(slider, a);
            if (i % 4 == 2)
                tile_down(slider, a);
            if (i % 4 == 3)
                tile_right(slider, a);
            i++;
            update_position(three, 3, a);
        }
        tile_right(slider, a);
        tile_up(slider, a);
        tile_left(slider, a);
        tile_left(slider, a);
        tile_down(slider, a);
    }
    else
    {
        int i = 0;
        while (!check_three(a))
        {
            if (i % 4 == 3)
                tile_up(slider, a);
            if (i % 4 == 2)
                tile_left(slider, a);
            if (i % 4 == 1)
                tile_down(slider, a);
            if (i % 4 == 0)
                tile_right(slider, a);
            i++;
            update_position(three, 3, a);
        }
        tile_right(slider, a);
        tile_up(slider, a);
        tile_left(slider, a);
        tile_left(slider, a);
        tile_down(slider, a);
    }
}
bool check_four(int a[])
{
    if (a[3] == 4)
        return true;
    return false;
}
void four_move(position four, position slider, int a[])
{
    if (check_four(a))
        return;
    if (four.y == 2)
    {
        tile_right(slider, a);
        int i = 0;
        while (four.y != 1)
        {
            if (i % 4 == 2)
                tile_up(slider, a);
            if (i % 4 == 3)
                tile_left(slider, a);
            if (i % 4 == 0)
                tile_down(slider, a);
            if (i % 4 == 1)
                tile_right(slider, a);
            i++;
            update_position(four, 4, a);
        }
        tile_up(slider, a);
        tile_left(slider, a);
        i = 0;
        while (!check_four(a))
        {
            if (i % 4 == 2)
                tile_up(slider, a);
            if (i % 4 == 1)
                tile_left(slider, a);
            if (i % 4 == 0)
                tile_down(slider, a);
            if (i % 4 == 3)
                tile_right(slider, a);
            i++;
            update_position(four, 4, a);
        }
    }
    if (four.y != 2)
    {
        int i = 0;
        while (!check_four(a))
        {
            if (i % 4 == 3)
                tile_up(slider, a);
            if (i % 4 == 2)
                tile_left(slider, a);
            if (i % 4 == 1)
                tile_down(slider, a);
            if (i % 4 == 0)
                tile_right(slider, a);
            i++;
            update_position(four, 4, a);
        }
    }
}
bool check_seven(int a[])
{
    if (a[6] == 7)
        return true;
    return false;
}
void seven_move(position seven, position slider, int a[])
{
    if (a[8] == 7)
    {
        tile_down(slider, a);
        tile_right(slider, a);
        tile_up(slider, a);
        tile_left(slider, a);
    }
    tile_right(slider, a);
    tile_up(slider, a);
    tile_left(slider, a);
    tile_left(slider, a);
    tile_down(slider, a);
    int i = 0;
    while (!(check_seven(a) != 0 && slider.y == 0))
    {
        if (i % 4 == 2)
            tile_up(slider, a);
        if (i % 4 == 3)
            tile_left(slider, a);
        if (i % 4 == 0)
            tile_down(slider, a);
        if (i % 4 == 1)
            tile_right(slider, a);
        i++;
        update_position(seven, 7, a);
    }
    tile_up(slider, a);
    tile_up(slider, a);
    tile_right(slider, a);
    tile_right(slider, a);
    tile_down(slider, a);
}
bool final_check(int a[])
{
    for (int i = 0; i < 8; i++)
    {
        if (a[i] != i + 1)
            return false;
    }
    return true;
}
void final_move(position slider, int a[])
{
    int i = 0;
    while (!final_check(a))
    {
        if (i % 4 == 3)
            tile_up(slider, a);
        if (i % 4 == 0)
            tile_left(slider, a);
        if (i % 4 == 1)
            tile_down(slider, a);
        if (i % 4 == 2)
            tile_right(slider, a);
        i++;
    }
}
void check_repeat(int* a)
{
    if (*a * *(a + 1) == 2 || *a * *(a + 1) == 12)
    {
        *a = -1;
        *(a + 1) = -1;
    }
}
void check_recur(int* a)
{
    int one = *a;
    int two = *(a + 1);
    int three = *(a + 2);
    int four = *(a + 3);
    if (one * two * three * four == 24)
    {
        int i = 0;
        while (1)
        {
            if (i % 4 == 0)
            {
                if (*(a + i) != one)
                    break;
            }
            if (i % 4 == 1)
            {
                if (*(a + i) != two)
                    break;
            }
            if (i % 4 == 2)
            {
                if (*(a + i) != three)
                    break;
            }
            if (i % 4 == 3)
            {
                if (*(a + i) != four)
                    break;
            }
            i++;
        }
        if (i >= 6)
        {
            for (int j = 0; j < i; j++)
                a[j] = -1;
            while (i >= 12)
                i = i - 12;
            for (int j = 0; j < 12 - i; j++)
            {
                if (j % 4 == 0)
                {
                    a[j] = two;
                }
                if (j % 4 == 1)
                {
                    a[j] = one;
                }
                if (j % 4 == 2)
                {
                    a[j] = four;
                }
                if (j % 4 == 3)
                {
                    a[j] = three;
                }
            }
        }
    }
}
int* output(int* a)
{
    int i = 0;
    while (step[i] != 0)
    {
        if (step[i] != -1)
            check_repeat(&step[i]);
        if (step[i] != -1)
            check_recur(&step[i]);
        i++;
    }
    int j = 0, k = 0;
    while (step[j] != 0)
    {
        if (step[j] != -1)
        {
            a[k] = step[j];
            k++;
        }
        j++;
    }
    i = 0;
    while (a[i] != 0)
    {
        if (a[i] != -1)
            check_repeat(&step[i]);
        if (a[i] != -1)
            check_recur(&step[i]);
        i++;
    }
            return a;
}

int* autoComplete(int array[], Ui::MainWindow* ui, int* s)
{
    int a[9];
    for(int i=0;i<9;i++)
    {
        a[i]=array[i];
    }
    position slider;
    update_position(slider, 0, a);
    position one;
    update_position(one, 1, a);
    position des = { 0,0 };
    one_move(one, slider, des, a);
    position two;
    update_position(two, 2, a);
    two_move(two, slider, a);
    position three;
    update_position(three, 3, a);
    three_move(three, slider, a);
    position four;
    update_position(four, 4, a);
    four_move(four, slider, a);
    position seven;
    update_position(seven, 7, a);
    update_position(slider, 0, a);
    seven_move(seven, slider, a);
    update_position(slider, 0, a);
    final_move(slider, a);
    s=output(s);
    return s;
}
